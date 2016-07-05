/*
 * File:		uart.h
 * Purpose:     Provide common uart routines for polled serial IO
 *
 * Notes:
 */

#ifndef __uart_H__
#define __uart_H__

/********************************************************************/

#define TERM_PORT_NUM 0

#define UART_MCGFLLCLK 	1
#define UART_OSCERCLK 	2
#define UART_MCGIRCLK	3

#define UART_PTB1_TX	PORT_PCR_MUX(2)
#define UART_PTB1_RX	PORT_PCR_MUX(3)
#define UART_PTB2_RX	PORT_PCR_MUX(2)
#define UART_PTB2_TX	PORT_PCR_MUX(3)
#define UART_PTB3_TX	PORT_PCR_MUX(3)
#define UART_PTB4_RX	PORT_PCR_MUX(3)

void UART0_init (uint8_t clk_source, int sysclk, int baud);
void UART0_pinMux(uint32_t port, uint8_t bit, uint32_t func);
char UART0_getchar (void);
void UART0_putchar (char ch);
int UART0_getchar_present (void);
void UART0_putstr(uint8_t *str);

/********************************************************************/

#endif /* __uart_H__ */
