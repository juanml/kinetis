#include "MKL05Z4.h"
#include "lptmr.h"
#include "Delay.h"

// The following defines set the default pins for the LCD display

#define LCD_ENABLE		(1<<8)    // LCD enable pin on PTA8 (Pin 19)
#define LCD_RS			(1<<9)	   // LCD r/s pin on PTA9	(Pin 20)
#define LCD_D4	        (1<<11)    // LCD data D4 pin PTA11	(Pin 22)
#define LCD_D5          (1<<4)    // LCD data D5 pin PTB5	(Pin 25)
#define LCD_D6          (1<<12)    // LCD data D6 pin PTA12 (Pin 26)
#define LCD_D7          (1<<12)    // LCD data D7 pin PTA13	(Pin 27)


// Funciones para setear y borrar los pines del LCD

#define LCD_ENABLE_ON   GPIOA_PSOR = LCD_ENABLE
#define LCD_ENABLE_OFF  GPIOA_PCOR = LCD_ENABLE
#define LCD_RS_ON		GPIOA_PSOR = LCD_RS
#define LCD_RS_OFF		GPIOA_PCOR = LCD_RS
#define LCD_D4_ON       GPIOA_PSOR = LCD_D4
#define LCD_D4_OFF      GPIOA_PCOR = LCD_D4
#define LCD_D5_ON       GPIOB_PSOR = LCD_D5
#define LCD_D5_OFF      GPIOB_PCOR = LCD_D5
#define LCD_D6_ON       GPIOA_PSOR = LCD_D6
#define LCD_D6_OFF      GPIOA_PCOR = LCD_D6
#define LCD_D7_ON       GPIOB_PSOR = LCD_D7
#define LCD_D7_OFF      GPIOB_PCOR = LCD_D7

#define LCD_SEC_LINE    0x40    // Address of the second line of the LCD

// LCD configuration constants
#define CURSOR_ON       2
#define CURSOR_OFF      0
#define CURSOR_BLINK    1
#define CURSOR_NOBLINK  0
#define DISPLAY_ON      4
#define DISPLAY_OFF     0
#define DISPLAY_8X5     0
#define DISPLAY_10X5    4
#define _2_LINES        8
#define _1_LINE         0

#define RightShiftCmd      0x1C
#define LeftShiftCmd       0x18
#define RightShiftCursor   0x14
#define LeftShiftCursor    0x10

//**************************************************************************
//* Prototypes
//**************************************************************************
void LCD_send_nibble(char data);
void LCD_send_byte(char address, char data);
void LCD_init(char mode1, char mode2);
void LCD_pos_xy(char x, char y);
void LCD_write_char(char c);
void LCD_write_string (char *c);
void LCD_display_on(void);
void LCD_display_off(void);
void LCD_cursor_on(void);
void LCD_cursor_off(void);
void LCD_cursor_blink_on(void);
void LCD_cursor_blink_off(void);
