#include "lcd_kinetis.h"

// Display configuration global variable
static char lcd_mode;	

void LCD_init(char mode1, char mode2)
{
	char aux;
    //SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK;       // enable clock to Port A and Port B
    PORTA_PCR8 = PORT_PCR_MUX(1);		// PTA8 GPIO
    PORTA_PCR9 = PORT_PCR_MUX(1);		// PTA9 GPIO
    PORTA_PCR11 = PORT_PCR_MUX(1);		// PTA11 GPIO
    PORTB_PCR4 = PORT_PCR_MUX(1);		// PTB4 GPIO
    PORTA_PCR12 = PORT_PCR_MUX(1);		// PTA12 GPIO
    PORTB_PCR12 = PORT_PCR_MUX(1);		// PTB12 GPIO
    //PORTA_PCR13 = PORT_PCR_MUX(1);		// PTA13 GPIO
    GPIOA_PDDR |= LCD_ENABLE|LCD_RS|LCD_D4|LCD_D6/*|LCD_D7*/;
    GPIOB_PDDR |= LCD_D5|LCD_D7;

	// Set the LCD data pins to zero
	LCD_ENABLE_OFF;
	LCD_RS_OFF;
	LCD_D4_OFF;
	LCD_D5_OFF;
	LCD_D6_OFF;
	LCD_D7_OFF;

	time_delay_ms(50);			//Secuencia de inicializacion
    
	// LCD 4-bit mode initialization sequence
	// send three times 0x03 and then 0x02 to finish configuring the LCD
	for(aux=0;aux<3;++aux)
	{		
	  LCD_send_nibble(3);
	  time_delay_ms(5);
	}
	LCD_send_nibble(2);
	// Now send the LCD configuration data
	LCD_send_byte(0,0x20 | mode1);
	LCD_send_byte(0,0x08 | mode2);
	lcd_mode = 0x08 | mode2;
	LCD_send_byte(0,1);
	LCD_send_byte(0,6);
}

//**************************************************************************
//* LCD cursor position set
//**************************************************************************
//* Calling arguments:
//* char x : column (starting by 0)
//* char y : line (0 or 1)
//**************************************************************************
void LCD_pos_xy(char x, char y)
{
  char address;
  if (y) address = LCD_SEC_LINE; else address = 0;
  address += x;
  LCD_send_byte(0,0x80|address);
}

//**************************************************************************
//* Write a character on the display
//**************************************************************************
//* Calling arguments:
//* char c : character to be written
//**************************************************************************
//* Notes :
//* \f clear the display
//* \n and \r return the cursor to line 1 column 0
//**************************************************************************
void LCD_write_char(char c)
{
  switch (c)
	{
	  case '\f' :	
	    LCD_send_byte(0,1);
	    time_delay_ms(5);
	    break;
	  case '\n' :
	  case '\r' :	
	    LCD_pos_xy(0,1);
	    break;
	  case RightShiftCmd :
		LCD_send_byte(0,c);
		break;
	  default:
	    LCD_send_byte(1,c);
   }
}

//**************************************************************************
//* Write a string on the display
//**************************************************************************
//* Calling arguments:
//* char *c : pointer to the string
//**************************************************************************
void LCD_write_string (char *c)
{
	while (*c)
	{
	  LCD_write_char(*c);
	  c++;
	}
}

//**************************************************************************
//* Turn the display on
//**************************************************************************
void LCD_display_on(void)
{
	lcd_mode |= 4;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn the display off
//**************************************************************************
void LCD_display_off(void)
{
	lcd_mode &= 0b11111011;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn the cursor on
//**************************************************************************
void LCD_cursor_on(void)
{
  lcd_mode |= 2;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn the cursor off
//**************************************************************************
void LCD_cursor_off(void)
{
	lcd_mode &= 0b11111101;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn on the cursor blink function
//**************************************************************************
void LCD_cursor_blink_on(void)
{
	lcd_mode |= 1;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Turn off the cursor blink function
//**************************************************************************
void LCD_cursor_blink_off(void)
{
	lcd_mode &= 0b11111110;
	LCD_send_byte (0,lcd_mode);
}

//**************************************************************************
//* Send a nibble to the LCD
//**************************************************************************
//* Calling arguments
//* char data : data to be sent to the display
//**************************************************************************
void LCD_send_nibble(char data)
{
	uint8_t bit0_data, bit1_data, bit2_data, bit3_data;

	bit0_data = (data & (1U << 0)) ? 1 : 0 ;
	bit1_data = (data & (1U << 1)) ? 1 : 0 ;
	bit2_data = (data & (1U << 2)) ? 1 : 0 ;
	bit3_data = (data & (1U << 3)) ? 1 : 0 ;

	if (bit3_data == 1)
	{
		LCD_D7_ON;
	} else
	{
		LCD_D7_OFF;
	}
	if (bit2_data == 1)
	{
		LCD_D6_ON;
	} else
	{
		LCD_D6_OFF;
	}
	if (bit1_data == 1)
	{
		LCD_D5_ON;
	} else
	{
		LCD_D5_OFF;
	}
	if (bit0_data == 1)
	{
		LCD_D4_ON;
	} else
	{
		LCD_D4_OFF;
	}

	// pulse the LCD enable line
	LCD_ENABLE_ON;
	Delay_Waitus(1);
	LCD_ENABLE_OFF;
}

//**************************************************************************
//* Write a byte into the LCD
//**************************************************************************
//* Calling arguments:
//* char address : 0 for instructions, 1 for data
//* char data : command or data to be written
//**************************************************************************
void LCD_send_byte(char address, char data)
{
	if (address == 1)
	{
		LCD_RS_ON;
	} else
	{
		LCD_RS_OFF;
	}
	LCD_ENABLE_OFF;                 // set LCD enable line to 0
	LCD_send_nibble(data >> 4);     // send the higher nibble
	LCD_send_nibble(data & 0x0f);   // send the lower nibble
	time_delay_ms(6);
}

//**************************************************************************
//* Create a custom character
//**************************************************************************
//* Calling arguments:
//* uint8_t location : location where you want to store
//					   (0,1,2,....7)
//* uint8_t *ptr : Pointer to pattern data
//
//*				   0x40-0x47 pattern for character 00
//				   0x48-0x4f pattern for character 01
//				   0x50-0x57 pattern for character 02
//				   0x58-0x5f pattern for character 03
//				   0x60-0x67 pattern for character 04
//				   0x68-0x6f pattern for character 05
//				   0x70-0x77 pattern for character 06
//				   0x78-0x7f pattern for character 07
//**************************************************************************

void LCD_Set_CustomChar(uint8_t location, uint8_t *ptr)
	{
		uint8_t i;
		if (location<8)
			{
				LCD_send_byte(0, 0x40+(location*8));
				for(i=0;i<8;i++)
				   LCD_send_byte(1, ptr[ i ]);
			}
	}
