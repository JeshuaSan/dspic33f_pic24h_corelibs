#include "peripheral/timer.h"
#include "common/globals.h"
#include <xc.h>

/* TxCON:TON<15> => Timer enable/disable*/
#define TMR_ON(tcon)       BIT_SET(tcon, 15)            // TON = 1  Enable Timer
#define TMR_OFF(tcon)      BIT_CLR(tcon, 15)            // TON = 0  Disable Timer

/* TxCON:TCKPS<5:4> => Prescaler value */
#define TMR_PRES_256(tcon) BITMASK_SET(tcon, 0x0030)    // TCKPS = 0b11 1:256 prescaler
#define TMR_PRES_1(tcon)   BITMASK_CLR(tcon, 0x0030)    // TCKPS = 0b00 1:1 prescaler

/* Computes the timer period in [ms] using a prescaler of 256 and TCY[ns] */
#define TMR_PR_MS(ms)  (ms * (1000000U / (TCY * 256U)))
/* Computes the timer period in [us] using a prescaler of 1 and TCY[ns] */
#define TMR_PR_US(us)  (us * (1000U / TCY))



static uint8_t timerINTF[] = {TMR1_INT, TMR2_INT, TMR3_INT, TMR4_INT, TMR5_INT};

typedef volatile uint16_t vuint16_t;
typedef vuint16_t* sfr_t;

static sfr_t timerCON[] = {&T1CON, &T2CON, &T3CON, &T4CON, &T5CON};
static sfr_t timerPR[] = {&PR1, &PR2, &PR3, &PR4, &PR5};
static sfr_t timerTMR[] = {&TMR1, &TMR2, &TMR3, &TMR4, &TMR5};

void timer_init(enum TIMER timer)
{
    // Set timer all registers to 0
    if (timer < (TIMER5+1))             // Timer1 to Timer5
    {
        *timerCON[timer] = 0x0000;
        *timerPR[timer] = 0x0000;
        *timerTMR[timer] = 0x0000;
    }
}

void timer_set_ms(enum TIMER timer, uint16_t ms)
{
    // Set prescaler value to 256
    TMR_PRES_256(*timerCON[timer]);

    // ms max value is 400
    if (ms > 400U)
    {
        ms = 400U;
    }

    *timerTMR[timer] = 0x0000;          // Clear TMR register
    *timerPR[timer] = TMR_PR_MS(ms);    // Period (ms)
}

void timer_set_us(enum TIMER timer, uint16_t us)
{
    // Set prescaler value to 1
    TMR_PRES_1(*timerCON[timer]);

    if (us > 999U)                      // us max value is 999
    {
        us = 999U;
    }

    *timerTMR[timer] = 0x0000;          // Clear TMR register
    *timerPR[timer] = TMR_PR_US(us);    // Period (us)
}

void timer_start(enum TIMER timer)
{
    // Set TON bit of TCON register
    TMR_ON(*timerCON[timer]);

    // Clear interrupt flag and enable timer interrupt
    if (timer < TIMER4)
    {
        BIT_CLR(IFS0, timerINTF[timer] );
        BIT_SET(IEC0, timerINTF[timer] );
    }
    else
    {
        BIT_CLR(IFS1, timerINTF[timer] );
        BIT_SET(IEC1, timerINTF[timer] );
    }
}

void timer1_stop(enum TIMER timer)
{
    // Clear TON bit of TCON register
    TMR_OFF(*timerCON[timer]);

    // Clear and disable timer interrupt
    if (timer < TIMER4)
    {
        BIT_CLR(IFS0, timerINTF[timer] );
        BIT_CLR(IEC0, timerINTF[timer] );
    }
    else
    {
        BIT_CLR(IFS1, timerINTF[timer] );
        BIT_CLR(IEC1, timerINTF[timer] );
    }
}
