#ifndef IC_H
#define	IC_H

/* Input Capture
 *
 * Uses Timer 3
 */

#include <stdint.h>

enum _IC
{
    _IC_1,
    _IC_2,
    _IC_7,
    _IC_8
};

enum _IC_MODE
{
    _IC_OFF,
    _IC_EVERY_EDGE,
    _IC_EVERY_FALLING,
    _IC_EVERY_RISING,
    _IC_EVERY_4TH_RISING,
    _IC_EVERY_16TH_RISING,
    _IC_UNUSED,
    _IC_IC_AS_INTERRUPT_PIN
};

void ic_init(enum _IC ic, uint8_t icPin);
void ic_start(enum _IC ic, enum _IC_MODE mode);
void ic_stop(enum _IC ic);
uint16_t ic_getPeriod(enum _IC ic);

#endif	/* IC_H */

