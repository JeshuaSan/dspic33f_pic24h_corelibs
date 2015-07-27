#ifndef SYSCONFIG_H
#define	SYSCONFIG_H

#include "pinconfig.h"
#include "common/globals.h"
#include "common/types.h"

enum
{
    SYSTICK_1MS,
    SYSTICK_10MS,
    SYSTICK_100MS,
    SYSTICK_1000MS
};

extern vuint8_t _sysTick;

void sys_init(void);

#endif	/* SYSCONFIG_H */

