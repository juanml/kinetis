/*
 * File:        uart.c
 * Purpose:     Provide common uart routines for serial IO
 *
 * Notes:       
 *              
 */

#include "MKL25Z4.h"
#include "uart.h"
#include <stdarg.h>

/********************************************************************/
/*
 * Initialize the uart for 8N1 operation, interrupts disabled, and
 * no hardware flow-control
 *
 * NOTE: Since the uarts are pinned out in multiple locations on most
 *       Kinetis devices, this driver does not enable uart pin functions.
 *       The desired pins should be enabled before calling this init function.
 *
 * Parameters:
 *  uartch      uart channel to initialize
 *  sysclk      uart module Clock in kHz(used to calculate baud)
 *  baud        uart baud rate
 */
void uart_init (UART_MemMapPtr uartch, int sysclk, int baud)
{
    register uint16 sbr;
    uint8 temp;
                                
         
      if (uartch == UART1_BASE_PTR)
        SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
      else
    	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
      /* Make sure that the transmitter and receiver are disabled while we 
       * change settings.
       */
      UART_C2_REG(uartch) &= ~(UART_C2_TE_MASK
				| UART_C2_RE_MASK );

      /* Configure the uart for 8-bit mode, no parity */
      UART_C1_REG(uartch) = 0;	/* We need all default settings, so entire register is cleared */
    
      /* Calculate baud settings */
      sbr = (uint16)((sysclk*1000)/(baud * 16));
        
      /* Save off the current value of the uartx_BDH except for the SBR field */
      temp = UART_BDH_REG(uartch) & ~(UART_BDH_SBR(0x1F));
    
      UART_BDH_REG(uartch) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
      UART_BDL_REG(uartch) = (uint8)(sbr & UART_BDL_SBR_MASK);
  
      /* Enable receiver and transmitter */
      UART_C2_REG(uartch) |= (UART_C2_TE_MASK
	    		  | UART_C2_RE_MASK );
    
}
/********************************************************************/
/*
 * Wait for a character to be received on the specified uart
 *
 * Parameters:
 *  channel      uart channel to read from
 *
 * Return Values:
 *  the received character
 */
char uart_getchar (UART_MemMapPtr channel)
{
      /* Wait until character has been received */
      while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK));
    
      /* Return the 8-bit data from the receiver */
      return UART_D_REG(channel);
}
/********************************************************************/
/*
 * Wait for space in the uart Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      uart channel to send to
 *  ch			 character to send
 */ 
void uart_putchar (UART_MemMapPtr channel, char ch)
{
      /* Wait until space is available in the FIFO */
      while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));
    
      /* Send the character */
      UART_D_REG(channel) = (uint8)ch;
    
 }
/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      uart channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart_getchar_present (UART_MemMapPtr channel)
{
    return (UART_S1_REG(channel) & UART_S1_RDRF_MASK);
}
/********************************************************************/

/***************************************************************************
 * Begin UART0 functions
 **************************************************************************/
/*
 * @brief Sets up the UART0 for 115.2 kbaud on PTA1/RX, PTA2/TX using PLL/2 clocking.
 */
void InitUart0()
{
	/*
	static const uint32_t uartclk_hz = CORE_CLOCK/2;
	static const uint32_t baud_rate = 115200U;
	*/

#if UART_SPEED_MODE == UART_115200
#pragma message "Configuring UART0 in 115.200 baud mode."

	/* 115200 baud: sbr 13, osr 15 is known to work */
	static const uint16_t sbr = 13U;
	static const uint8_t osr = 15U;
#elif UART_SPEED_MODE == UART_230400
#pragma message "Configuring UART0 in 230.400 baud mode."

	/* 230400 baud: sbr 7, osr 15 */
	static const uint16_t sbr = 7U;
	static const uint8_t osr  = 15U;
#elif UART_SPEED_MODE == UART_DEV
	static const uint16_t sbr = 39U;    // 38400 baud
	static const uint8_t osr  = 15U;
#else
#error No UART speed configured
#endif

	/*
	uint32_t calculated_baud = uartclk_hz / ((osr+1)*sbr);
	int32_t difference = (calculated_baud - baud_rate);
	if (calculated_baud < baud_rate)
	{
		difference = (baud_rate - calculated_baud);
	}
	const int8_t valid = difference < (baud_rate/100*3);
	*/

	/* enable clock gating to uart0 module */
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

	/* disable rx and tx */
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	/* set uart clock to PLL/2 clock */
#if UART_SPEED_MODE == UART_115200
	SIM->SOPT2 &= ~(SIM_SOPT2_UART0SRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK);
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0b01U) | SIM_SOPT2_PLLFLLSEL_MASK;
#elif UART_SPEED_MODE == UART_230400
	SIM->SOPT2 &= ~(SIM_SOPT2_UART0SRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK);
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0b01U) | SIM_SOPT2_PLLFLLSEL_MASK;
#elif UART_SPEED_MODE == UART_DEV
	SIM->SOPT2 &= ~(SIM_SOPT2_UART0SRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK);
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0b01U) | SIM_SOPT2_PLLFLLSEL_MASK;
#else
#error No UART speed configured
#endif

	/* enable clock gating to port A */
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; /* enable clock to port A (PTA1=rx, PTA2=tx) */

	/* set pins to uart0 rx/tx */
	/* not using |= assignment here due to some of the flags being undefined at reset */
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);	/* alternative 2: RX */
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);	/* alternative 2: TX */

	/* configure the uart */
	UART0->BDH =  (0 << UART_BDH_LBKDIE_SHIFT) /* disable line break detect interrupt */
				| (0 << UART_BDH_RXEDGIE_SHIFT) /* disable RX input active edge interrupt */
				| (0 << UART_BDH_SBNS_SHIFT) /* use one stop bit */
				| UART_BDH_SBR((sbr & 0x1F00) >> 8); /* set high bits of scaler */
	UART0->BDL = UART_BDL_SBR(sbr & 0x00FF) ; /* set low bits of scaler */

	/* set oversampling ratio */
	UART0->C4 &= ~UART0_C4_OSR_MASK;
	UART0->C4 |= UART0_C4_OSR(osr);

	/* set oversampling ratio when oversampling is between 4 and 7
	 * (it is optional for higher oversampling ratios) */
#if UART_SPEED_MODE == UART_115200
    UART0->C5 = 0;
#elif UART_SPEED_MODE == UART_230400
	UART0->C5 = 0;
#elif UART_SPEED_MODE == UART_DEV
	UART0->C5 = 0;
#else
	if (osr >= 3 && osr <= 7)
	{
		UART0->C5 = UART0_C5_BOTHEDGE_MASK;
	}
	else {
		UART0->C5 = 0;
	}
#endif

	/* keep default settings for parity and loopback */
	UART0->C1 = 0;

	UART0->C3 = 0;

	/* clear flags to avoid unexpected behaviour */
	UART0->MA1 = 0;
	UART0->MA2 = 0;
	UART0->S1 |= UART0_S1_IDLE_MASK
            | UART0_S1_OR_MASK
            | UART0_S1_NF_MASK
            | UART0_S1_FE_MASK
            | UART0_S1_PF_MASK;
	UART0->S2 = (UART0_S2_LBKDIF_MASK | UART0_S2_RXEDGIF_MASK);

	/*UART0->C1 |= UART0_C1_LOOPS_MASK;*/

	/* enable rx and tx */
	UART0->C2 |= UART0_C2_TE_MASK | UART0_C2_RE_MASK;
}
/********************************************************************/
/*
 * Wait for a character to be received on the specified uart
 *
 * Parameters:
 *  channel      uart channel to read from
 *
 * Return Values:
 *  the received character
 */
char uart0_getchar (UART0_MemMapPtr channel)
{
      /* Wait until character has been received */
      while (!(UART0_S1_REG(channel) & UART0_S1_RDRF_MASK));
    
      /* Return the 8-bit data from the receiver */
      return UART0_D_REG(channel);
}
/********************************************************************/
/*
 * Wait for space in the uart Tx FIFO and then send a character
 *
 * Parameters:
 *  ch			 character to send
 */ 

void uart0_putchar(uint8_t ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART0->S1 & UART0_S1_TDRE_MASK));

    /* Send the char */
    UART0->D = ch;
}
/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      uart channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart0_getchar_present (UART0_MemMapPtr channel)
{
    return (UART0_S1_REG(channel) & UART0_S1_RDRF_MASK);
}
/********************************************************************/

void uart0_putstr(const uint8_t *str)
{
    while(*str != '\0')
    {
        uart0_putchar(*str++);
    }
}
