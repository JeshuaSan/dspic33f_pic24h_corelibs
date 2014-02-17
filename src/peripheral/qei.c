#include "peripheral/qei.h"
#include "device/pinconfig.h"
#include "common/globals.h"
#include "common/types.h"
#include <pps.h>


void qei_init(enum QEI qei)
{

    // Map PPS pins to periphereal functions
    PPSUnLock;
    PPSInput(IN_FN_PPS_QEA1, QE1_A);
    PPSInput(IN_FN_PPS_QEB1, QE1_B);
    PPSLock;
}