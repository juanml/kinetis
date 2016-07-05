/*
 * tpm.h
 *
 *  Created on: Jul 16, 2013
 *      Author: B34443
 */

#include "MKL05Z4.h"

#ifndef TPM_H_
#define TPM_H_

#define TPM_MCGFLLCLK 	1
#define TPM_OSCERCLK 	2
#define TPM_MCGIRCLK	3

#define	TPM_DISABLE	0
#define	TPM_CLK		1
#define	TPM_EXT_CLK	2

#define PS_1	0
#define PS_2	1
#define PS_4	2
#define PS_8	3
#define PS_16	4
#define PS_32	5
#define PS_64	6
#define PS_128	7

#define TPM_OC_TOGGLE	TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK
#define TPM_OC_CLR		TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_SET		TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTL		TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTH		TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK

#define TPM_PWM_H 		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK
#define TPM_PWM_L		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK

#define EDGE_PWM		0
#define COUNT_UP		0
#define CENTER_PWM		1
#define	COUNT_DOWN		1

void TPM_init(TPM_MemMapPtr TPMx, uint8_t  clock_source, uint16_t module, uint8_t clock_mode, uint8_t ps, uint8_t counting_mode);
void TPM_setTOFint(TPM_MemMapPtr TPMx);
void TPM_disableTOFint(TPM_MemMapPtr TPMx);
void TPM_clearFlagTOF(TPM_MemMapPtr TPMx);
void TPM_waitTOF(TPM_MemMapPtr TPMx);
void TPM_stop(TPM_MemMapPtr TPMx);
void TPM_start(TPM_MemMapPtr TPMx);
void TPM_resume(TPM_MemMapPtr TPMx);
void TPM_CH_init(TPM_MemMapPtr TPMx, uint8_t channel, uint8_t mode);
void TPM_setDuty(TPM_MemMapPtr TPMx, uint8_t channel, uint16_t value);

#endif /* TPM_H_ */
