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
#include "clk.h"

uint32_t estado = 0, estado1 = 0;

int main(void)
{
	SIM_COPC = 0x00;		//Deshabilito el watchdog
	CLK_init();	//Activo relojes de PORTA y PORTB, Core Clock = 47.972.352 Hz, Bus Clock = 23.986.176 Hz, desactivo WDOG

	GPIO_Init(PORT_A, 11, IO_MUX | PULL_UP | PULL_EN);	//Selecciono MUX de IO para PTA11
	GPIO_Init(PORT_A, 9, IO_MUX | PULL_UP | PULL_EN);	//Selecciono MUX de IO para PTA9
	GPIO_Init(PORT_A, 10, IO_MUX);	//Selecciono MUX de IO para PTA10
	GPIO_Init(PORT_A, 8, IO_MUX);	//Selecciono MUX de IO para PTA8
	GPIO_IO(PORT_A, 11, INPUT);		//Configuro PTA11 como entrada
	GPIO_IO(PORT_A, 9, INPUT);		//Configuro PTA9 como entrada
	GPIO_IO(PORT_A, 10, OUTPUT);	//Configuro PTA10 como salida
	GPIO_IO(PORT_A, 8, OUTPUT);		//Configuro PTA8 como salida
    for (;;) {

    	estado = GPIO_Read(PORT_A, 11);
    	if (!estado)
			{
				GPIO_Set(PORT_A, 10);
			}
    	else if (estado)
			{
				GPIO_Clear(PORT_A, 10);
			}
    	estado1 = GPIO_Read(PORT_A, 9);
    	if (!estado1)
			{
				GPIO_Set(PORT_A, 8);
			}
    	else if (estado1)
			{
				GPIO_Clear(PORT_A, 8);
			}

    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
