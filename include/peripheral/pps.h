#ifndef CPPS_H
#define	CPPS_H

#include <xc.h>
#include <stdint.h>

enum PPS_IN_RP
{
    PPS_IN_RP0,
    PPS_IN_RP1,
    PPS_IN_RP2,
    PPS_IN_RP3,
    PPS_IN_RP4,
    PPS_IN_RP5,
    PPS_IN_RP6,
    PPS_IN_RP7,
    PPS_IN_RP8,
    PPS_IN_RP9,
    PPS_IN_RP10,
    PPS_IN_RP11,
    PPS_IN_RP12,
    PPS_IN_RP13,
    PPS_IN_RP14,
    PPS_IN_RP15,
    PPS_IN_RP16,
    PPS_IN_RP17,
    PPS_IN_RP18,
    PPS_IN_RP19,
    PPS_IN_RP20,
    PPS_IN_RP21,
    PPS_IN_RP22,
    PPS_IN_RP23,
    PPS_IN_RP24,
    PPS_IN_RP25,
    PPS_IN_VSS = 31
};

// External interrupt
#define PPS_MAP_IN_INT1(pin)    ( RPINR0  |= (pin << 8) )
#define PPS_MAP_IN_INT2(pin)    ( RPINR1  |= (pin << 0) )

// Timer external clock
#define PPS_MAP_IN_T3CK(pin)    ( RPINR3  |= (pin << 8) )
#define PPS_MAP_IN_T2CK(pin)    ( RPINR3  |= (pin << 0) )
#define PPS_MAP_IN_T5CK(pin)    ( RPINR4  |= (pin << 8) )
#define PPS_MAP_IN_T4CK(pin)    ( RPINR4  |= (pin << 0) )

// Input Capture
#define PPS_MAP_IN_IC2(pin)     ( RPINR7  |= (pin << 8) )
#define PPS_MAP_IN_IC1(pin)     ( RPINR7  |= (pin << 0) )
#define PPS_MAP_IN_IC8(pin)     ( RPINR10 |= (pin << 8) )
#define PPS_MAP_IN_IC7(pin)     ( RPINR10 |= (pin << 0) )

// Output compare
#define PPS_MAP_IN_OCFA(pin)    ( RPINR11 |= (pin << 0) )
#define PPS_MAP_IN_FLTA1(pin)   ( RPINR12 |= (pin << 0) )
#define PPS_MAP_IN_FLTA2(pin)   ( RPINR13 |= (pin << 0) )

// Quadrature Encoder
#define PPS_MAP_IN_QE1B(pin)    ( RPINR14 |= (pin << 8) )
#define PPS_MAP_IN_QE1A(pin)    ( RPINR14 |= (pin << 0) )
#define PPS_MAP_IN_QE1I(pin)    ( RPINR15 |= (pin << 0) )
#define PPS_MAP_IN_QE2B(pin)    ( RPINR16 |= (pin << 8) )
#define PPS_MAP_IN_QE2A(pin)    ( RPINR16 |= (pin << 0) )
#define PPS_MAP_IN_QE2I(pin)    ( RPINR17 |= (pin << 0) )

// UART
#define PPS_MAP_IN_U1CTS(pin)   ( RPINR18 |= (pin << 8) )
#define PPS_MAP_IN_U1RX(pin)    ( RPINR18 |= (pin << 0) )
#define PPS_MAP_IN_U2CTS(pin)   ( RPINR19 |= (pin << 8) )
#define PPS_MAP_IN_U2RX(pin)    ( RPINR19 |= (pin << 0) )

// SPI
#define PPS_MAP_IN_SCK1(pin)    ( RPINR20 |= (pin << 8) )   /* SPI1 Clock Input (SCK1) */
#define PPS_MAP_IN_SDI1(pin)    ( RPINR20 |= (pin << 0) )   /* SPI1 Data Input (SDI1) */
#define PPS_MAP_IN_SS1(pin)     ( RPINR21 |= (pin << 0) )   /* SPI1 Slave Select (SS1) */
#define PPS_MAP_IN_SCK2(pin)    ( RPINR22 |= (pin << 8) )   /* SPI2 Clock Input (SCK2) */
#define PPS_MAP_IN_SDI2(pin)    ( RPINR22 |= (pin << 0) )   /* SPI2 Data Input (SDI2) */
#define PPS_MAP_IN_SS2(pin)     ( RPINR23 |= (pin << 0) )   /* SPI2 Slave Select (SS2) */

// ECAN
#define PPS_MAP_IN_C1RX(pin)    ( RPINR26 |= (pin << 0) )   /* ECAN1 Receive (C1RX) */

/******************************************************************************/
enum PPS_OUT_PERIPHERAL
{
    PPS_OUT_NULL,           // 0
    PPS_OUT_C1OUT,          // 1
    PPS_OUT_C2OUT,          // 2
    PPS_OUT_U1TX,           // 3
    PPS_OUT_U1RTS,          // 4
    PPS_OUT_U2TX,           // 5
    PPS_OUT_U2RTS,          // 6
    PPS_OUT_SDO1,           // 7
    PPS_OUT_SCK1,           // 8
    PPS_OUT_SS1,            // 9
    PPS_OUT_SDO2,           // 10
    PPS_OUT_SCK2,           // 11
    PPS_OUT_SS2,            // 12
    PPS_OUT_C1TX    = 16,   // 16
    PPS_OUT_OC1     = 18,   // 18
    PPS_OUT_OC2,            // 19
    PPS_OUT_OC3,            // 20
    PPS_OUT_OC4,            // 21
    PPS_OUT_UPDN1   = 26,   // 26
    PPS_OUT_UPDN2           // 27
};

#define PPS_MAP_TO_RP0(fn)      ( RPOR0  |= (fn << 0) )
#define PPS_MAP_TO_RP1(fn)      ( RPOR0  |= (fn << 8) )
#define PPS_MAP_TO_RP2(fn)      ( RPOR1  |= (fn << 0) )
#define PPS_MAP_TO_RP3(fn)      ( RPOR1  |= (fn << 8) )
#define PPS_MAP_TO_RP4(fn)      ( RPOR2  |= (fn << 0) )
#define PPS_MAP_TO_RP5(fn)      ( RPOR2  |= (fn << 8) )
#define PPS_MAP_TO_RP6(fn)      ( RPOR3  |= (fn << 0) )
#define PPS_MAP_TO_RP7(fn)      ( RPOR3  |= (fn << 8) )
#define PPS_MAP_TO_RP8(fn)      ( RPOR4  |= (fn << 0) )
#define PPS_MAP_TO_RP9(fn)      ( RPOR4  |= (fn << 8) )
#define PPS_MAP_TO_RP10(fn)     ( RPOR5  |= (fn << 0) )
#define PPS_MAP_TO_RP11(fn)     ( RPOR5  |= (fn << 8) )
#define PPS_MAP_TO_RP12(fn)     ( RPOR6  |= (fn << 0) )
#define PPS_MAP_TO_RP13(fn)     ( RPOR6  |= (fn << 8) )
#define PPS_MAP_TO_RP14(fn)     ( RPOR7  |= (fn << 0) )
#define PPS_MAP_TO_RP15(fn)     ( RPOR7  |= (fn << 8) )
#define PPS_MAP_TO_RP16(fn)     ( RPOR8  |= (fn << 0) )
#define PPS_MAP_TO_RP17(fn)     ( RPOR8  |= (fn << 8) )
#define PPS_MAP_TO_RP18(fn)     ( RPOR9  |= (fn << 0) )
#define PPS_MAP_TO_RP19(fn)     ( RPOR9  |= (fn << 8) )
#define PPS_MAP_TO_RP20(fn)     ( RPOR10 |= (fn << 0) )
#define PPS_MAP_TO_RP21(fn)     ( RPOR10 |= (fn << 8) )
#define PPS_MAP_TO_RP22(fn)     ( RPOR11 |= (fn << 0) )
#define PPS_MAP_TO_RP23(fn)     ( RPOR11 |= (fn << 8) )
#define PPS_MAP_TO_RP24(fn)     ( RPOR12 |= (fn << 0) )
#define PPS_MAP_TO_RP25(fn)     ( RPOR12 |= (fn << 8) )

#define PPS_RP0_OUT_REG         RPOR0
#define PPS_RP1_OUT_REG         RPOR0
#define PPS_RP2_OUT_REG         RPOR1
#define PPS_RP3_OUT_REG         RPOR1
#define PPS_RP4_OUT_REG         RPOR2
#define PPS_RP5_OUT_REG         RPOR2
#define PPS_RP6_OUT_REG         RPOR3
#define PPS_RP7_OUT_REG         RPOR3
#define PPS_RP8_OUT_REG         RPOR4
#define PPS_RP9_OUT_REG         RPOR4
#define PPS_RP10_OUT_REG        RPOR5
#define PPS_RP11_OUT_REG        RPOR5
#define PPS_RP12_OUT_REG        RPOR6
#define PPS_RP13_OUT_REG        RPOR6
#define PPS_RP14_OUT_REG        RPOR7
#define PPS_RP15_OUT_REG        RPOR7
#define PPS_RP16_OUT_REG        RPOR8
#define PPS_RP17_OUT_REG        RPOR8
#define PPS_RP18_OUT_REG        RPOR9
#define PPS_RP19_OUT_REG        RPOR9
#define PPS_RP20_OUT_REG        RPOR10
#define PPS_RP21_OUT_REG        RPOR10
#define PPS_RP22_OUT_REG        RPOR11
#define PPS_RP23_OUT_REG        RPOR11
#define PPS_RP24_OUT_REG        RPOR12
#define PPS_RP25_OUT_REG        RPOR12

#define PPS_RP0_OUT_BIT         0U
#define PPS_RP1_OUT_BIT         8U
#define PPS_RP2_OUT_BIT         0U
#define PPS_RP3_OUT_BIT         8U
#define PPS_RP4_OUT_BIT         0U
#define PPS_RP5_OUT_BIT         8U
#define PPS_RP6_OUT_BIT         0U
#define PPS_RP7_OUT_BIT         8U
#define PPS_RP8_OUT_BIT         0U
#define PPS_RP9_OUT_BIT         8U
#define PPS_RP10_OUT_BIT        0U
#define PPS_RP11_OUT_BIT        8U
#define PPS_RP12_OUT_BIT        0U
#define PPS_RP13_OUT_BIT        8U
#define PPS_RP14_OUT_BIT        0U
#define PPS_RP15_OUT_BIT        8U
#define PPS_RP16_OUT_BIT        0U
#define PPS_RP17_OUT_BIT        8U
#define PPS_RP18_OUT_BIT        0U
#define PPS_RP19_OUT_BIT        8U
#define PPS_RP20_OUT_BIT        0U
#define PPS_RP21_OUT_BIT        8U
#define PPS_RP22_OUT_BIT        0U
#define PPS_RP23_OUT_BIT        8U
#define PPS_RP24_OUT_BIT        0U
#define PPS_RP25_OUT_BIT        8U

#define TO_STR(pin)  PPS_OUT_REG_RP ## pin
#define TO_REG(pin)     TO_STR(pin)
/**
 * PPS_MAP_OUT_C1OUT(0) => PPS_MAP_TO_RP0(PPS_OUT_C1OUT) => RPOR0 |= (1 << 0);
 */
#define PPS_MAP_OUT_C1OUT(pin)  ( PPS_MAP_TO_RP##pin( PPS_OUT_C1OUT ))
#define PPS_MAP_OUT_C12UT(pin)  ( PPS_MAP_TO_RP##pin( PPS_OUT_C2OUT ))
//#define PPS_MAP_OUT_U1TX(pin)   ( PPS_MAP_TO_RP##pin( PPS_OUT_U1TX  ))
#define PPS_MAP_OUT_U1TX(pin)   ( TO_REG(pin) |= (PPS_OUT_U1TX << PPS_RP##pin##_OUT_BIT) )
#define PPS_MAP_OUT_U1RTS(pin)  ( PPS_MAP_TO_RP##pin( PPS_OUT_U1RTS ))
#define PPS_MAP_OUT_U2TX(pin)   ( PPS_MAP_TO_RP##pin( PPS_OUT_U2TX  ))
#define PPS_MAP_OUT_U2RTS(pin)  ( PPS_MAP_TO_RP##pin( PPS_OUT_U2RTS ))
#define PPS_MAP_OUT_SDO1(pin)   ( PPS_MAP_TO_RP##pin( PPS_OUT_SDO1  ))
#define PPS_MAP_OUT_SCK1(pin)   ( PPS_MAP_TO_RP##pin( PPS_OUT_SCK1  ))
#define PPS_MAP_OUT_SS1(pin)    ( PPS_MAP_TO_RP##pin( PPS_OUT_SS1   ))
#define PPS_MAP_OUT_SDO2(pin)   ( PPS_MAP_TO_RP##pin( PPS_OUT_SDO2  ))
#define PPS_MAP_OUT_SCK2(pin)   ( PPS_MAP_TO_RP##pin( PPS_OUT_SCK2  ))
#define PPS_MAP_OUT_SS2(pin)    ( PPS_MAP_TO_RP##pin( PPS_OUT_SS2   ))
#define PPS_MAP_OUT_C1TX(pin)   ( PPS_MAP_TO_RP##pin( PPS_OUT_C1TX  ))
#define PPS_MAP_OUT_OC1(pin)    ( PPS_MAP_TO_RP##pin( PPS_OUT_OC1   ))
#define PPS_MAP_OUT_OC2(pin)    ( PPS_MAP_TO_RP##pin( PPS_OUT_OC2   ))
#define PPS_MAP_OUT_OC3(pin)    ( PPS_MAP_TO_RP##pin( PPS_OUT_OC3   ))
#define PPS_MAP_OUT_OC4(pin)    ( PPS_MAP_TO_RP##pin( PPS_OUT_OC4   ))
#define PPS_MAP_OUT_UPDN1(pin)  ( PPS_MAP_TO_RP##pin( PPS_OUT_UPDN1 ))
#define PPS_MAP_OUT_UPDN2(pin)  ( PPS_MAP_TO_RP##pin( PPS_OUT_UPDN2 ))


#define  PPS_UNLOCK()           __builtin_write_OSCCONL(OSCCON & 0xbf)
#define  PPS_LOCK()             __builtin_write_OSCCONL(OSCCON | 0x40)

void pps_mapRP(uint8_t pin, uint8_t peripheral);

#endif	/* CPPS_H */

