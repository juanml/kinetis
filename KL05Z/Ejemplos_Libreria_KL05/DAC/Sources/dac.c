/*
 * dac.c
 *
 *  Created on: 31/5/2016
 *      Author: Juan
 */

#include "MKL05Z4.h"
#include "dac.h"

void DAC_init(uint8_t dac_en, uint8_t trigger, uint8_t buffer)
{
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;   	//Habilito el clock del DAC
	DAC0->C1 = DAC_C1_DACBFEN(buffer);   	//Configuro buffer
	DAC0->C0 = DAC_C0_DACEN(dac_en) |	 	//Activo o no el DAC
			   DAC_C0_DACTRGSEL(trigger);   //Uso trigger por hardware o software
}

void DAC_Write(uint16_t val)
{
    DAC0->DAT[0].DATL = val & 0xFF;       	//Escribo los 8 bits más bajos
    DAC0->DAT[0].DATH = (val >> 8) & 0x0F;	//Escribo los 8 bits más altos
}


