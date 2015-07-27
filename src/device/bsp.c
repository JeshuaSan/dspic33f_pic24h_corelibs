#include "device/bsp.h"
#include "peripheral/timer.h"
#include <xc.h>


static vuint32_t _tick[4] = {0};
vuint8_t _sysTick = 0;

static void sys_ConfigClock(void);
static void sys_ConfigPins(void);

void sys_init()
{
    sys_ConfigClock();
    sys_ConfigPins();

    timer_init(TIMER1);
    timer_set_ms(TIMER1, 1);
    timer_start(TIMER1);
}

static void sys_ConfigClock()
{
    /* Clock setup on " dsPIC33F/PC24 Family Reference Manual : 70186E Section 7. Oscillator " */

    /* Configure PLL prescaler, PLL post scaller, PLL divisor
     *  Fosc = Fin * ( M / (N1*N2) )
     *      N1 = PLLPRE + 2
     *      N2 = 2 * (PLLPOST + 1)
     *       M = PLLDIV + 2
     * 
     *     Fin = 7372800 [Hz]
     *  PLLPRE = 4
     *  PLLPOST = 0
     *  PLLDIV = 128
     *      N1 = 6
     *      N2 = 2
     *       M = 130
     * 
     *  Fosc = 7372800 * ( 130 / (6*2) )
     *       = 79872000
     * 
     *   Fcy = Fosc / 2 = 39936000 [Hz]
     */

    // PLLFBD: PLL Feedback Divisor Resgister
    PLLFBD = 128;           /* PLLDIV<8:0> = 128    M, PLL Multiplier */

    // CLKDIV: Clock Divisor Register
    CLKDIV = 
        (0U << 6)   |   /* PLLPOST<7:6> = 00    Output divided by 2
                           N2, PLL Postscaller */
        (4U << 0);      /* PLLPRE(4:0> = 4      Input divided by 6 
                           N1, PLL Prescaler */


    /* Initiate clock switch to Primary Oscillator with PLL (NOSc = 0b011) */
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);

#if !defined(_MPLAB_SIM)
    /* Wait fo clock switch to occur */
    while(OSCCONbits.COSC != 0x03);


    /* Wait for PLL to lock */
    while(OSCCONbits.LOCK != 1);
#endif
}

static void sys_ConfigPins()
{
    // All pins digital by default
    AD1PCFGL = 0xFFFF;        // All digital I/O

    LED_TRS = 0;
}

void _ISR_NOPSV _T1Interrupt(void)
{
    BIT_CLR(IFS0, TMR1_INT);        // Clear Timer1 interrupt flag

    BIT_SET(_sysTick, SYSTICK_1MS); // 1 ms

    if (++_tick[SYSTICK_10MS] > 10U)
    {
        BIT_SET(_sysTick, SYSTICK_10MS);    // 10 ms
        _tick[SYSTICK_10MS] = 0;

        if (++_tick[SYSTICK_100MS] > 10U)
        {
            BIT_SET(_sysTick, SYSTICK_100MS);   // 100 ms
            _tick[SYSTICK_100MS] = 0;

            if (++_tick[SYSTICK_1000MS] > 10U)
            {
                BIT_SET(_sysTick, SYSTICK_1000MS);  // 1000 ms
                BIT_TGL(LATA, 4);
                _tick[SYSTICK_1000MS] = 0;
            }
        }
    }
}
