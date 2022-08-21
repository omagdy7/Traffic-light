#include "tm4c123gh6pm.h"
#include "Bitwise_operations.h"
#include <stdint.h>

#define DIROFF 0x400 / 4
#define PUROFF 0x510 / 4
#define POROFF 0x514 / 4
#define DENOFF 0x51c / 4
#define LOCKOFF 0x520 / 4
#define COMMITOFF 0x524 / 4

#define PORTF GPIO_PORTF_DATA_R
#define RIGHT_SWITCH !DIO_ReadPin(&PORTF, 0)
#define LEFT_SWITCH !DIO_ReadPin(&PORTF, 4)
#define BOTH_SWITCHES RIGHT_SWITCH && LEFT_SWITCH
#define DELAY 10000


void DIO_Init(char port, unsigned int dir, unsigned int pur);
void DIO_WritePin(volatile uint32_t* port, unsigned int pin, unsigned int value);
void DIO_WritePort(volatile uint32_t* port, unsigned int value);
int DIO_ReadPin(volatile uint32_t* port, unsigned int pin);
uint32_t DIO_ReadPort(volatile uint32_t port);
void delay(int value);

