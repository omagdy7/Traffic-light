#include "trafficlight.h"

uint32_t period_1   = RED_PERIOD;
uint32_t period_2   = GREEN_PERIOD;
uint32_t period_3   = RED_PERIOD;

Traffic tf1    =    {RED   , GPIO_PORTF_BASE, 1, 2, 3, 0};
Traffic tf2    =    {YELLOW, GPIO_PORTA_BASE, 2, 3, 4, 0};
Traffic tf_ped =    {RED   , GPIO_PORTB_BASE, 5, 0, 1, 0};

void Switch_Handler() {

}

void Timer0_Handler() {
  TimerIntClear(TIMER0_BASE, TIMER_BOTH);
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

void Timer1_Handler() {
  TimerIntClear(TIMER1_BASE, TIMER_BOTH);
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

void Timer2_Handler() {
  TimerIntClear(TIMER2_BASE, TIMER_BOTH);
  switch(tf_ped.cur_color) {
    case RED: 
      tf_ped.cur_color = GREEN;
      set_tf_color(tf_ped, GREEN);
      TimerLoadSet(TIMER2_BASE, TIMER_BOTH, GREEN_PERIOD);
      break;
    case YELLOW: 
      tf_ped.cur_color = RED;
      set_tf_color(tf_ped, RED);
      TimerLoadSet(TIMER2_BASE, TIMER_BOTH, RED_PERIOD);
      break;
    case GREEN: 
      tf_ped.cur_color = YELLOW;
      set_tf_color(tf_ped, YELLOW);
      TimerLoadSet(TIMER2_BASE, TIMER_BOTH, YELLOW_PERIOD);
      break;
  }
}


int main()
{
  PortInit(GPIO_PORTF_BASE, SYSCTL_PERIPH_GPIOF); // Initialize portf
  PortInit(GPIO_PORTA_BASE, SYSCTL_PERIPH_GPIOA); // Initialize porta
  PortInit(GPIO_PORTB_BASE, SYSCTL_PERIPH_GPIOB); // Initialize portb
  __asm("CPSID I"); // Disable all interrupts
  TimerInit(TIMER0_BASE, Timer0_Handler, SYSCTL_PERIPH_TIMER0, period_1); // Intialize Timer0 with period_1
  TimerInit(TIMER1_BASE, Timer1_Handler, SYSCTL_PERIPH_TIMER1, period_2); // Intialize Timer1 with period_2
  TimerInit(TIMER2_BASE, Timer2_Handler, SYSCTL_PERIPH_TIMER2, period_3); // Intialize Timer1 with period_2
  __asm("CPSIE I"); // Enable all interrupts
  while(1) {
    __asm("wfi"); // power saving mode
  }
}
