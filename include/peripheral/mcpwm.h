#ifndef MCPWM_H
#define	MCPWM_H

#include <xc.h>
#include <stdint.h>

enum MC_PWM
{
    MC_PWM1,
    MC_PWM2
};

void mcpwm_init(uint16_t freq);
void mcpwm_start(void);
void mcpwm_stop(void);
void mcpwm_setDC(enum MC_PWM reg, uint16_t dutycycle);
void mcpwm_setDCPC(enum MC_PWM reg, uint16_t dutycycle);

#endif	/* MCPWM_H */

