#include "peripheral/mcpwm.h"
#include "common/globals.h"

/* Private prototypes *********************************************************/
static void mcpwm_configReg();
static void mcpwm_setFreq(uint16_t freq);

/* Public functions ***********************************************************/
void mcpwm_init(uint16_t freq)
{
    P1TCON =
            (0U << 15)  |   /* PTEM = 0     PWM time base is off */
                                            // bit 14 unimplemented
            (0U << 13)  |   /* PTSDL = 0    PWM time base runs in CPU idle mode */
                                            // bit <12:8> uimplemented
            (0U << 4)   |   /* PTOPS<7:4> = 0   1:1 postscale */
            (0U << 2)   |   /* PTCKPS<3:2> = 0  1:1 prescale */
            (0U << 0);      /* PTMOD<1:0> = 0   PWM time base operates in Free-running mode */

    mcpwm_setFreq(freq);
}

/* Private functions **********************************************************/
static void mcpwm_setFreq(uint16_t freq)
{
    // PxTPER = (FCY/(Fpwm * PxTMRPS)) - 1
    uint8_t mcpwmPTCKPS[] = {1,4,16,64};              // Posible prescaler values
    uint16_t ptckps = P1TCON;          // Actual prescaler value (P1TCON:PTCKPS<3:2>)
    uint8_t mcpwmTMRPS = mcpwmPTCKPS[ptckps];

    uint32_t pwmFreq = ((uint32_t)freq) * mcpwmTMRPS; // Freq * PxTMRPS
    uint16_t ptper = (FCY/pwmFreq) - 1;              // (FCY/Fpwm)-1

    P1TPER = ptper;
}