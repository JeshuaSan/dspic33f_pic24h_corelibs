#ifndef ADC_H
#define ADC_H

#include <stdint.h>

enum ADCPORT
{
    AN0,
    AN1,
    AN2,
    AN3,
    AN4,
    AN5
};

void adc_init(enum ADCPORT adcPortA, enum ADCPORT adcPortB);
void adc_start(void);
void adc_stop(void);
uint16_t adc_read(enum ADCPORT adcPort);

#endif  /* ADC_H */

