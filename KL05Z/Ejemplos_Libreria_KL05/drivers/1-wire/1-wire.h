/////////////////////////////////////////////////////////////////////////////////////////
//
// 1-Wire Library V1
//
// --------------------------------------------------------------------------------------
//
// Filename:      1-wire.h 
// Version:       1.2
// Date:          01/11/2011
// Author:        Joel Guittet - http://myfreescalewebpage.free.fr
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Revisions
//
// Version	| Author		| Description
// --------------------------------------------------------------------------------------
// 1.0      | Joel Guittet  | Initial Release
// 1.1		| Joel Guittet	| Coding improvements
// 1.1		| Joel Guittet	| Modification of ONE_WIRE_DELAY to use TPMV3 peripheral
// 1.1		| Joel Guittet	| Modification of DS18B20ReadT to return the device status
// 1.2      | Joel Guittet  | Coding improvements
// 1.2      | Joel Guittet  | Creation of the file "ds18b20.h"
// 1.2      | Joel Guittet  | Modifications to use "typedef.h"
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef ONEWIRE_H_
#define ONEWIRE_H_

typedef unsigned char						BOOLEAN;

//---------------------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------------------

#include "MKL05Z4.h"


//---------------------------------------------------------------------------------------
// Definitions
//---------------------------------------------------------------------------------------

/* Pin and Pin Direction definitions (can be modified to use another pin on the microcontroller) */
#define ONEWIRE_PIN              			0//PTED_PTED3
//#define ONEWIRE_DIR	         				PTEDD_PTEDD3

/* 1-Wire macros */
#define ONEWIRE_SET_LOW          				GPIOB->PDDR |= (1<<ONEWIRE_PIN); GPIOB->PCOR |= (1<<ONEWIRE_PIN);
#define ONEWIRE_SET_HIGH         				GPIOB->PCOR |= (1<<ONEWIRE_PIN); GPIOB->PDDR &= ~(1<<ONEWIRE_PIN);
#define ONEWIRE_SET_STRONG_PU				   	GPIOB->PSOR |= (1<<ONEWIRE_PIN); GPIOB->PDDR |= (1<<ONEWIRE_PIN);

/* MCU Clock Frequency used by 1-Wire functions (MHz) (can be modified) */
//#define BUSCLK             					18

/* 1-Wire Delay macro - 'Delay' value must be given in micro-seconds (maximum value: 3640µs @ 18MHz) */
//#define ONEWIRE_DELAY(u16Delay)				TPM1MOD = u16Delay * BUSCLK; 				\
											TPM1SC = 0b00001000; 						\
											while(!TPM1SC_TOF){__RESET_WATCHDOG();}		\
											TPM1SC &= 0x7F;                          	\
											TPM1SC = 0x00;

/* 1-Wire Reset result, used to know the current device status */
typedef enum
{
	NO_DEVICE_DETECTED,
	DEVICE_PRESENT,
	DEVICE_SHORTED
}
t_OneWireResetResult;


//---------------------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------------------

void ONEWIRE_Init(void);
t_OneWireResetResult ONEWIRE_Reset(void);
void ONEWIRE_WriteByte(uint8_t u8Byte);
uint8_t ONEWIRE_ReadByte(void);
void ONEWIRE_SetStrongPullUp(void);


#endif
