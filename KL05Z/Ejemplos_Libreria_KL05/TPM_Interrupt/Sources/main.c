/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL05Z4.h"
#include "gpio.h"
#include "lptmr.h"
#include "tpm.h"
#include "adc.h"
#include "clk.h"

#define TPM_MODULE  65000

static int clk = 0;
uint16_t cuenta = 0;

int main(void)
{

	SIM_COPC = 0x00;						//Deshabilito el watchdog
	CLK_init();		//Activo relojes de PORTA y PORTB, Core Clock = 47.972.352 Hz, Bus Clock = 23.986.176 Hz

	SystemCoreClockUpdate();
	clk = SystemCoreClock;

	GPIO_Init(PORT_A, 10, IO_MUX);

	GPIO_IO(PORT_A, 10, OUTPUT);

	TPM_init(TPM1, TPM_MCGFLLCLK, TPM_MODULE, TPM_CLK, PS_128, COUNT_UP);

	TPM_setTOFint(TPM1);

    for (;;) {
    	cuenta = TPM_getCount(TPM1);
    }
    /* Never leave main */
    return 0;
}

void TPM1_IRQHandler(void)
{
	TPM_clearFlagTOF(TPM1);
	GPIO_Toggle(PORT_A, 10); //Toggle PTA10
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
