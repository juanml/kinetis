/*
 * File:		adc.h
 * Purpose:     
 *
 * Notes:
 */


/*
 * Definiciones para la funcion ADC_init
 */
#define ADC_NORMAL		0
#define ADC_LOW_POWER	1

#define ADC_CLK_DIV1	0
#define ADC_CLK_DIV2	1
#define ADC_CLK_DIV4	2
#define ADC_CLK_DIV8	3

#define ADC_SHORT_SAMPLE	0
#define	ADC_LONG_SAMPLE		1

#define ADC_RES_8	0
#define	ADC_RES_10	2
#define	ADC_RES_12 	1

#define ADC_BUS_DIV1	0
#define ADC_BUS_DIV2 	1
#define ADC_ALT_CLK		2
#define	ADC_ASC_CLK		3

#define ADC_SINGLE_CONV	0
#define ADC_CONT_CONV	1

#define ADC_HW_PROM_OFF	0
#define ADC_HW_PROM_ON	1

#define ADC_4_SAMPLES	0
#define ADC_8_SAMPLES	1
#define ADC_16_SAMPLES	2
#define ADC_32_SAMPLES	3

/*
 * Definiciones para la funcion ADC_setCH_Int
 */

//Canales del ADC

#define AD0 	0
#define AD1 	1
#define AD2 	2
#define AD3 	3
#define AD4 	4
#define AD5 	5
#define AD6 	6
#define AD7 	7
#define AD8 	8
#define AD9 	9
#define AD10 	10
#define AD11	11
#define AD12	12
#define AD13	13
#define AD14	14
#define AD15	15
#define AD16	16
#define AD17	17
#define AD18	18
#define AD19	19
#define AD20	20
#define AD21	21
#define AD22	22
#define AD23	23
#define TEMP_SENSOR	26 //Temp Sensor (single-ended) is selected as input.
#define BANDGAP 27	   //Bandgap (single-ended) is selected as input.
#define VREFSH	29	   //VREFSH is selected as input. Voltage reference selected is determined by SC2[REFSEL].
#define VREFSL  30	   // VREFSL is selected as input. Voltage reference selected is determined by SC2[REFSEL].
#define DISABLED 31    // Module is disabled.

//Bit AIEN

#define ADC_INT_ON	1
#define ADC_INT_OFF	0

/*
 * Definicion de funciones
 */

void ADC_init(uint8_t power, uint8_t clock_div, uint8_t short_long, uint8_t resolution, uint8_t clock_input, uint8_t adco_mode);

void ADC_pinMux(uint8_t adc_pin);

void ADC_hw_prom(uint8_t avge_mode, uint8_t avgs_samples);

unsigned char ADCAutoCalibration(void);

unsigned char TriggerADC(unsigned char channel);

uint16_t ADC_Read_Poll(uint8_t channel);

uint16_t ADC_Read_Int(void);

void ADC_disable(void);

void ADC_setCH_Int(uint8_t channel, uint8_t aien_bit);

unsigned char  ADCHardwareTriggerSelect(unsigned char HardwareTriggerSource);

uint8_t ADC_Cal(ADC_MemMapPtr adcmap);
void ADC_SwitchVref( unsigned char VrefSource );

/********************************************************************/
