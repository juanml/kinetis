/////////////////////////////////////////////////////////////////////////////////////////
//
// DS18B20 Library V1
//
// --------------------------------------------------------------------------------------
// 
// Filename:      ds18b20.h
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
// 1.2      | Joel Guittet  | Coding improvements
// 1.2      | Joel Guittet  | Creation of the file "ds18b20.h"
// 1.2      | Joel Guittet  | Modifications to use "typedef.h"
//
/////////////////////////////////////////////////////////////////////////////////////////


#ifndef DS18B20_H_
#define DS18B20_H_


//---------------------------------------------------------------------------------------
// Include
//---------------------------------------------------------------------------------------

#include "MKL05Z4.h"
#include "1-wire.h"


//---------------------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------------------

t_OneWireResetResult DS18B20_Init(uint8_t u8Resolution);
t_OneWireResetResult DS18B20_ConvertT(void);
t_OneWireResetResult DS18B20_ReadT(uint16_t * pu16Temperature);


#endif
