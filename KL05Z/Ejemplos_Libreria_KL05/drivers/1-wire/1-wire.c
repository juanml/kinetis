/////////////////////////////////////////////////////////////////////////////////////////
//
// 1-Wire Library V1
//
// --------------------------------------------------------------------------------------
// 
// Filename:      1-wire.c
// Version:       1.2
// Date:          01/11/2011
// Author:        Joel Guittet - http://myfreescalewebpage.free.fr
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Description
//
// This files contains the functions used to communicate with the 1-Wire interface.
// Due to its simple implementation, the 1-Wire Library V1 is able to communicate with a
// single 1-Wire device on the microcontroller. It is not able to manage multiple 1-Wire
// devices.
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Revisions
//
// Version	| Author		| Description
// --------------------------------------------------------------------------------------
// 1.0      | Joel Guittet  | Initial Release
// 1.1		| Joel Guittet	| Coding improvements
// 1.2      | Joel Guittet  | Coding improvements
// 1.2      | Joel Guittet  | Modifications to use "typedef.h"
//
/////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------------------

#include "1-wire.h"
#include "WAIT1.h"
#include "gpio.h"


//---------------------------------------------------------------------------------------
// Name:        ONEWIRE_Init
// Param:		-
// Return:      -
//
// Description:	Initialization of the 1-wire serial interface
//---------------------------------------------------------------------------------------
void ONEWIRE_Init(void)
{
	ONEWIRE_SET_HIGH
}


//---------------------------------------------------------------------------------------
// Name:        ONEWIRE_Reset
// Param:		-
// Return:      1-Wire reset result: NO_DEVICE_DETECTED, DEVICE_PRESENT or DEVICE_SHORTED
//
// Description:	Performs 1-Wire Reset
//---------------------------------------------------------------------------------------
t_OneWireResetResult ONEWIRE_Reset(void)
{
	BOOLEAN bShortDetect = FALSE;
	BOOLEAN bPresencePulseDetect = FALSE;
		
	/* Reset Pulse */
	ONEWIRE_SET_LOW  
	//ONEWIRE_DELAY(500)
	WAIT1_Waitus(500);
	ONEWIRE_SET_HIGH
	
	/* Short delay */
	//ONEWIRE_DELAY(5)
	WAIT1_Waitus(5);
	
	/* Short detect: if the 1-wire pin is low, it is because the 1-wire device is shorted */
	if (GPIO_Read(PORT_B, 0) == 0/*ONEWIRE_PIN == 0*/) bShortDetect = TRUE;
	
	/* Wait the device answer */
	//ONEWIRE_DELAY(65)
	WAIT1_Waitus(65);
	
	/* Presence pulse: if the 1-wire pin is low, it is because the 1-wire device is present (or shorted) */
	if (GPIO_Read(PORT_B, 0) == 0 /*ONEWIRE_PIN == 0*/) bPresencePulseDetect = TRUE;
	
	/* Delay */
	//ONEWIRE_DELAY(500)
	WAIT1_Waitus(500);
	
	/* Result */
	if (bShortDetect == TRUE)
		return DEVICE_SHORTED;
	else if (bPresencePulseDetect == TRUE)
		return DEVICE_PRESENT;
	else
		return NO_DEVICE_DETECTED;
}
 

//---------------------------------------------------------------------------------------
// Name:        ONEWIRE_WriteByte
// Param:		Byte: byte which have to be written on the 1-wire interface
// Return:		-
//
// Description:	Write a byte
//---------------------------------------------------------------------------------------
void ONEWIRE_WriteByte(uint8_t u8Byte)
{
	uint8_t u8Index;
	
	/* Write the 8 bits on the 1-wire pin */
	for (u8Index = 0; u8Index < 8; u8Index++)
	{
		/* Pulse */
		ONEWIRE_SET_LOW
	
		if ((u8Byte & 0x01 << u8Index) == 0)
		{
			/* '0' => Long Pulse */
			//ONEWIRE_DELAY(60)
			WAIT1_Waitus(60);
			ONEWIRE_SET_HIGH
			//ONEWIRE_DELAY(5)
			WAIT1_Waitus(5);
		}
		else
		{
			/* '1' => Short Pulse */
			//ONEWIRE_DELAY(5)
			WAIT1_Waitus(5);
			ONEWIRE_SET_HIGH
			//ONEWIRE_DELAY(60)
			WAIT1_Waitus(60);
		}
	}
}


//---------------------------------------------------------------------------------------
// Name:     	ONEWIRE_ReadByte
// Param:    	-
// Return:      Byte read
//
// Description:	Read a byte
//---------------------------------------------------------------------------------------
uint8_t ONEWIRE_ReadByte(void)
{
	uint8_t u8Index, u8Byte = 0;
	
	/* Read the 8 bits */
	for (u8Index = 0; u8Index < 8; u8Index++)
	{
		/* Short Pulse */
		ONEWIRE_SET_LOW
		//ONEWIRE_DELAY(5)
		WAIT1_Waitus(5);
		ONEWIRE_SET_HIGH
	
		/* Delay */
		//ONEWIRE_DELAY(5)
		WAIT1_Waitus(5);
	
		/* Read the 1-wire device response */
		if (GPIO_Read(PORT_B, 0) != 0 /*ONEWIRE_PIN != 0*/) u8Byte += 0x01 << u8Index;
	
		/* Delay */
		//ONEWIRE_DELAY(55)
		WAIT1_Waitus(55);
	}
	
	return u8Byte;
}


//---------------------------------------------------------------------------------------
// Name:        ONEWIRE_SetStrongPullUp
// Param:    	-
// Return:      -
//
// Description:	Set strong pull-up in order to power the 1-Wire device throw the microcontroller
//---------------------------------------------------------------------------------------
void ONEWIRE_SetStrongPullUp(void)
{
	ONEWIRE_SET_STRONG_PU
}
