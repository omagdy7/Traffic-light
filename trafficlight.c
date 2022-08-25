#include "trafficlight.h"

/* 
  Function to handle the state machine of each traffic light
*/
void set_tf_color(Traffic tf, uint8_t color) {
  uint32_t pins = 0xFF;
	switch (color) {
		case RED:
      GPIOPinWrite(tf.port, pins, (1 << tf.red));
			break;
		case YELLOW:
      GPIOPinWrite(tf.port ,pins, (1 << tf.yellow));
			break;
		case GREEN:
      GPIOPinWrite(tf.port ,pins, (1 << tf.green));
			break;
	}
}

/* 
  Function that takes port base address and the clk of the port and the corresponding input and output pins
*/
void PortInit(uint32_t port, uint32_t clk, uint32_t input, uint32_t output) {
  uint32_t pins = 0xFF; 
  SysCtlPeripheralEnable(clk);
  while(!SysCtlPeripheralReady(clk)) {};
  GPIOUnlockPin(port, pins);
  GPIOPinTypeGPIOInput(port, input);
  GPIOPinTypeGPIOOutput(port, output);
  GPIOPadConfigSet (port, pins,
  GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}

void portsInit() {
  PortInit(GPIO_PORTA_BASE, SYSCTL_PERIPH_GPIOA, 0x0, 0xFF); // Initialize porta as all output
  PortInit(GPIO_PORTB_BASE, SYSCTL_PERIPH_GPIOB, 0x0, 0xFF); // Initialize portb as all output
  PortInit(GPIO_PORTD_BASE, SYSCTL_PERIPH_GPIOD, 0x0, 0xFF); // Initialize portb as all output
  PortInit(GPIO_PORTE_BASE, SYSCTL_PERIPH_GPIOE, 0x0, 0xFF); // Initialize portb as all output
  PortInit(GPIO_PORTF_BASE, SYSCTL_PERIPH_GPIOF, 0x1, 0x7E); // Initialize portf as the first pin input and the rest output
}

/*
  Function that takes a timer address and the function that handler the timer interrupt flag, 
  the clock of the timer and the intial delay of the timer
*/
void TimerInit(uint32_t timer, void(*timer_handler)(), uint32_t clk, uint32_t delay) {
  SysCtlPeripheralEnable(clk);
  while(!SysCtlPeripheralReady(clk)) {}
  TimerDisable(timer, TIMER_BOTH);
  TimerConfigure(timer, (TIMER_CFG_PERIODIC));
  TimerLoadSet(timer, TIMER_BOTH, delay);
  TimerIntUnregister(timer, TIMER_BOTH);
  TimerEnable(timer, TIMER_BOTH);
  TimerIntRegister(timer, TIMER_BOTH, timer_handler);
  TimerIntEnable(timer, TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT);
}

/*
  Function that handles traffic_1 timer 
*/
void Timer0_Handler() {
  Traffic_Handler(&tf1);
}

/*
  Function that handles traffic_2 timer
*/
void Timer1_Handler() {
  Traffic_Handler(&tf2);
}

/*
  Function that handles pedestrian traffic timer
*/
void Timer2_Handler() {
  TimerIntClear(tf_ped.timer, TIMER_BOTH);
  switch(tf_ped.cur_color) {
    case RED: // If I am here it means I finished my red period
      tf_ped.cur_color = GREEN;
      set_tf_color(tf_ped, GREEN);
      TimerLoadSet(tf_ped.timer, TIMER_BOTH, GREEN_PERIOD);
      break;
    case YELLOW: // If I am here it means I finished my yellow period
      // set both traffic1 and traffic2 to their previous color before the pedestrian pushed the button
      set_tf_color(tf1, tf1.cur_color);
      set_tf_color(tf2, tf2.cur_color);
      set_tf_color(tf_ped, RED);
      // Re enable traffic1 and 2 timers
      TimerEnable(tf1.timer, TIMER_BOTH);
      TimerEnable(tf2.timer, TIMER_BOTH);
      switch_pressed = false;
      break;
    case GREEN: // If I am here it means I finished my green period
      tf_ped.cur_color = YELLOW;
      set_tf_color(tf_ped, YELLOW);
      TimerLoadSet(tf_ped.timer, TIMER_BOTH, YELLOW_PERIOD);
      break;
  }
}

void Switch_Handler() {
  GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
  switch_pressed = true;
  // Disable the timers of both tf1 and tf2
  TimerDisable(tf1.timer, TIMER_BOTH);
  TimerDisable(tf2.timer, TIMER_BOTH);
  // set both traffic light to red
  set_tf_color(tf1, RED);
  set_tf_color(tf2, RED);
  // set pedestrian traffic light to green
  set_tf_color(tf_ped, GREEN);
  tf_ped.cur_color = RED; 
  TimerInit(tf_ped.timer, Timer2_Handler, SYSCTL_PERIPH_TIMER2, period_3); // Intialize Timer2 with period_3
}

void TrafficInit() {
  portsInit(); // Used ports intialization
  __asm("CPSID I"); // Disable all interrupts
  GPIOIntUnregister(GPIO_PORTF_BASE); // unregister interrupts for portf as a precaution
  GPIOIntRegister(GPIO_PORTF_BASE, Switch_Handler); // Set Switch_handler as the interrupt handler for portf
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0); // Enable interrupts for pin0 of portf
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_RISING_EDGE); // Make interrupts happen with rising edge
	IntEnable(INT_GPIOF_TM4C123); // Enable CPU interrupts
  IntMasterEnable();
  TimerInit(tf1.timer, Timer0_Handler, SYSCTL_PERIPH_TIMER0, period_1); // Intialize Timer0 with period_1
  TimerInit(tf2.timer, Timer1_Handler, SYSCTL_PERIPH_TIMER1, period_2); // Intialize Timer1 with period_2
  __asm("CPSIE I"); // Enable all interrupts
  while(1) {
    if(switch_pressed) {
      BcdWrite(bcd_ped, tf_ped.timer, true);
    } else {
      BcdWrite(bcd1, tf1.timer, false);
      BcdWrite(bcd2, tf2.timer, false);
    }
  }
}

/*
  Function that handles the timers of each traffic light
*/
void Traffic_Handler(Traffic *tf) {
  TimerIntClear(tf->timer, TIMER_BOTH);
  if(switch_pressed) {
    set_tf_color(*tf, RED);
  } else {
    switch(tf->cur_color) {
      case RED: // If I am here it means I finished my red period
        tf->cur_color = GREEN;
        set_tf_color(*tf, GREEN);
        TimerLoadSet(tf->timer, TIMER_BOTH, GREEN_PERIOD);
        break;
      case YELLOW: // If I am here it means I finished my yellow period
        tf->cur_color = RED;
        set_tf_color(*tf, RED);
        TimerLoadSet(tf->timer, TIMER_BOTH, RED_PERIOD);
        break;
      case GREEN: // If I am here it means I finished my green period
        tf->cur_color = YELLOW;
        set_tf_color(*tf, YELLOW);
        TimerLoadSet(tf->timer, TIMER_BOTH, YELLOW_PERIOD);
        break;
    }
  }
}

/*
  A function that takes a bcd(decoder) and a timer and flag ped which states if the bcd is a pedestrian bcd or not,
  and the function writes the current value of the timer in the right pins of the right port
*/
void BcdWrite(Bcd bcd, uint32_t timer, bool ped) {
  // n is the current value of the timer, we add one because we don't want 0 indexing
  uint8_t n = (TimerValueGet(timer, TIMER_A) / TIVA_CLK) + 1; 
  int bin[4]; // An array that will contain the binary representation of the current value of the timer in seconds
  // treat pedestrian as a special case because it contains pins in two different ports 3 in A and 1 in E
  if(ped) {
    // loop to get the binary representation of current timer
    for(int i = 0; i < 4; i++) {
      bin[i] = n % 2;
      n /= 2;
    }
    DIO_WritePin(&GPIO_PORTA_DATA_R, bcd.A, bin[0]);
    DIO_WritePin(&GPIO_PORTA_DATA_R, bcd.B, bin[1]);
    DIO_WritePin(&GPIO_PORTA_DATA_R, bcd.C, bin[2]);
    DIO_WritePin(&GPIO_PORTE_DATA_R, bcd.C, bin[3]);
  }
  else {
    for(int i = 0; i < 4; i++) {
      bin[i] = n % 2;
      n /= 2;
    }
    GPIOPinWrite(bcd.port, 0xFF, ((bin[0]) << bcd.A) | ((bin[1]) << bcd.B) | (bin[2] << bcd.C) | (bin[3] << bcd.D));
  }
}
