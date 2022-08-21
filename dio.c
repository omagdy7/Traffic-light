#include "dio.h"

void DIO_Init(char port, unsigned int dir, unsigned int pur) {
  unsigned int off = port - 'A';
  SYSCTL_RCGCGPIO_R |= 1 << off;
  while(SYSCTL_RCGCGPIO_R && (1 << off) == 0) {};
  unsigned int* address = (unsigned int*)(0x40004000 + (off * 0x1000));
  if (off >= 4) {
    address = (unsigned int*)(0x40024000 + ((off - 4) * 0x1000));
  }
  *(address + LOCKOFF) = 0x4C4F434B; // LOCK
  *(address + COMMITOFF) = 0x1F;
  *(address + PUROFF) = pur;  
  *(address + DENOFF) = 0x1F;  
  *(address + DIROFF) = dir;
}

void DIO_WritePin(volatile uint32_t* port, unsigned int pin, unsigned int value) {
  if(value) {
    SET(port, pin);
  } else {
    RESET(port, pin);
  }
}

void DIO_WritePort(volatile uint32_t* port, unsigned int value) {
  	*port = value;
}


int DIO_ReadPin(volatile uint32_t* port, unsigned int pin) {
	int x = GET_BIT(port, pin); 
	return x;
}

uint32_t DIO_ReadPort(volatile uint32_t port) {
	return port;
}

void delay(int value) {
  while(value--) {}
}

