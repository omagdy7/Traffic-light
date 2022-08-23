#include "color.h"
#include <stdint.h>


void set_color(uint8_t color) {
  uint32_t pins = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	switch (color) {
		case RED_TF1:
      GPIOPinWrite(GPIO_PORTF_BASE, pins, 0x2);
			break;
		case YELLOW_TF1:
      GPIOPinWrite(GPIO_PORTF_BASE, pins, 0x4);
			break;
		case GREEN_TF1:
      GPIOPinWrite(GPIO_PORTF_BASE, pins, 0x8);
			break;
		case RED_TF2:
      GPIOPinWrite(GPIO_PORTA_BASE, pins, 0x4);
			break;
		case YELLOW_TF2:
      GPIOPinWrite(GPIO_PORTA_BASE, pins, 0x8);
			break;
		case GREEN_TF2:
      GPIOPinWrite(GPIO_PORTA_BASE, pins, 0x10);
			break;
	}
}

// void toggle_color(uint8_t color) {
// 	switch (color) {
// 		case RED:
//       GPIO_PORTF_DATA_R ^= LED_RED;
// 			break;
// 		case BLUE:
//       GPIO_PORTF_DATA_R ^= LED_BLUE;
// 			break;
// 		case GREEN:
//       GPIO_PORTF_DATA_R ^= LED_GREEN;
// 			break;
// 		case WHITE:
//       GPIO_PORTF_DATA_R ^= (LED_RED | LED_BLUE | LED_GREEN);
// 			break;
// 	}
// }

void reset_color() {
	PORTF &= 0x11;
}
