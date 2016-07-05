/*
 * gpio.h
 *
 *  Created on: 21/5/2016
 *      Author: Juan Manuel Lopez
 */

#include "MKL05Z4.h"

#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_

#define OUTPUT	1
#define INPUT	0

#define PORT_A	PORTA_BASE
#define PORT_B	PORTB_BASE

#define IO_MUX				PORT_PCR_MUX(1)
#define PULL_UP				PORT_PCR_PS(1)
#define PULL_EN				PORT_PCR_PE(1)
#define PULL_OFF			PORT_PCR_PE(0)
#define SLEW_RATE_FAST		PORT_PCR_SRE(1)
#define SLEW_RATE_SLOW		PORT_PCR_SRE(0)
#define FILTER_ON			PORT_PCR_PFE(1)
#define FILTER_OFF			PORT_PCR_PFE(0)
#define DRV_STR_ON			PORT_PCR_DSE(1)
#define DRV_STR_OFF			PORT_PCR_DSE(0)
#define IRQ_OFF				PORT_PCR_IRQC(0)
#define DMA_RISING			PORT_PCR_IRQC(1)
#define DMA_FALLING			PORT_PCR_IRQC(2)
#define DMA_RISING_FALLING	PORT_PCR_IRQC(3)
#define IRQ_LOW				PORT_PCR_IRQC(4)
#define IRQ_RISING			PORT_PCR_IRQC(5)
#define IRQ_FALLING			PORT_PCR_IRQC(6)
#define IRQ_RISING_FALLING	PORT_PCR_IRQC(7)
#define IRQ_HIGH			PORT_PCR_IRQC(8)


void GPIO_Init(uint32_t port, uint8_t bit, uint32_t func);
void GPIO_IO(uint32_t port, uint8_t bit, uint8_t dir);
void GPIO_Set(uint32_t port, uint8_t bit);
void GPIO_Clear(uint32_t port, uint8_t bit);
void GPIO_Toggle(uint32_t port, uint8_t bit);
uint32_t GPIO_Read(uint32_t port, uint8_t bit);

#endif /* INCLUDES_GPIO_H_ */
