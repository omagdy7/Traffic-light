#include "color.h"
#include <stdint.h>

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

void set_color(uint8_t color) {
	switch (color) {
		case RED:
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x2);
			break;
		case BLUE:
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x4);
			break;
		case GREEN:
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x8);
			break;
		case WHITE:
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0xe);
			break;
	}
}

void toggle_color(uint8_t color) {
	switch (color) {
		case RED:
      GPIO_PORTF_DATA_R ^= LED_RED;
			break;
		case BLUE:
      GPIO_PORTF_DATA_R ^= LED_BLUE;
			break;
		case GREEN:
      GPIO_PORTF_DATA_R ^= LED_GREEN;
			break;
		case WHITE:
      GPIO_PORTF_DATA_R ^= (LED_RED | LED_BLUE | LED_GREEN);
			break;
	}
}

void reset_color() {
	PORTF &= 0x11;
}
