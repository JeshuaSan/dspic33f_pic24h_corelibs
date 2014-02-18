#ifndef QEI_H
#define	QEI_H

#include <stdint.h>


enum QEI
{
    QEI1,
    QEI2
};

enum QEI_MODE
{
    QEI_2X_INDEX = 4,   /* QEIM<10:8> = 4   QEI 2x mode, reset by index pulse */
    QEI_2X_MATCH,       /* QEIM<10:8> = 5   QEI 2x mode, reset by match (MAXxCNT) */
    QEI_4X_INDEX,       /* QEIM<10:8> = 6   QEI 4x mode, reset by index pulse */
    QEI_4X_MATCH        /* QEIM<10:8> = 7   QEI 4x mode, reset by match (MAXxCNT) */
};

void qei_init(enum QEI qei, uint8_t a, uint8_t b, enum QEI_MODE md);
void qei_setMode(enum QEI qei, enum QEI_MODE md);
uint16_t qei_getCNT(enum QEI qei);
#endif	/* QEI_H */