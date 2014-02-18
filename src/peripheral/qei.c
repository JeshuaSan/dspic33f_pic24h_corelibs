#include "peripheral/qei.h"
#include "common/globals.h"
#include "common/types.h"
#include <pps.h>

/* Private protorypes *********************************************************/
static inline void qei_pins1(uint8_t a, uint8_t b);
static inline void qei_pins2(uint8_t a, uint8_t b);
static vuint16_t *qeiCON[] = {&QEI1CON, &QEI2CON};
static vuint16_t *qeiCNT[] = {&POS1CNT, &POS2CNT};

/* Main functions *************************************************************/
void qei_init(enum QEI qei, uint8_t a, uint8_t b, enum QEI_MODE md)
{
    static void(* qei_pins[])(uint8_t a, uint8_t b) = {qei_pins1, qei_pins2};

    
    qei_pins[qei](a, b);

    *qeiCON[qei] =
            (0U << 15)  |   /* CNTERR = 0   Position count error has not ocurred
                                            only applies when QEIM = 110 or 100 */
                            //              bit 14 unimplemented
            (0U << 13)  |   /* QEISDL = 0   Continue in idle */
                            /* INDEX        bit 12 read-only */
                            /* UPDN         bit 11 read-only when QEIM = 1xx */
            (md << 8)   |   /* QEIM<10:8> = mode */
            (0U << 7)   |   /* SWAPAB = 0   Phase A and phase B inputs are not swapped */
            (1U << 6)   |   /* PCDOUT = 1   QEI logic constrols state of I/O pins */
                            /* TQGATE       ignored on QEI mode */
                            /* TQCKPS<4:3>  ignored on QEI mode */
            (1U << 2);      /* POSRES = 1   Index pulse resets position counter
                                            applies only when QEIM = 100 or 110 */
}

void qei_setMode(enum QEI qei, enum QEI_MODE mode)
{

}

uint16_t qei_getCNT(enum QEI qei)
{
    return *qeiCNT[qei];
}

/* Private functions **********************************************************/

static inline void qei_pins1(uint8_t a, uint8_t b)
{
    // Map PPS pins to periphereal functions
    PPSUnLock;
    PPSInput(IN_FN_PPS_QEA1, a);
    PPSInput(IN_FN_PPS_QEB1, b);
    PPSLock;
}

static inline void qei_pins2(uint8_t a, uint8_t b)
{
    // Map PPS pins to periphereal functions
    PPSUnLock;
    PPSInput(IN_FN_PPS_QEA2, a);
    PPSInput(IN_FN_PPS_QEB2, b);
    PPSLock;
}