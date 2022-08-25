#include <stdint.h>
#include <stdbool.h>
#include "tivaware.h"

#define TIVA_CLK      16e6 //16MHz clock
#define GREEN_PERIOD  TIVA_CLK * 5 // 5 seconds
#define YELLOW_PERIOD TIVA_CLK * 2 // 2 seconds
#define RED_PERIOD    TIVA_CLK * 7 // 7 seconds
#define RED           1
#define YELLOW        2
#define GREEN         3


typedef struct Bcd{
  uint32_t port;
  uint8_t A;
  uint8_t B;
  uint8_t C;
  uint8_t D;
} Bcd;

typedef struct Traffic{
  uint8_t  cur_color;
  uint32_t port;
  uint8_t  red;
  uint8_t  yellow;
  uint8_t  green;
  uint32_t timer;
} Traffic;

extern Traffic tf1;
extern Traffic tf2;
extern Traffic tf_ped;

extern Bcd bcd1;
extern Bcd bcd2;
extern Bcd bcd_ped;

extern bool switch_pressed;


extern uint32_t period_1;
extern uint32_t period_2;
extern uint32_t period_3;

void TrafficInit();
void Traffic_Handler(Traffic *tf);
void set_tf_color(Traffic tf, uint8_t color);
void PortInit(uint32_t port, uint32_t clk, uint32_t input, uint32_t output);
void TimerInit(uint32_t timer, void(*timer_handler)(), uint32_t clk, uint32_t delay);
void BcdWrite(Bcd bcd, uint32_t timer, bool ped);
