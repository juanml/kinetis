/*
 * gpio.c
 *
 *  Created on: 21/5/2016
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
		case PORTA_BASE: PORT_PCR_REG(PORTA_BASE_PTR, bit) |= func; break;
	  	case PORTB_BASE: PORT_PCR_REG(PORTB_BASE_PTR, bit) |= func; break;
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
	  switch (port)
		  {
	  	  	  case PORTA_BASE: return ((GPIOA_PDIR & (1ul << bit))? (uint8_t)TRUE : (uint8_t)FALSE); break;
	  	  	  case PORTB_BASE: return ((GPIOB_PDIR & (1ul << bit))? (uint8_t)TRUE : (uint8_t)FALSE); break;
		  }
	}
