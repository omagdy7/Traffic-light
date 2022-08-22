#include "color.h"
#include "stdio.h"
#include <stdint.h>

int cnt = 1;
#define GREEN_PERIOD 80000000
#define YELLOW_PERIOD 48000000
#define RED_PERIOD 16000000
uint8_t cur_color = GREEN;
uint32_t period = GREEN_PERIOD;




void Timer0_Handler() {
  TimerIntClear(TIMER0_BASE, TIMER_BOTH);
  switch(cur_color) {
    case RED: 
      cur_color = GREEN;
      set_color(cur_color);
      TimerLoadSet(TIMER0_BASE, TIMER_BOTH, GREEN_PERIOD);
      break;
    case YELLOW: 
      cur_color = RED;
      set_color(cur_color);
      TimerLoadSet(TIMER0_BASE, TIMER_BOTH, RED_PERIOD);
      break;
    case GREEN: 
      cur_color = YELLOW;
      set_color(cur_color);
      TimerLoadSet(TIMER0_BASE, TIMER_BOTH, YELLOW_PERIOD);
      break;
  }
}

void portFInit() {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {};
  GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPadConfigSet (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
  GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}
void traffic_delay() {
  portFInit();
  reset_color();
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}
  TimerDisable(TIMER0_BASE, TIMER_BOTH);
  TimerConfigure(TIMER0_BASE, (TIMER_CFG_PERIODIC));
  TimerLoadSet(TIMER0_BASE, TIMER_BOTH, period);
  TimerIntUnregister(TIMER0_BASE, TIMER_BOTH);
  TimerEnable(TIMER0_BASE, TIMER_BOTH);
  set_color(GREEN);
  TimerIntRegister(TIMER0_BASE, TIMER_BOTH, (*Timer0_Handler));
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT);
  while(1) {

  }

}

int main()
{
  traffic_delay();
}
