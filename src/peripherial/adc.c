#include "adc.h"
#include "timer/timer1.h"
#include <xc.h>
#include <stdint.h>

#define ADC_N_CHAN      2
#define ADC_BUF_SIZE    4

int16_t dmaBufferA[ADC_N_CHAN][ADC_BUF_SIZE] __attribute__((space(dma), aligned(32)));
int16_t dmaBufferB[ADC_N_CHAN][ADC_BUF_SIZE] __attribute__((space(dma), aligned(32)));

static void adc_dmaInit(void);
static void adc_timerInit(void);

void adc_init()
{
    adc_dmaInit();
    adc_timerInit();
}



static void adc_dmaInit()
{

    // DMAXCON: DMA Channel X Control Register
    DMA0CONbits.AMODE = 2;      // 10 = Peripheral Indirect Addressing mode
    DMA0CONbits.MODE = 2;       // 10 = Continuous, Ping-Pong modes enabled

    // DMAXPAD: DMA Channel X Peripheral Address Register
    DMA0PAD = (uint16_t)&ADC1BUF0;   // ADC1

    // DMAXCNT: DMA Channel X Transfer Count Register
    DMA0CNT = (ADC_BUF_SIZE * ADC_N_CHAN)-1;

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

static void adc_timerInit(void)
{
    timer_init(TIMER3);
    timer_set_us(TIMER3, 120);
    timer_start(TIMER3);
}