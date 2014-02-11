#include <pps.h>
#include "spi.h"
#include "../pinconfig.h"

/*
 * MOSI, MISO and CLK pins must be defined
 */

#if !defined(SPI_MOSI) || !defined (SPI_MISO) || !defined(SPI_CLK)
#error("Must define MOSI, MISO and CLK ")
#endif


static void spiConfig(void);
static void spiConfigPins(void);

static void spiConfigPins()
{
    // Assign MOSI, MISO and CLK pins to SPI periphereal
    // Pin directions set automatically, no need to set tris bits
    PPSUnLock;
    PPSOutput(OUT_FN_PPS_SDO1, SPI_MOSI);  // DATA as SDO
    PPSOutput(OUT_FN_PPS_SCK1, SPI_CLK);   // CLK as SCK
    PPSLock;
}

static void spiConfig()
{
    SPI1STATbits.SPIEN = 0;     // Disable SPI module

    // SPI1CON1
    SPI1CON1bits.DISSCK = 0;    // Internal serial clock enabled
    SPI1CON1bits.DISSDO = 0;    // SDO pin controlled by the module
    SPI1CON1bits.MODE16 = 0;    // 8-bits communication
    SPI1CON1bits.CKE = 0;       // Serial output changes on clock state transition
                                // from idle (H) to active(L)
    SPI1CON1bits.CKP = 1;       // clock idle = H, active = L
    SPI1CON1bits.MSTEN = 1;     // Master mode enabled
    SPI1CON1bits.PPRE = 3;      // 1:1 Primary prescaler
    SPI1CON1bits.SPRE = 4;      // 5:1 Secondary prescaler
                                // ~8 MHz

    SPI1STATbits.SPIEN = 1;     // Enable SPI module
}

void spi_init()
{
    spiConfigPins();
    spiConfig();
}

uint16_t spiWrite(uint8_t c)
{
//    while(SPI1STATbits.SPITBF);
    SPI1BUF = c;
    while(!SPI1STATbits.SPIRBF);
    return SPI1BUF;
}