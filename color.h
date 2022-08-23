#include "tivaware.h"


#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define RED_TF1 1
#define YELLOW_TF1 2
#define GREEN_TF1 3
#define RED_TF2 4
#define YELLOW_TF2 5
#define GREEN_TF2 6
#define RED_TF3 7
#define YELLOW_TF3 8
#define GREEN_TF3 9
#define PORTF GPIO_PORTF_DATA_R
// #define RED 1
// #define BLUE 2
// #define GREEN 3
// #define MAGENTA 4
// #define CYAN 5
// #define YELLOW 6
// #define WHITE 7


void set_color(uint8_t color);

// void toggle_color(uint8_t color);

void reset_color();


