#ifndef PINCONFIG_H
#define	PINCONFIG_H

#include <xc.h>
#include <pps.h>
#include "peripheral/pps.h"

// LED
#define LED             LATAbits.LATA4      // LED
#define LED_TRS         TRISAbits.TRISA4    // LED Tris

// UART
#define UART_RX         IN_PIN_PPS_RP10
#define UART_TX         OUT_PIN_PPS_RP11

// OLED display
#define OLED_CS         LATAbits.LATA0      // Chip select
#define OLED_CS_TRS     TRISAbits.TRISA0    // Chip select TRIS
#define OLED_RST        LATBbits.LATB6      // Reset
#define OLED_RST_TRS    TRISBbits.TRISB6    // Reset TRIS
#define OLED_DC         LATBbits.LATB7      // Data/command
#define OLED_DC_TRS     TRISBbits.TRISB7    // Data/command TRIS
#define OLED_CLK        OUT_PIN_PPS_RP8     // Clock
#define OLED_DATA       OUT_PIN_PPS_RP9     // Data out

// SPI
#define SPI_MISO        0
#define SPI_MOSI        OLED_DATA
#define SPI_CLK         OLED_CLK

// QEI
#define QE1_A           IN_PIN_PPS_RP2
#define QE1_B           IN_PIN_PPS_RP3
#define QE2_A           IN_PIN_PPS_RP4
#define QE2_B           IN_PIN_PPS_RP5


#endif	/* PINCONFIG_H */

