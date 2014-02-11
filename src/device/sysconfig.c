#include "sysconfig.h"
#include <xc.h>
#include "pinconfig.h"

static void sys_ConfigClock(void);
static void sys_ConfigPins(void);

void sys_init()
{
    sys_ConfigClock();
    sys_ConfigPins();
}

static void sys_ConfigClock()
{
    _PLLPRE = 4;        // Prescale = PLLPRE + 2
    _PLLDIV = 128;      // Multiply = PLLDIV + 2
    _PLLPOST = 0;        // Postscale = 2 * (PLLPOST + 1)
}

static void sys_ConfigPins()
{
    // All pins digital by default
    AD1PCFGL = 0xFFFF;        // All digital I/O

    LED_TRS = 0;
}


