#ifndef MCPWM_H
#define	MCPWM_H

#include <xc.h>
#include <stdint.h>

typedef enum 
{
    MC_PWM1,
    MC_PWM2
} eMC_PWM;

typedef enum _ePTCKPS
{
    PTCKPS_1,
    PTCKPS_4,
    PTCKPS_16,
    PTCKPS_64
} ePTCKPS;

void mcpwm_init(uint16_t freq, ePTCKPS ps);
void mcpwm_start(void);
void mcpwm_stop(void);
void mcpwm_setDC(eMC_PWM reg, uint16_t dutycycle);
void mcpwm_setDCPC(eMC_PWM reg, uint16_t dutycycle);

#endif	/* MCPWM_H */

