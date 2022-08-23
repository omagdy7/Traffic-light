#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/inc/hw_memmap.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/inc/hw_ints.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/driverlib/debug.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/driverlib/gpio.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/driverlib/sysctl.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/driverlib/systick.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/driverlib/timer.h"
#include "../../ti/TivaWare_C_Series-2.2.0.295/driverlib/interrupt.h"

#define RIGHT_SWITCH    !(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) != 0)
#define LEFT_SWITCH     !(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) != 0)
#define BOTH_SWITCHES   (RIGHT_SWITCH && LEFT_SWITCH)

