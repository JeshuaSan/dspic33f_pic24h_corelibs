#include "adc.h"
#include "timer/timer1.h"
#include "../globals.h"
#include <xc.h>
#include <stdint.h>

/* DMA buffer configuration */
#define ADC_N_INPUT     6U
#define ADC_BUF_SIZE    4U
#define ADC_N_WORDS     (ADC_N_INPUT * ADC_BUF_SIZE)
#define ADC_N_BYTES     (ADC_N_WORDS * 2U)

/* ADC helpers */
#define ADC_INT         13U
#define ADC_ON()        BIT_SET(AD1CON1, 15)
#define ADC_OFF()       BIT_CLR(AD1CON1, 15)

/* Private variables **********************************************************/
uint16_t dmaBufferA[ADC_N_INPUT][ADC_BUF_SIZE] __attribute__((space(dma), aligned(64)));
uint16_t dmaBufferB[ADC_N_INPUT][ADC_BUF_SIZE] __attribute__((space(dma), aligned(64)));
volatile uint16_t adcBuffer[ADC_N_INPUT] = {0};     // holds adc averaged conversions
volatile uint8_t dmaBufferIndex = 0;                // holds dma buffer in use

/* Private functions **********************************************************/
static void adc_dmaInit(void);
static void adc_configReg(uint8_t adcN_inputs);
static void adc_average(uint16_t* dmaBuffer, volatile uint16_t* adcBuffer);

/* Main functions *************************************************************/
void adc_init(enum ADCPORT adcPortA, enum ADCPORT adcPortB)
{
    // Make pins analog
    BIT_CLR(AD1PCFGL, adcPortA);
    BIT_CLR(AD1PCFGL, adcPortB);

    // Select inputs to scan
    BIT_SET(AD1CSSL, adcPortA);
    BIT_SET(AD1CSSL, adcPortB);
    adc_configReg(2);
    adc_dmaInit();

    // Clear and disable ADC1 interrupts
    BIT_CLR(IFS0, ADC_INT);
    BIT_CLR(IEC0, ADC_INT);
}

void adc_start(void)
{
    ADC_ON();
    DMA0CONbits.CHEN = 1;
}

void adc_stop(void)
{
    ADC_OFF();
    DMA0CONbits.CHEN = 0;
}

uint16_t adc_read(enum ADCPORT adcPort)
{
    return adcBuffer[adcPort];
}
/* Private functions **********************************************************/
static void adc_configReg(uint8_t adcN_inputs)
{
    uint8_t _n = adcN_inputs - 1;

    AD1CON1 =
            (0U << 15)  |   /* ADON = 0     ADC is off. */
                            //              bit 14 unimplemented
            (0U << 13)  |   /* ADSIDL = 0   Continue operation in idle. */
            (0U << 12)  |   /* ADMABM = 0   DMA buffers are witten in Scatter/Gatter mode. */
                            //              bit 11 unimplemented
            (0U << 10)  |   /* AD12B = 0    10-bit, 4-channel ADC */
            (0U << 9)   |   /* FORM<9-8> = <00> Unsigned Integer (Dout = 000 00dd dddd dddd) */
            (0U << 8)   |
            (1U << 7)   |   /* SSRC<7-5> = <111> Internal counter ends sampling and */
            (1U << 6)   |                   //      starts conversion (auto-convert)
            (1U << 5)   |
                            //              bit 4 unimplemented
            (0U << 3)   |   /* SIMSAM = 0   Samples multiple channels individually in sequence. */
            (1U << 2);      /* ASAM = 1     Sampling begins imediately after last conversion.
                                            SAMP bit is auto-set. */
                            /* SAMP = 1     ADC sample/hold amplifiers are sampling */
                            /* DONE         Automatically set by hardware when
                                            ADC conversions are complete. */


    AD1CON2 =
            (0U << 15)  |   /* VCFG<15-13 = 000     ADREF+ = Avdd */
            (0U << 14)  |                   //      ADREF- = Avss
            (0U << 13)  |
                            //              bits <12:11> unimplemented
            (1U << 10)  |   /* CSCNA = 1    Scan inputs */
            (0U << 9)   |   /* CHPS<9-8> = 00       Converts CH0 */
            (0U << 8)   |
                            /* BUFS         Only valid when BUFM = 1 */
                            //              bit 6 unimplemented
            (_n << 2)   |   /* SMPI<5-2> = n_inputs - 1     Increments DMA address after
                                                    competion of every nth
                                                    sample/conversion operation */
            (0U << 1)   |   /* BUFM = 0     Always starts filling buffer ad address 0x0 */
            (0U << 0);      /* ALTS = 0     Always uses channel input selects por Sample A */


    AD1CON3 =
            (0U << 15)  |   /* ADRC = 0     Clock devided from system clock. */
                            //              bit 14 unimplemented
                            //              bit 13 unimplemented
            (31U << 8)  |   /* SAMC<12-8> = 31      31 TAD */
            (63U << 0);     /* ADCS<7:0>  = 63      64 * TCY = TAD */


    AD1CON4 = 2U;           /* DMABL = 2    Allocates 4 words of buffer to each
                                            analog input*/


    // AD1CHS123: ADC1 channel 1, 2, 3 select register
    AD1CHS123 = 0x0000;      /* CH1, CH2, CH3 unused */


    // AD1CHS0: ADC1 input channel 0 select register
    AD1CHS0 =
            (0U << 15)  |   /* CH0NB = 0    Channel 0 negative input is Vref-
                                            ** NOT USED ** */
                            //              bits <14:13> unimplemented
            (0U << 8)   |   /* CH0SB = 0    Channel 0 positive input is AN0
                                            ** NOT USED ** */
            (0U << 7)   |   /* CH0NA = 0    Channel 0 negative input is Vref- */
                            //              bits <6:5> unimplemented
            (0U << 0);      /* CH0SA = 0    Channel 0 positive input is AN0
                                            ** OVERRIDE BY AD1CON2:CSCNA ** */

}

static void adc_dmaInit()
{

    // DMAXCON: DMA Channel X Control Register
    DMA0CONbits.AMODE = 2;      // 10 = Peripheral Indirect Addressing mode
    DMA0CONbits.MODE = 2;       // 10 = Continuous, Ping-Pong modes enabled

    // DMAXPAD: DMA Channel X Peripheral Address Register
    DMA0PAD = (uint16_t)&ADC1BUF0;   // ADC1

    // DMAXCNT: DMA Channel X Transfer Count Register
    DMA0CNT = (ADC_BUF_SIZE * ADC_N_INPUT) - 1;

    // DMAXREQ: DMA Channel X IRQ Select Register
    DMA0REQ = 13;     // 0001101 = ADC1 Convert Done (ADC1)

    // DMAXSTA: DMA Channel X DPSRAM Start Address Offset Register A
    DMA0STA = __builtin_dmaoffset(dmaBufferA);

    // DMAXSTB: DMA Channel X DPSRAM Start Address Offset Register B
    DMA0STB = __builtin_dmaoffset(dmaBufferB);


    IFS0bits.DMA0IF = 0;    // Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = 1;    // Set the DMA interrupt enable bit

    DMA0CONbits.CHEN = 0;   // Disable DMA
}

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    if(dmaBufferIndex == 0)
    {
        adc_average(&dmaBufferA[0][0], &adcBuffer[0]);
        adc_average(&dmaBufferA[1][0], &adcBuffer[1]);
        adc_average(&dmaBufferA[2][0], &adcBuffer[2]);
        adc_average(&dmaBufferA[3][0], &adcBuffer[3]);
        adc_average(&dmaBufferA[4][0], &adcBuffer[4]);
        adc_average(&dmaBufferA[5][0], &adcBuffer[5]);
    }
    else
    {
        adc_average(&dmaBufferB[0][0], &adcBuffer[0]);
        adc_average(&dmaBufferB[1][0], &adcBuffer[1]);
        adc_average(&dmaBufferB[2][0], &adcBuffer[2]);
        adc_average(&dmaBufferB[3][0], &adcBuffer[3]);
        adc_average(&dmaBufferA[4][0], &adcBuffer[4]);
        adc_average(&dmaBufferA[5][0], &adcBuffer[5]);
    }

    dmaBufferIndex ^= 1;
    IFS0bits.DMA0IF = 0;
}

static void adc_average(uint16_t* dmaBuffer, volatile uint16_t* adcBuffer)
{
    volatile uint8_t i = 0;
    volatile uint16_t adcSample = 0;
    for(; i < ADC_BUF_SIZE; ++i, ++dmaBuffer)
    {
        adcSample += *dmaBuffer;
    }

    *adcBuffer = adcSample / 4;
}
