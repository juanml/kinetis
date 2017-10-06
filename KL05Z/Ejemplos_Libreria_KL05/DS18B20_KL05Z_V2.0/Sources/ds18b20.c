/////////////////////////////////////////////////////////////////////////////////////////
//
// DS18B20 Library V1
//
// --------------------------------------------------------------------------------------
// 
// Filename:      ds18b20.c
// Version:       1.2
// Date:          01/11/2011
// Author:        Joel Guittet - http://myfreescalewebpage.free.fr
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Description
//
// This files contains the functions used to communicate with the DS18B20 temperature
// sensor throw the 1-Wire interface.
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Revisions
//
// Version	| Author		| Description
// --------------------------------------------------------------------------------------
// 1.0      | Joel Guittet  | Initial Release
// 1.1		| Joel Guittet	| Coding improvements
// 1.1		| Joel Guittet	| Modification of DS18B20ReadT to return the device status
// 1.2      | Joel Guittet  | Coding improvements
// 1.2      | Joel Guittet  | Modifications to use "typedef.h"
//
/////////////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------------

#include "ds18b20.h"


//---------------------------------------------------------------------------------------
// Name:        DS18B20_Init
// Param:    	Resolution: DS18B20 resolution (9, 10, 11 or 12 bits)
// Return:      1-Wire Reset result: NO_DEVICE_DETECTED, DEVICE_PRESENT or DEVICE_SHORTED
//
// Description:	Initialization of the DS18B20 device
//---------------------------------------------------------------------------------------
t_OneWireResetResult DS18B20_Init(uint8_t u8Resolution)
{
	t_OneWireResetResult xResult;
	
	/* First initialize the 1-Wire interface */
	ONEWIRE_Init();
	
	/* Check the resolution */
	if (u8Resolution < 9 || u8Resolution > 12) return NO_DEVICE_DETECTED;
	
	/* Convert the resolution */
	u8Resolution = 0x1F + ((u8Resolution - 9) << 5);
	
	/* To write in the scratchpad, perform a 1-wire reset */
	xResult = ONEWIRE_Reset();
	
	if (xResult == DEVICE_PRESENT)
	{
		ONEWIRE_WriteByte(0xCC);				/* Skip ROM 		  */
		ONEWIRE_WriteByte(0x4E);            	/* Write Scratchpad   */
		ONEWIRE_WriteByte(0xFF);            	/* TH 				  */
		ONEWIRE_WriteByte(0x00);            	/* TL 				  */
		ONEWIRE_WriteByte(u8Resolution);		/* DS18B20 resolution */
		(void)ONEWIRE_Reset();               	/* 1-wire reset 	  */
		ONEWIRE_WriteByte(0xCC);             	/* Skip ROM 		  */
		ONEWIRE_WriteByte(0x48);             	/* Copy Scratchpad 	  */
	}
	
	return xResult;
}


//---------------------------------------------------------------------------------------
// Name:        DS18B20_ConvertT
// Param:		-
// Return:      1-Wire Reset result: NO_DEVICE_DETECTED, DEVICE_PRESENT or DEVICE_SHORTED
//
// Description:	Initiate a temperature conversion if the device is present and not shorted
//---------------------------------------------------------------------------------------
t_OneWireResetResult DS18B20_ConvertT(void)
{
	t_OneWireResetResult xResult;
	
	xResult = ONEWIRE_Reset();
	
	if (xResult == DEVICE_PRESENT)
	{
		ONEWIRE_WriteByte(0xCC);            	/* Skip ROM										  */
		ONEWIRE_WriteByte(0x44);            	/* ConvertT										  */
		ONEWIRE_SetStrongPullUp();          	/* Set Strong Pull-Up to power the DS18B20 device */
	}
	
	return xResult;
}


//---------------------------------------------------------------------------------------
// Name:        DS18B20_ReadT
// Param:		Temperature: contain the temperature returned by the sensor, if present
// Return:      1-Wire Reset result: NO_DEVICE_DETECTED, DEVICE_PRESENT or DEVICE_SHORTED
//
// Description:	Read the result of the last temperature conversion (see function DS18B20_ConvertT)
//---------------------------------------------------------------------------------------
t_OneWireResetResult DS18B20_ReadT(uint16_t * pu16Temperature)
{
	t_OneWireResetResult xResult;
	uint8_t u8LSB, u8MSB;
		
	xResult = ONEWIRE_Reset();
	
	//To read the memory map of the DS18B20, execute a 1-wire reset 
	if (xResult == DEVICE_PRESENT)
	{
		ONEWIRE_WriteByte(0xCC);            	/* Skip ROM								  		  */
		ONEWIRE_WriteByte(0xBE);            	/* Read DS18B20 memory map						  */
		
		u8LSB = ONEWIRE_ReadByte();        		/* Temperature LSB								  */
		u8MSB = ONEWIRE_ReadByte();        		/* Temperature MSB								  */
		
		(void)ONEWIRE_Reset();              	/* Reset the device to end reading the memory map */
		
		/* Temperature from the DS18B20 device  */
		*pu16Temperature = u8LSB + 256 * u8MSB;
	}
	
	return xResult;
}
