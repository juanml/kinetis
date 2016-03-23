/*
 * gpio.c
 *
 *  Created on: 18/3/2016
 *      Author: Juan Manuel Lopez
 */

#include "gpio.h"

/**
  Function Name	: GPIO_Init
  Parameters	: uint32_t port, uint8_t bit, uint32_t func
  Returns       : Nothing
  Notes         : Esta función permite inicializar el pin indicado y enviar
  	  	  	  	  los distintos parámetros de configuración haciendo una OR
  	  	  	  	  entre ellos.
*/
void GPIO_Init(uint32_t port, uint8_t bit, uint32_t func)
{
  switch (port)
	{
		case PORTA_BASE: PORT_PCR_REG(PORTA_BASE_PTR, bit) = func; break;
	  	case PORTB_BASE: PORT_PCR_REG(PORTB_BASE_PTR, bit) = func; break;
	  	case PORTC_BASE: PORT_PCR_REG(PORTC_BASE_PTR, bit) = func; break;
	  	case PORTD_BASE: PORT_PCR_REG(PORTD_BASE_PTR, bit) = func; break;
	  	case PORTE_BASE: PORT_PCR_REG(PORTE_BASE_PTR, bit) = func; break;
	}
}

/**
  Function Name	: GPIO_Output
  Parameters	: uint32_t port, uint8_t bit
  Returns       : Nothing
  Notes         : Configura como salida el pin del puerto indicado
*/

void GPIO_IO(uint32_t port, uint8_t bit, uint8_t dir)
{
    if ((port == PORTA_BASE) && (dir == OUTPUT))
		{
		  GPIOA_PDDR |= (1ul << bit);
		} else if ((port == PORTA_BASE) && (dir == INPUT))
					{
						GPIOA_PDDR &= ~(1ul << bit);
					}
    if ((port == PORTB_BASE) && (dir == OUTPUT))
		{
		  GPIOB_PDDR |= (1ul << bit);
		} else if ((port == PORTB_BASE) && (dir == INPUT))
					{
						GPIOB_PDDR &= ~(1ul << bit);
					}
    if ((port == PORTC_BASE) && (dir == OUTPUT))
		{
		  GPIOC_PDDR |= (1ul << bit);
		} else if ((port == PORTC_BASE) && (dir == INPUT))
					{
						GPIOC_PDDR &= ~(1ul << bit);
					}
    if ((port == PORTD_BASE) && (dir == OUTPUT))
		{
		  GPIOD_PDDR |= (1ul << bit);
		} else if ((port == PORTD_BASE) && (dir == INPUT))
					{
						GPIOD_PDDR &= ~(1ul << bit);
					}
    if ((port == PORTE_BASE) && (dir == OUTPUT))
		{
		  GPIOE_PDDR |= (1ul << bit);
		} else if ((port == PORTE_BASE) && (dir == INPUT))
					{
						GPIOE_PDDR &= ~(1ul << bit);
					}
}

/**
  Function Name	: GPIO_Set
  Parameters	: uint32_t port, uint8_t bit
  Returns       : Nothing
  Notes         : Pone en alto el pin del puerto indicado
*/
void GPIO_Set(uint32_t port, uint8_t bit)
{
	switch (port)
		{
			case PORTA_BASE: GPIOA_PSOR = (1ul << bit); break;
		  	case PORTB_BASE: GPIOB_PSOR = (1ul << bit); break;
		  	case PORTC_BASE: GPIOC_PSOR = (1ul << bit); break;
		  	case PORTD_BASE: GPIOD_PSOR = (1ul << bit); break;
		  	case PORTE_BASE: GPIOE_PSOR = (1ul << bit); break;
		}
}

/**
  Function Name	: GPIO_Clear
  Parameters	: uint32_t port, uint8_t bit
  Returns       : Nothing
  Notes         : Pone en bajo el pin del puerto indicado
*/
void GPIO_Clear(uint32_t port, uint8_t bit)
{
	switch (port)
		{
			case PORTA_BASE: GPIOA_PCOR = (1ul << bit); break;
		  	case PORTB_BASE: GPIOB_PCOR = (1ul << bit); break;
		  	case PORTC_BASE: GPIOC_PCOR = (1ul << bit); break;
		  	case PORTD_BASE: GPIOD_PCOR = (1ul << bit); break;
		  	case PORTE_BASE: GPIOE_PCOR = (1ul << bit); break;
		}
}

/**
  Function Name	: GPIO_Toggle
  Parameters	: uint32_t port, uint8_t bit
  Returns       : Nothing
  Notes         : Cambia el valor del pin del puerto indicado
*/
void GPIO_Toggle(uint32_t port, uint8_t bit)
{
   switch (port)
	  {
	  	  case PORTA_BASE: GPIOA_PTOR = (1ul << bit); break;
	  	  case PORTB_BASE: GPIOB_PTOR = (1ul << bit); break;
	  	  case PORTC_BASE: GPIOC_PTOR = (1ul << bit); break;
	  	  case PORTD_BASE: GPIOD_PTOR = (1ul << bit); break;
	  	  case PORTE_BASE: GPIOE_PTOR = (1ul << bit); break;
	  }
}

/**
  Function Name	: GPIO_Read
  Parameters	: uint32_t port, uint8_t bit
  Returns       : uint8_t temp
  Notes         : Cuando un pin se configura como entrada, lee su valor
   	   	   	   	  y lo devuelve en la variable temp.
*/
uint8_t GPIO_Read(uint32_t port, uint8_t bit)
	{
	  uint8_t temp;

	  switch (port)
		  {
	  	  	  case PORTA_BASE: temp = GPIOA_PDIR & (1ul << bit); break;
	  	  	  case PORTB_BASE: temp = GPIOB_PDIR & (1ul << bit); break;
	  	  	  case PORTC_BASE: temp = GPIOC_PDIR & (1ul << bit); break;
	  	  	  case PORTD_BASE: temp = GPIOD_PDIR & (1ul << bit); break;
	  	  	  case PORTE_BASE: temp = GPIOE_PDIR & (1ul << bit); break;
		  }
	  return temp;
	}
