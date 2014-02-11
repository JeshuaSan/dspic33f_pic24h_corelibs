#ifndef TIMER1_H
#define	TIMER1_H

#include <stdint.h>

enum TIMER
{
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5
};

void timer_init(enum TIMER timer);
void timer_start(enum TIMER timer);
void timer_stop(enum TIMER timer);
void timer_set_ms(enum TIMER timer, uint16_t ms);
void timer_set_us(enum TIMER timer,uint16_t us);

#endif	/* TIMERS_H */

