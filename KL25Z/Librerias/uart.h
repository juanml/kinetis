/*
 * File:		uart.h
 * Purpose:     Provide common ColdFire uart routines for polled serial IO
 *
 * Notes:
 */

#ifndef __uart_H__
#define __uart_H__

#include "stdio.h"

typedef signed char             int8;
typedef signed short int        int16;
typedef signed long int         int32;

typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;

typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned long int       uint32_t;

#define TERM_PORT_NUM       0

#define TERMINAL_BAUD       115200

#define UART_115200 115200 /*! UART in 115.2 kbaud mode */
#define UART_SPEED_MODE UART_115200
/********************************************************************/


void uart_init (UART_MemMapPtr uartch, int sysclk, int baud);
char uart_getchar (UART_MemMapPtr channel);
void uart_putchar (UART_MemMapPtr channel, char ch);
int uart_getchar_present (UART_MemMapPtr channel);
void InitUart0(void);
char uart0_getchar (UART0_MemMapPtr channel);
void uart0_putchar (uint8_t ch);
int uart0_getchar_present (UART0_MemMapPtr channel);
void uart0_putstr(const uint8_t *str);

/********************************************************************/

#endif /* __uart_H__ */
