#include "peripheral/ic.h"
#include "common/types.h"
#include "common/globals.h"
#include <xc.h>
#include <pps.h>
#include <stdint.h>

#define IC1F    1U
#define IC2F    5U
static uint8_t icINTF[] = {IC1F, IC2F};
static vuint16_t* icCON[] = {&IC1CON, &IC2CON, &IC7CON, &IC8CON};

static vuint16_t icPeriod[4];

/* Private funtions declaration ***********************************************/
static void ic_pins1(uint8_t icPin);
static void ic_pins2(uint8_t icPin);
static void ic_pins7(uint8_t icPin);
static void ic_pins8(uint8_t icPin);


/* Public funtions ************************************************************/
void ic_init(enum _IC ic, uint8_t icPin)
{
    static void(* ic_pinConfig[])(uint8_t icPin) = {ic_pins1, ic_pins2, ic_pins7, ic_pins8};

    // Configure pin
    ic_pinConfig[ic](icPin);

    // Configure register
    *icCON[ic] =
                                            // bit<15:14> unimplemented
            (0U << 13)  |   /* ICSIDL = 0   Input capture module continues on CPU idle */
                                            // bit<12:8> unimplemented
            (0U << 7)   |   /* ICTMR = 0    TMR3 contents are captured on capture event */
            (0U << 6)   |   /* ICI<6:5> = b01   Interrupt on every second */
            (1U << 5)   |   /*                  capture */
                            /* ICOV: Input capture overflow status bit (read-ony) */
                            /* ICBNE: Input capture buffer empty status bit (read-only) */
            (0U << 2)   |   /* ICM<2:0> = 0 Input capture module turned off */
            (0U << 1)   |
            (0U << 0);

    T3CON = 0x8030;        //Timer 3 operates with prescaler 1:256 and internal clock
}

void ic_start(enum _IC ic, enum _IC_MODE mode)
{
    BIT_CLR(IFS0, icINTF[ic]);
    BIT_SET(IEC0, icINTF[ic]);
    *icCON[ic] |= mode;      /* ICM<2:0>    Capture mode */
}

void ic_stop(enum _IC ic)
{
    BIT_CLR(IFS0, icINTF[ic]);
    BIT_CLR(IEC0, icINTF[ic]);
}

uint16_t ic_getPeriod(enum _IC ic)
{
    uint16_t period = icPeriod[ic];
//    icPeriod[ic] = 0;
    return period;
}
/* Private functions **********************************************************/

void _ISR_NOPSV _IC1Interrupt(void)
{
    vuint16_t period1 = IC1BUF;
    vuint16_t period2 = IC1BUF;

    if (period2 > period1)
    {
        icPeriod[0] = period2 - period1;
    }
    else
    {
        icPeriod[0] = (PR3 - period1) + period2;
    }

    BIT_CLR(IFS0, IC1F);
}

void _ISR_NOPSV _IC2Interrupt(void)
{
    vuint16_t period1 = IC2BUF;
    vuint16_t period2 = IC2BUF;
    if (period2 > period1)
    {
        icPeriod[1] = period2 - period1;
    }
    else
    {
        icPeriod[1] = (PR3 - period1) + period2;
    }

    BIT_CLR(IFS0, IC2F);
}

static void ic_pins1(uint8_t icPin)
{
    PPSUnLock;
    PPSInput(IN_FN_PPS_IC1, icPin);
    PPSLock;
}

static void ic_pins2(uint8_t icPin)
{
    PPSUnLock;
    PPSInput(IN_FN_PPS_IC2, icPin);
    PPSLock;
}

static void ic_pins7(uint8_t icPin)
{
    PPSUnLock;
    PPSInput(IN_FN_PPS_IC7, icPin);
    PPSLock;
}

static void ic_pins8(uint8_t icPin)
{
    PPSUnLock;
    PPSInput(IN_FN_PPS_IC8, icPin);
    PPSLock;
}