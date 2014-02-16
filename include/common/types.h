#ifndef TYPES_H
#define	TYPES_H

#include <stdint.h>

// Volatile types
typedef volatile int8_t     vint8_t;
typedef volatile uint8_t    vuint8_t;
typedef volatile int16_t    vint16_t;
typedef volatile uint16_t   vuint16_t;
typedef volatile int32_t    vint32_t;
typedef volatile uint32_t   vuint32_t;
typedef volatile int64_t    vint64_t;
typedef volatile uint64_t   vuint64_t;

// Interrupt types
#define _ISR_NOPSV __attribute__ ((interrupt, no_auto_psv))

#endif  /* TYPES_H */