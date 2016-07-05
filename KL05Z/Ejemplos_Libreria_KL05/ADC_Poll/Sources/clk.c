/*
 * clk.c
 *
 *  Created on: 25/5/2016
 *      Author: Juan
 */

#include "clk.h"

void CLK_init(void)
{
	/* System clock initialization */
	  /* SIM_CLKDIV1: OUTDIV1=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=3,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
	  SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0x00) | SIM_CLKDIV1_OUTDIV4(0x03)); /* Set the system prescalers to safe value */
	  /* SIM_SCGC5: PORTB=1,PORTA=1 */
	  SIM_SCGC5 |= (SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTA_MASK); /* Enable clock gate for ports to enable pin routing */
	  if ((PMC_REGSC & PMC_REGSC_ACKISO_MASK) != 0x0U) {
	    /* PMC_REGSC: ACKISO=1 */
	    PMC_REGSC |= PMC_REGSC_ACKISO_MASK; /* Release IO pads after wakeup from VLLS mode. */
	  }
	  /* SIM_CLKDIV1: OUTDIV1=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
	  SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(0x00) | SIM_CLKDIV1_OUTDIV4(0x01)); /* Update system prescalers */
	  /* SIM_SOPT1: OSC32KSEL=0 */
	  SIM_SOPT1 &= (uint32_t)~(uint32_t)(SIM_SOPT1_OSC32KSEL(0x03)); /* System oscillator drives 32 kHz clock for various peripherals */
	  /* SIM_SOPT2: TPMSRC=1 */
	  SIM_SOPT2 = (uint32_t)((SIM_SOPT2 & (uint32_t)~(uint32_t)(
	               SIM_SOPT2_TPMSRC(0x02)
	              )) | (uint32_t)(
	               SIM_SOPT2_TPMSRC(0x01)
	              ));                      /* Set the TPM clock */
	  /* PORTA_PCR3: ISF=0,MUX=0 */
	  PORTA_PCR3 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
	  /* PORTA_PCR4: ISF=0,MUX=0 */
	  PORTA_PCR4 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
	  /* Switch to FEE Mode */
	  /* MCG_C2: LOCRE0=0,??=0,RANGE0=0,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
	  MCG_C2 = (MCG_C2_RANGE0(0x00) | MCG_C2_EREFS0_MASK);
	  /* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
	  OSC0_CR = OSC_CR_ERCLKEN_MASK;
	  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
	  MCG_C1 = (MCG_C1_CLKS(0x00) | MCG_C1_FRDIV(0x00) | MCG_C1_IRCLKEN_MASK);
	  /* MCG_C4: DMX32=1,DRST_DRS=1 */
	  MCG_C4 = (uint8_t)((MCG_C4 & (uint8_t)~(uint8_t)(
	            MCG_C4_DRST_DRS(0x02)
	           )) | (uint8_t)(
	            MCG_C4_DMX32_MASK |
	            MCG_C4_DRST_DRS(0x01)
	           ));
	  while((MCG_S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
	  }
	  while((MCG_S & 0x0CU) != 0x00U) {    /* Wait until output of the FLL is selected */
	  }
	  /*** End of PE initialization code after reset ***/
}
