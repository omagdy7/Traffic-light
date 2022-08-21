#include "color.h"
#include "systick.h"
#include "stdio.h"

int cnt = 0;

void portFInit() {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {};
  GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPadConfigSet (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
  GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}

void toggle_white() {
  if((GPIO_PORTF_DATA_R & 0xe) == 0xe) {
    reset_color();
  } else {
    set_color(WHITE);
  }
}

void SysTick_Handler() {
  cnt++;
  if(cnt % 5 == 0) {
    toggle_color(WHITE);
  }
}

void toggle_interrupts() {
  portFInit();
  SysTickDisable();
  SysTickPeriodSet(PERIOD);
  SysTickIntEnable();
  SysTickEnable();
  while(1) {

  }
}

int main()
{
  toggle_interrupts();
}
