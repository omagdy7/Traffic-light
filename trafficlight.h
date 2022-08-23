#include <stdint.h>
#include <stdbool.h>
#include "tivaware.h"
#include "color.h"

#define TIVA_CLK 16e6
#define GREEN_PERIOD TIVA_CLK * 5
#define YELLOW_PERIOD TIVA_CLK * 2
#define RED_PERIOD TIVA_CLK * 7


typedef struct Traffic{
  uint8_t  cur_color;
  uint32_t port;
  uint8_t  red;
  uint8_t  yellow;
  uint8_t  green;
} Traffic;

extern Traffic tf1;
extern Traffic tf2;

void set_tf_color(Traffic tf, uint8_t color);
void PortInit(uint32_t port, uint32_t clk);
void TimerInit(uint32_t timer, void(*timer_handler)(), uint32_t clk, uint32_t delay);
