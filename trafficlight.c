#include "trafficlight.h"

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

void Timer0_Handler() {
  TimerIntClear(TIMER0_BASE, TIMER_BOTH);
  if(switch_pressed) {
    set_tf_color(tf1, RED);
  } else {
    switch(tf1.cur_color) {
      case RED: 
        tf1.cur_color = GREEN;
        set_tf_color(tf1, GREEN);
        TimerLoadSet(TIMER0_BASE, TIMER_BOTH, GREEN_PERIOD);
        break;
      case YELLOW: 
        tf1.cur_color = RED;
        set_tf_color(tf1, RED);
        TimerLoadSet(TIMER0_BASE, TIMER_BOTH, RED_PERIOD);
        break;
      case GREEN: 
        tf1.cur_color = YELLOW;
        set_tf_color(tf1, YELLOW);
        TimerLoadSet(TIMER0_BASE, TIMER_BOTH, YELLOW_PERIOD);
        break;
    }
  }
}

void Timer1_Handler() {
  TimerIntClear(TIMER1_BASE, TIMER_BOTH);
  if(switch_pressed) {
    set_tf_color(tf2, RED);
  } else {
    switch(tf2.cur_color) {
      case RED: 
        tf2.cur_color = GREEN;
        set_tf_color(tf2, GREEN);
        TimerLoadSet(TIMER1_BASE, TIMER_BOTH, GREEN_PERIOD);
        break;
      case YELLOW: 
        tf2.cur_color = RED;
        set_tf_color(tf2, RED);
        TimerLoadSet(TIMER1_BASE, TIMER_BOTH, RED_PERIOD);
        break;
      case GREEN: 
        tf2.cur_color = YELLOW;
        set_tf_color(tf2, YELLOW);
        TimerLoadSet(TIMER1_BASE, TIMER_BOTH, YELLOW_PERIOD);
        break;
    }

  }
}

void Timer2_Handler() {
  TimerIntClear(TIMER2_BASE, TIMER_BOTH);
  switch(tf_ped.cur_color) {
    case RED: 
      tf_ped.cur_color = GREEN;
      set_tf_color(tf_ped, GREEN);
      TimerLoadSet(TIMER2_BASE, TIMER_BOTH, GREEN_PERIOD);
      break;
    case YELLOW: 
      set_tf_color(tf1, tf1.cur_color);
      set_tf_color(tf2, tf2.cur_color);
      set_tf_color(tf_ped, RED);
      TimerEnable(TIMER0_BASE, TIMER_BOTH);
      TimerEnable(TIMER1_BASE, TIMER_BOTH);
      switch_pressed = false;
      break;
    case GREEN: 
      tf_ped.cur_color = YELLOW;
      set_tf_color(tf_ped, YELLOW);
      TimerLoadSet(TIMER2_BASE, TIMER_BOTH, YELLOW_PERIOD);
      break;
  }
}

void Switch_Handler() {
  GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
  switch_pressed = true;
  tf1.prevPeriod = TimerValueGet(tf1.port, TIMER_A);
  tf2.prevPeriod = TimerValueGet(tf2.port, TIMER_A);
  TimerDisable(TIMER0_BASE, TIMER_BOTH);
  TimerDisable(TIMER1_BASE, TIMER_BOTH);
  set_tf_color(tf1, RED);
  set_tf_color(tf2, RED);
  set_tf_color(tf_ped, GREEN);
  tf_ped.cur_color = RED; 
  TimerInit(TIMER2_BASE, Timer2_Handler, SYSCTL_PERIPH_TIMER2, GREEN_PERIOD); // Intialize Timer2 with period_3
}

void TrafficInit() {
  PortInit(GPIO_PORTF_BASE, SYSCTL_PERIPH_GPIOF, 0x1, 0x7E); // Initialize portf
  PortInit(GPIO_PORTA_BASE, SYSCTL_PERIPH_GPIOA, 0x0, 0xFF); // Initialize porta
  PortInit(GPIO_PORTB_BASE, SYSCTL_PERIPH_GPIOB, 0x0, 0xFF); // Initialize portb
  __asm("CPSID I"); // Disable all interrupts
  GPIOIntUnregister(GPIO_PORTF_BASE);
  GPIOIntRegister(GPIO_PORTF_BASE, Switch_Handler);
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_RISING_EDGE);
	IntEnable(INT_GPIOF_TM4C123);
  IntMasterEnable();
  TimerInit(TIMER0_BASE, Timer0_Handler, SYSCTL_PERIPH_TIMER0, period_1); // Intialize Timer0 with period_1
  TimerInit(TIMER1_BASE, Timer1_Handler, SYSCTL_PERIPH_TIMER1, period_2); // Intialize Timer1 with period_2
  __asm("CPSIE I"); // Enable all interrupts
  while(1) {
    __asm("wfi"); // power saving mode
  }
}
