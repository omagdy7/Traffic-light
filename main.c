#include "trafficlight.h"

uint32_t period_1   = RED_PERIOD;
uint32_t period_2   = GREEN_PERIOD;
uint32_t period_3   = GREEN_PERIOD;
bool switch_pressed = false;

//Traffics
Traffic tf1    =    {RED   , GPIO_PORTA_BASE, 2, 3, 4};
Traffic tf2    =    {YELLOW, GPIO_PORTF_BASE, 1, 2, 3};
Traffic tf_ped =    {RED   , GPIO_PORTB_BASE, 5, 0, 7};

//Decoders
Bcd bcd1       =    {GPIO_PORTE_BASE, 1, 2, 3, 5};
Bcd bcd2       =    {GPIO_PORTD_BASE, 1, 2, 3, 6};
Bcd bcd_ped    =    {GPIO_PORTA_BASE, 5, 6, 7, 4}; // (5, 6, 7) A and 4 of E

int main()
{
  TrafficInit();
  // PortInit(GPIO_PORTE_BASE, SYSCTL_PERIPH_GPIOE, 0x0, 0xFF); // Initialize porta
  // GPIOPinWrite(GPIO_PORTE_BASE, 0xFF, 0);
  // GPIOPinWrite(GPIO_PORTE_BASE, 0xFF, (1 << 1) | (1 << 2));
}
