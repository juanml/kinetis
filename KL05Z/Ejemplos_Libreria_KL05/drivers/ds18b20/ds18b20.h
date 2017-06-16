

#include <MKL05Z4.h>


/* check configuration of driver */
#define DS1820_DATAPIN	1


#define TEMP_RES              0x100 /* temperature resolution => 1/256°C = 0.0039°C */


/* -------------------------------------------------------------------------- */
/*                         DS1820 Timing Parameters                           */
/* -------------------------------------------------------------------------- */

#define DS1820_RST_PULSE       480   /* master reset pulse time in [us] */
#define DS1820_MSTR_BITSTART   2     /* delay time for bit start by master */
#define DS1820_PRESENCE_WAIT   90    /* delay after master reset pulse in [40 us] */ 
#define DS1820_PRESENCE_FIN    480   /* dealy after reading of presence pulse [us] */
#define DS1820_BITREAD_DLY     5     /* bit read delay */
#define DS1820_BITWRITE_DLY    100   /* bit write delay */


/* -------------------------------------------------------------------------- */
/*                            DS1820 Registers                                */
/* -------------------------------------------------------------------------- */

#define DS1820_REG_TEMPLSB    0
#define DS1820_REG_TEMPMSB    1
#define DS1820_REG_CNTREMAIN  6
#define DS1820_REG_CNTPERSEC  7
#define DS1820_SCRPADMEM_LEN  9     /* length of scratchpad memory */

#define DS1820_ADDR_LEN       8


/* -------------------------------------------------------------------------- */
/*                            DS1820 Commands                                 */
/* -------------------------------------------------------------------------- */

#define DS1820_CMD_SEARCHROM     0xF0
#define DS1820_CMD_READROM       0x33
#define DS1820_CMD_MATCHROM      0x55
#define DS1820_CMD_SKIPROM       0xCC
#define DS1820_CMD_ALARMSEARCH   0xEC
#define DS1820_CMD_CONVERTTEMP   0x44
#define DS1820_CMD_WRITESCRPAD   0x4E
#define DS1820_CMD_READSCRPAD    0xBE
#define DS1820_CMD_COPYSCRPAD    0x48
#define DS1820_CMD_RECALLEE      0xB8


#define DS1820_FAMILY_CODE_DS18B20      0x28
#define DS1820_FAMILY_CODE_DS18S20      0x10

//#define TRUE 1
//#define FALSE 0

/* -------------------------------------------------------------------------- */
/*                            static variables                                */
/* -------------------------------------------------------------------------- */

static uint8_t bDoneFlag;
static uint8_t nLastDiscrepancy_u8;
static uint8_t nRomAddr_au8[DS1820_ADDR_LEN];

void DS1820_DelayUs(int32_t dly_us);
void DS1820_DelayMs(int32_t dly_ms);
void output_low(uint8_t pin);
void output_high(uint8_t pin);
uint8_t input(uint8_t pin);
uint8_t DS1820_Reset(void);
uint8_t DS1820_ReadBit(void);
void DS1820_WriteBit(uint8_t bBit);
uint8_t DS1820_ReadByte(void);
uint8_t DS1820_ReadByte(void);
void DS1820_WriteByte(uint8_t val_u8);
void DS1820_AddrDevice(uint8_t nAddrMethod);
uint8_t DS1820_FindNextDevice(void);
uint8_t DS1820_FindFirstDevice(void);
void DS1820_WriteEEPROM(uint8_t nTHigh, uint8_t nTLow);
int16_t DS1820_GetTempRaw(void);
float DS1820_GetTempFloat(void);
void DS1820_GetTempString(int16_t tRaw_s16, uint8_t *strTemp_pc);
