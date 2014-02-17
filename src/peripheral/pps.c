#include "peripheral/pps.h"

//void pps_unlock()
//{
//    __builtin_write_OSCCONL(OSCCON & 0xbf);
//}

static inline void pps_mapRP0(uint8_t peripheral);
static inline void pps_mapRP1(uint8_t peripheral);
static inline void pps_mapRP2(uint8_t peripheral);
static inline void pps_mapRP3(uint8_t peripheral);
static inline void pps_mapRP4(uint8_t peripheral);
static inline void pps_mapRP5(uint8_t peripheral);
static inline void pps_mapRP6(uint8_t peripheral);
static inline void pps_mapRP7(uint8_t peripheral);
static inline void pps_mapRP8(uint8_t peripheral);
static inline void pps_mapRP9(uint8_t peripheral);
static inline void pps_mapRP10(uint8_t peripheral);
static inline void pps_mapRP11(uint8_t peripheral);
static inline void pps_mapRP12(uint8_t peripheral);
static inline void pps_mapRP13(uint8_t peripheral);
static inline void pps_mapRP14(uint8_t peripheral);
static inline void pps_mapRP15(uint8_t peripheral);
static inline void pps_mapRP16(uint8_t peripheral);
static inline void pps_mapRP17(uint8_t peripheral);
static inline void pps_mapRP18(uint8_t peripheral);
static inline void pps_mapRP19(uint8_t peripheral);
static inline void pps_mapRP20(uint8_t peripheral);
static inline void pps_mapRP21(uint8_t peripheral);
static inline void pps_mapRP22(uint8_t peripheral);
static inline void pps_mapRP23(uint8_t peripheral);
static inline void pps_mapRP24(uint8_t peripheral);
static inline void pps_mapRP25(uint8_t peripheral);

void pps_mapRP(uint8_t pin, uint8_t peripheral)
{
    static void (* const pps_map[])(uint8_t peripheral) =
    {pps_mapRP0, pps_mapRP1, pps_mapRP2, pps_mapRP3, pps_mapRP4, pps_mapRP5,
     pps_mapRP6, pps_mapRP7, pps_mapRP8, pps_mapRP9, pps_mapRP10, pps_mapRP11,
     pps_mapRP12, pps_mapRP13, pps_mapRP14, pps_mapRP15, pps_mapRP16, pps_mapRP17,
     pps_mapRP18, pps_mapRP19, pps_mapRP20, pps_mapRP21, pps_mapRP22, pps_mapRP23,
     pps_mapRP24, pps_mapRP25};

    pps_map[pin](peripheral);
}

/* Private functions **********************************************************/
static inline void pps_mapRP0(uint8_t peripheral)
{
    RPOR0 |= (peripheral << 0);
}

static inline void pps_mapRP1(uint8_t peripheral)
{
    RPOR0 |= (peripheral << 8);
}

static inline void pps_mapRP2(uint8_t peripheral)
{
    RPOR1 |= (peripheral << 0);
}

static inline void pps_mapRP3(uint8_t peripheral)
{
    RPOR1 |= (peripheral << 8);
}

static inline void pps_mapRP4(uint8_t peripheral)
{
    RPOR2 |= (peripheral << 0);
}

static inline void pps_mapRP5(uint8_t peripheral)
{
    RPOR2 |= (peripheral << 8);
}

static inline void pps_mapRP6(uint8_t peripheral)
{
    RPOR3 |= (peripheral << 0);
}

static inline void pps_mapRP7(uint8_t peripheral)
{
    RPOR3 |= (peripheral << 8);
}

static inline void pps_mapRP8(uint8_t peripheral)
{
    RPOR4 |= (peripheral << 0);
}

static inline void pps_mapRP9(uint8_t peripheral)
{
    RPOR4 |= (peripheral << 8);
}

static inline void pps_mapRP10(uint8_t peripheral)
{
    RPOR5 |= (peripheral << 0);
}

static inline void pps_mapRP11(uint8_t peripheral)
{
//    RPOR5 |= (peripheral << 8);
    RPOR5 |= (0x00FF | (peripheral << 8) );
}

static inline void pps_mapRP12(uint8_t peripheral)
{
    RPOR6 |= (peripheral << 0);
}

static inline void pps_mapRP13(uint8_t peripheral)
{
    RPOR6 |= (peripheral << 8);
}

static inline void pps_mapRP14(uint8_t peripheral)
{
    RPOR7 |= (peripheral << 0);
}

static inline void pps_mapRP15(uint8_t peripheral)
{
    RPOR7 |= (peripheral << 8);
}

static inline void pps_mapRP16(uint8_t peripheral)
{
    RPOR8 |= (peripheral << 0);
}

static inline void pps_mapRP17(uint8_t peripheral)
{
    RPOR8 |= (peripheral << 8);
}

static inline void pps_mapRP18(uint8_t peripheral)
{
    RPOR9 |= (peripheral << 0);
}

static inline void pps_mapRP19(uint8_t peripheral)
{
    RPOR9 |= (peripheral << 8);
}

static inline void pps_mapRP20(uint8_t peripheral)
{
    RPOR10 |= (peripheral << 0);
}

static inline void pps_mapRP21(uint8_t peripheral)
{
    RPOR10 |= (peripheral << 8);
}

static inline void pps_mapRP22(uint8_t peripheral)
{
    RPOR11 |= (peripheral << 0);
}

static inline void pps_mapRP23(uint8_t peripheral)
{
    RPOR11 |= (peripheral << 8);
}

static inline void pps_mapRP24(uint8_t peripheral)
{
    RPOR12 |= (peripheral << 0);
}

static inline void pps_mapRP25(uint8_t peripheral)
{
    RPOR12 |= (peripheral << 8);
}
