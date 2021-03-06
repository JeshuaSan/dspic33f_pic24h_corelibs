/* http://www.ganssle.com/tem/tem110.pdf */

#include "peripheral/uart.h"
#include "device/pinconfig.h"
#include "common/globals.h"
#include "common/types.h"
#include <pps.h>
//#include <string.h>
#include <stdint.h>

#define BRG(br)     ((FCY/16U/br) - 1U)

#if !defined(UART_RX) || !defined (UART_TX)
#error Must define UART_RX and UART_TX
#endif


/* Private variables **********************************************************/
#define BUF_SIZE    (64U)
#define BUF_MASK    (BUF_SIZE - 1U)

typedef struct tagFifoBuffer {
    uint8_t data[BUF_SIZE];
    uint8_t head;
    uint8_t tail;
} fifoBuffer_t;

static volatile fifoBuffer_t rxBuffer;
static volatile fifoBuffer_t txBuffer;

/* Private prototypes *********************************************************/
static void uart_config(const uint32_t baudRate);
static void uart_pins(void);

static inline vuint8_t fifo_len(volatile fifoBuffer_t* fifoBuffer);
static inline void fifo_put(volatile fifoBuffer_t* fifoBuffer, const vuint8_t c);
static inline vuint8_t fifo_get(volatile fifoBuffer_t* fifoBuffer);

/* Public funtions ************************************************************/

void uart_init(const uint32_t baudRate)
{
    uart_pins();
    uart_config(baudRate);
 //   memset((uint8_t *)&rxBuffer, 0x00, sizeof(rxBuffer));
}



uint8_t uart_charReady()
{
    /* Return "true" if the buffer is not empty */
    return (rxBuffer.head - rxBuffer.tail) != 0;
}

uint8_t uart_getc()
{
    //uint8_t c = -1;
    uint8_t c = 0;

    /* If the buffer is not empty, return the last character stored */
//    if ((rxBuffer.head - rxBuffer.tail) != 0 )
    if (fifo_len(&rxBuffer) != 0)
    {
//        c = *( rxBuffer.data + (rxBuffer.tail & BUF_MASK) );
//        ++rxBuffer.tail;
        c = fifo_get(&rxBuffer);
    }
    return c;
}

void uart_putc(const uint8_t c)
{
    /* If the buffer is not full, store the character read in it */
    if (fifo_len(&txBuffer) < BUF_SIZE)
    {
//        /* Read the byte and wrap if necessary */
//        *(txBuffer.data + (txBuffer.head & BUF_MASK)) = c;
//        ++txBuffer.head;
        fifo_put(&txBuffer, c);
        _U1TXIE = 1;
    }
}


/* Private functions **********************************************************/

static void uart_pins(void)
{
    // Map PPS pins to periphereal functions
    PPSUnLock;
    PPSInput(IN_FN_PPS_U1RX, UART_RX);
    PPSOutput(OUT_FN_PPS_U1TX, UART_TX);
    PPSLock;
}

static void uart_config(const uint32_t baudRate)
{
    U1BRG = BRG(baudRate);          // Set baudrate

    // UART Mode Register
    U1MODE =
            (1U << 15)  |   // UARTEN = 1   UART1 enabled
            /* bit 14 us unimplemented */
            (0U << 13)  |   // USIDL = 0    Continue operation in idle mode
            (0U << 12)  |   // IREN = 0     IrDA encoder and decoder disabled
            (0U << 11)  |   // RTSMD = 0    UxRTS1 in flow control mode. Given
            (0U << 8)   |   // UEN = 0      UxTX and UxRx pins are enabled and
                            //                  used; UxCTS, UxRTS, and BCLKx pins are
                            //                  controlled by port latches
            (0U << 7)   |   // WAKE = 0     Wake-up is disabled
            (0U << 6)   |   // LPBACK = 0   Loopback mode is disabled
            (0U << 5)   |   // ABAUD = 0    Auto-baud disabled
            (0U << 4)   |   // URXINV = 0   UxRX Idle is '1
            (0U << 3)   |   // BRGH = 0     Low speed mode
            (0U << 1)   |   // PDSEL = 0    8-bit data, no parity
            (0U << 0);      // STSEL = 0    1 stop bit

    // UART Status and Control Register
    U1STA =
            (0U << 15)  |   // UTXISEL1 = 0 See bit 13
            (0U << 14)  |   // UTXINV = 0   UxTX idle state is '1'
            (0U << 13)  |   // UTXISEL0 = 0 With bit 15, UTXISEL = 00:
                            //                  Interrupt generated when any character
                            //                  is transferred to the Transmit Shift Register).
            /* Bit 12 is unimplemented */
            (0U << 11)  |   // UTXBRK = 0   Sync break transmission disabled
            (1U << 10)  |   // UTXEN = 0    UARTx transmitter enabled. NOTE: per
                            //                  the data sheet, this must be set
                            //                  *AFTER* UARTEN is set to 1
            /* Bit 9 is read-only (UTXBF) */
            /* Bit 8 is read-only (TRMT) */
            (0U <<  6)  |   // URXISEL<7:6> = 00 Interrupt flag bit is set when
                            //                  a character is received
            (0U <<  5)  |   // ADDEN = 0    Address detect mode disabled
            /* Bit 4 is read-only */
            /* Bit 3 is read-only */
            /* Bit 2 is read-only */
            (0U <<  1);     // OERR = 0     Clear any overrun errors
                            /* Bit 0 is read-only */


    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;            // Enable UART1 RX interrupt
}

void _ISR_NOPSV _U1RXInterrupt(void)
{
    _U1RXIF = 0;

    vuint8_t c = U1RXREG;

    /* If the buffer is not full, store the character read in it */
    if ((rxBuffer.head - rxBuffer.tail) < BUF_SIZE)
    {
        rxBuffer.head &= BUF_MASK;          // Wrap if necessary
        rxBuffer.data[rxBuffer.head] = c;
        ++rxBuffer.head;
    }
}

void _ISR_NOPSV _U1TXInterrupt(void)
{
    /* If the buffer is not empty, return the last character stored */
    if ((txBuffer.head - txBuffer.tail) != 0 )
    {
        /* Put the corresponding data on the register and wrap if necessary */
        U1TXREG = *(txBuffer.data + (txBuffer.tail & BUF_MASK));
        ++txBuffer.tail;
        _U1TXIF = 0;
    }
    else
    {
        _U1TXIE = 0;
    }
}

static inline vuint8_t fifo_len(volatile fifoBuffer_t* fifoBuffer)
{
    return fifoBuffer->head - fifoBuffer->tail;
}

static inline void fifo_put(volatile fifoBuffer_t* fifoBuffer, const vuint8_t c)
{
    /* Read the byte and wrap if necessary */
    *(fifoBuffer->data + (fifoBuffer->head & BUF_MASK)) = c;
    ++fifoBuffer->head;
}

static inline vuint8_t fifo_get(volatile fifoBuffer_t* fifoBuffer)
{
    vuint8_t c = *( fifoBuffer->data + (fifoBuffer->tail & BUF_MASK) );
    ++fifoBuffer->tail;
    return c;
}