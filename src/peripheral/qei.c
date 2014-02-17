#include "peripheral/qei.h"
#include "device/pinconfig.h"
#include "common/globals.h"
#include "common/types.h"
#include "peripheral/pps.h"


void qei_init(enum QEI qei)
{

    // Map PPS pins to periphereal functions
    PPS_UNLOCK();

    PPS_MAP_IN_QE1A(0);
    PPS_MAP_IN_QE1B(1);

    PPS_LOCK();
}