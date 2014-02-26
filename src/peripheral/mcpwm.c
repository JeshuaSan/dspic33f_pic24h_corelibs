#include "peripheral/mcpwm.h"

/* Private prototypes *********************************************************/
static void mcpwm_configReg();
static inline void mcpwm_setFreq(uint16_t freq);

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


}

/* Private functions **********************************************************/
static inline void mcpwm_setFreq(uint16_t freq)
{

}