#include "device/sysconfig.h"
#include "device/pinconfig.h"
#include <xc.h>

static void sys_ConfigClock(void);
static void sys_ConfigPins(void);

void sys_init()
{
    sys_ConfigClock();
    sys_ConfigPins();
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


