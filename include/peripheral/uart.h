/* 
 * File:   uart.h
 * Author: jesus
 *
 * Created on February 5, 2014, 9:32 AM
 */

#ifndef UART_H
#define	UART_H

#include <stdint.h>

void uart_init(const uint32_t baudRate);

void uart_putc(const uint8_t c);
uint8_t uart_getc(void);
uint8_t uart_charReady(void);

#endif	/* UART_H */

