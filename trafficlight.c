#include "trafficlight.h"

void PortInit(uint32_t port, uint32_t clk) {
  uint32_t pins = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
  SysCtlPeripheralEnable(clk);
  while(!SysCtlPeripheralReady(clk)) {};
  GPIOUnlockPin(port, pins);
  GPIOPinTypeGPIOInput(port, GPIO_PIN_0);
  GPIOPinTypeGPIOOutput(port, pins);
  GPIOPadConfigSet (port, GPIO_PIN_0 | GPIO_PIN_4 | GPIO_PIN_5, 
  GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}



void TimerInit(uint32_t timer, void(*timer_handler)(), uint32_t clk, uint32_t delay) {
  reset_color();
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


