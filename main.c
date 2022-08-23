#include "trafficlight.h"

uint8_t cur_color_1 = RED_TF1;
uint8_t cur_color_2 = YELLOW_TF2;
uint32_t period_1 = RED_PERIOD;
uint32_t period_2 = GREEN_PERIOD;

void Timer0_Handler() {
  TimerIntClear(TIMER0_BASE, TIMER_BOTH);
  switch(cur_color_1) {
    case RED_TF1: 
      cur_color_1 = GREEN_TF1;
      set_color(cur_color_1);
      TimerLoadSet(TIMER0_BASE, TIMER_BOTH, GREEN_PERIOD);
      break;
    case YELLOW_TF1: 
      cur_color_1 = RED_TF1;
      set_color(cur_color_1);
      TimerLoadSet(TIMER0_BASE, TIMER_BOTH, RED_PERIOD);
      break;
    case GREEN_TF1: 
      cur_color_1 = YELLOW_TF1;
      set_color(cur_color_1);
      TimerLoadSet(TIMER0_BASE, TIMER_BOTH, YELLOW_PERIOD);
      break;
  }
}

void Timer1_Handler() {
  TimerIntClear(TIMER1_BASE, TIMER_BOTH);
  switch(cur_color_2) {
    case RED_TF2: 
      cur_color_2 = GREEN_TF2;
      set_color(cur_color_2);
      TimerLoadSet(TIMER1_BASE, TIMER_BOTH, GREEN_PERIOD);
      break;
    case YELLOW_TF2: 
      cur_color_2 = RED_TF2;
      set_color(cur_color_2);
      TimerLoadSet(TIMER1_BASE, TIMER_BOTH, RED_PERIOD);
      break;
    case GREEN_TF2: 
      cur_color_2 = YELLOW_TF2;
      set_color(cur_color_2);
      TimerLoadSet(TIMER1_BASE, TIMER_BOTH, YELLOW_PERIOD);
      break;
  }
}


int main()
{
  PortInit(GPIO_PORTF_BASE, SYSCTL_PERIPH_GPIOF); // Initialize portf
  PortInit(GPIO_PORTA_BASE, SYSCTL_PERIPH_GPIOA); // Initialize porta
  __asm("CPSID I"); // Disable all interrupts
  TimerInit(TIMER0_BASE, Timer0_Handler, SYSCTL_PERIPH_TIMER0, period_1); // Intialize Timer0 with period_1
  TimerInit(TIMER1_BASE, Timer1_Handler, SYSCTL_PERIPH_TIMER1, period_2); // Intialize Timer1 with period_2
  __asm("CPSIE I"); // Enable all interrupts
  while(1) {
    __asm("wfi"); // power saving mode
  }
}
