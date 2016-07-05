/*
 * tpm.c
 *
 *  Created on: Jul 16, 2013
 *      Author: B34443
 */

#include "tpm.h"

void TPM_init(TPM_MemMapPtr TPMx, uint8_t  clock_source, uint16_t module, uint8_t clock_mode, uint8_t ps, uint8_t counting_mode)
{
	if(TPMx == TPM0_BASE_PTR)
		SIM_SCGC6	|= SIM_SCGC6_TPM0_MASK;
	else if(TPMx == TPM1_BASE_PTR)
		SIM_SCGC6	|= SIM_SCGC6_TPM1_MASK;

	SIM_SOPT2	|= SIM_SOPT2_TPMSRC(clock_source);

	TPM_MOD_REG(TPMx)  	=  module;

	TPM_SC_REG(TPMx)	|= TPM_SC_CMOD(clock_mode) | TPM_SC_PS(ps);

	if(counting_mode)
		TPM_SC_REG(TPMx) |= TPM_SC_CPWMS_MASK;

}

void TPM_pinMux(uint32_t port, uint8_t bit)
{
  switch (port)
	{
		case PORTA_BASE: PORT_PCR_REG(PORTA_BASE_PTR, bit) = PORT_PCR_MUX(2); break;
	  	case PORTB_BASE: PORT_PCR_REG(PORTB_BASE_PTR, bit) = PORT_PCR_MUX(2); break;
	}
}

void TPM_setTOFint(TPM_MemMapPtr TPMx)
{
    TPM_SC_REG(TPMx) |= TPM_SC_TOIE_MASK;
    NVIC_EnableIRQ(TPM1_IRQn);
}

void TPM_disableTOFint(TPM_MemMapPtr TPMx)
{
	TPM_SC_REG(TPMx) &= ~TPM_SC_TOIE_MASK;
    NVIC_DisableIRQ(TPM1_IRQn);
}

void TPM_clearFlagTOF(TPM_MemMapPtr TPMx)
{
	TPM_SC_REG(TPMx) |= TPM_SC_TOF_MASK;
}

void TPM_waitTOF(TPM_MemMapPtr TPMx)
{
	 while((TPM_SC_REG(TPMx) & TPM_SC_TOF_MASK)!=TPM_SC_TOF_MASK);//Poll TOF bit
	 TPM_SC_REG(TPMx) |= TPM_SC_TOF_MASK;//clear TOF
}

void TPM_stop(TPM_MemMapPtr TPMx)
{
	TPM_SC_REG(TPMx)	|= TPM_SC_CMOD(TPM_DISABLE);
}

void TPM_start(TPM_MemMapPtr TPMx)
{
	TPM_stop(TPMx);
	TPM_CNT_REG(TPMx) = 0;
	TPM_resume(TPMx);
}

void TPM_resume(TPM_MemMapPtr TPMx)
{
	TPM_SC_REG(TPMx)	|= TPM_SC_CMOD(TPM_CLK);
}

void TPM_CH_init(TPM_MemMapPtr TPMx, uint8_t channel, uint8_t mode)
{
	TPM_CnSC_REG(TPMx, channel) |= mode;
}

void TPM_setDuty(TPM_MemMapPtr TPMx, uint8_t channel, uint16_t value)
{
	TPM_CnV_REG(TPMx, channel) = value;
}

