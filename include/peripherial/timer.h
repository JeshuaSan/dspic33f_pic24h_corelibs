#ifndef TIMER1_H
#define TIMER1_H

#include <stdint.h>

/* Timer modules */
enum TIMER
{
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5
};

/* Timer interrupt flags and enable bits*/
#define TMR1_INT    3U
#define TMR2_INT    7U
#define TMR3_INT    8U
#define TMR4_INT    11U
#define TMR5_INT    12U

void timer_init(enum TIMER timer);
void timer_start(enum TIMER timer);
void timer_stop(enum TIMER timer);
void timer_set_ms(enum TIMER timer, uint16_t ms);
void timer_set_us(enum TIMER timer,uint16_t us);

#endif  /* TIMERS_H */

