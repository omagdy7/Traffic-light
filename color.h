#include "tivaware.h"


#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define PORTF GPIO_PORTF_DATA_R
#define INTIAL_COLOR WHITE
#define RED 1
#define BLUE 2
#define GREEN 3
#define MAGENTA 4
#define CYAN 5
#define YELLOW 6
#define WHITE 7


void set_color(uint8_t color);

void toggle_color(uint8_t color);

void reset_color();


