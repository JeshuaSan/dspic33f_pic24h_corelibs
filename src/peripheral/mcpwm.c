#include "peripheral/mcpwm.h"
#include "common/globals.h"
#include "common/types.h"

/* Private prototypes *********************************************************/
static void mcpwm_configReg();
static void mcpwm_setFreq(uint16_t freq);

/* Public functions ***********************************************************/
void mcpwm_init(uint16_t freq)
{
    mcpwm_configReg();
    mcpwm_setFreq(freq);
}

void mcpwm_setDC(enum MC_PWM reg, uint16_t dutycycle)
{
    vuint16_t *dc[] = {&P1DC1, &P1DC2};
    *dc[reg] = dutycycle;
}

void mcpwm_setDCPC(enum MC_PWM reg, uint16_t dutycyclePC) {
    vuint32_t maxDC = (P1TPER + 1) * 2;
    uint32_t dutycycle = (maxDC * dutycyclePC) / 100;
    mcpwm_setDC(reg, dutycycle);
}

void mcpwm_start(void)
{
    BIT_SET(P1TCON, 15);
}

void mcpwm_stop(void)
{
    BIT_CLR(P1TCON, 15);
}


/* Private functions **********************************************************/
static void mcpwm_configReg()
{
    P1TCON =
            (0U << 15)  |   /* PTEN = 0     PWM time base is off */
                                            // bit 14 unimplemented
            (0U << 13)  |   /* PTSDL = 0    PWM time base runs in CPU idle mode */
                                            // bit <12:8> uimplemented
            (0U << 4)   |   /* PTOPS<7:4> = 0   1:1 postscale */
            (0U << 2)   |   /* PTCKPS<3:2> = 0  1:1 prescale */
            (0U << 0);      /* PTMOD<1:0> = 0   PWM time base operates in Free-running mode */

    PWM1CON1 =
                                            // bit <15:11> unimplemented
            (0U << 10)  |   /* PMOD3 = 0    PWM I/O pin is in the Complementary Output mode */
            (0U << 9)   |   /* PMOD2 = 0    PWM I/O pin is in the Complementary Output mode */
            (0U << 8)   |   /* PMOD1 = 0    PWM I/O pin is in the Complementary Output mode */
                                            // bit 7 unimplemented
            (0U << 6)   |   /* PEN3H = 0    PWM3H pin disabled. I/O pin is general purpose */
            (1U << 5)   |   /* PMO2H = 1    PWM2H pin is enabled for PWM output */
            (1U << 4)   |   /* PMO1H = 1    PWM1H pin is enabled for PWM output */
                                            // bit 3 unimplemented
            (0U << 2)   |   /* PEN3L = 0    PWM3H pin disabled. I/O pin is general purpose */
            (1U << 1)   |   /* PMO2L = 1    PWM2L pin is enabled for PWM output */
            (1U << 0);      /* PMO1L = 1    PWM1L pin is enabled for PWM output */

    PWM1CON2 =
                                            // bit <15:12> uinimplemented
            (0U << 8)   |   /* SECPOS<11:8> = 0     1:1 postscale */
                                            // bit <7:3> unimplemented
            (1U << 2)   |   /* IUE = 1      Updates to the active PxDC registers are inmediate */
            (1U << 1)   |   /* OSYNC = 1    Output overrides via the RxOVDCON register are synchronized to the PWM time base */
            (0U << 0);      /* UDIS = 0     Updates from Duty Cycle and Period Buffer registers are enabled */

}
static void mcpwm_setFreq(uint16_t freq)
{
    // PxTPER = (FCY/(freq * PTCKPS)) - 1
    // PTCKPS = 1
    uint16_t ptper = (FCY/(uint32_t)freq) - 1;
    P1TPER = ptper;
}
