#include "trafficlight.h"

uint32_t period_1   = RED_PERIOD;
uint32_t period_2   = GREEN_PERIOD;
uint32_t period_3   = RED_PERIOD;
bool switch_pressed = false;


Traffic tf1    =    {YELLOW, GPIO_PORTA_BASE, 2, 3, 4, 0};
Traffic tf2    =    {RED   , GPIO_PORTF_BASE, 1, 2, 3, 0};
Traffic tf_ped =    {RED   , GPIO_PORTB_BASE, 5, 4, 1, 0};

int main()
{
  TrafficInit();
}
