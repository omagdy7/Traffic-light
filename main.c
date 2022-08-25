#include "trafficlight.h"

uint32_t period_1   = RED_PERIOD; // Intial period of tf1
uint32_t period_2   = GREEN_PERIOD; // Intial period of tf2
uint32_t period_3   = 0; // Intial peroid of tf_ped

bool switch_pressed = false;

//Decoders
Bcd bcd1       =    {GPIO_PORTE_BASE, 1, 2, 3, 5};
Bcd bcd2       =    {GPIO_PORTD_BASE, 1, 2, 3, 6};
Bcd bcd_ped    =    {GPIO_PORTA_BASE, 5, 6, 7, 4}; // (5, 6, 7) A and 4 of E

//Traffics
Traffic tf1    =    {RED   , GPIO_PORTA_BASE, 2, 3, 4, TIMER0_BASE}; 
Traffic tf2    =    {YELLOW, GPIO_PORTF_BASE, 1, 2, 3, TIMER1_BASE};
Traffic tf_ped =    {RED   , GPIO_PORTB_BASE, 5, 0, 7, TIMER2_BASE};


int main()
{
  TrafficInit();
}
