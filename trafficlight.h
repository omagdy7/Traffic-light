#include <stdint.h>
#include <stdbool.h>
#include "color.h"
#include "dio.h"

#define TIVA_CLK 16e6
#define GREEN_PERIOD TIVA_CLK * 5
#define YELLOW_PERIOD TIVA_CLK * 2
#define RED_PERIOD TIVA_CLK * 7

void PortInit(uint32_t port, uint32_t clk);
void TimerInit(uint32_t timer, void(*timer_handler)(), uint32_t clk, uint32_t delay);
