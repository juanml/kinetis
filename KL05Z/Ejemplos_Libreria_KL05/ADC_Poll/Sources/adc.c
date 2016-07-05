/*
 * File:        adc.c
 * Purpose:     Provide common adc routines
 *
 * Notes:       
 *              
 */

#include "MKL05Z4.h"


/****************************************************************
*                  Inicialización el ADC
*****************************************************************/
void ADC_init(uint8_t power, uint8_t clock_div, uint8_t short_long, uint8_t resolution, uint8_t clock_input, uint8_t adco_mode)
{
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;  			// Activo el clock del ADC0

  	ADC0_CFG1 |= ADC_CFG1_ADLPC(power)|			// Normal o Low Power
  				ADC_CFG1_ADIV(clock_div)|       // Divisor del clock (1, 2, 4 ,8)
  				ADC_CFG1_MODE(resolution)|		// Resolucion (8, 10, 12 bits)
                ADC_CFG1_ADLSMP(short_long)|	// Muestreo corto o muestreo largo
  				ADC_CFG1_ADICLK(clock_input);   // Fuente de clock (Bus, Bus/2, alternativo, asincronico)

  	ADC0_SC3 |= ADC_SC3_ADCO(adco_mode);		//Modo continuo o simple
}

void ADC_hw_prom(uint8_t avge_mode, uint8_t avgs_samples)
{
  	ADC0_SC3 |= ADC_SC3_AVGE(avge_mode) |		//Promediacion por hardware activada o desactivada
				ADC_SC3_AVGS(avgs_samples);		//Cantidad de muestras promediadas (4, 8, 16, 32)
}

void ADC_pinMux(uint8_t adc_pin)
{
	  switch (adc_pin)
		{
			case 0: PORT_PCR_REG(PORTA_BASE_PTR, 12) = 0; break;
			case 1: PORT_PCR_REG(PORTB_BASE_PTR, 5) = 0; break;
			case 2: PORT_PCR_REG(PORTA_BASE_PTR, 9) = 0; break;
			case 3: PORT_PCR_REG(PORTA_BASE_PTR, 8) = 0; break;
			case 4: PORT_PCR_REG(PORTB_BASE_PTR, 2) = 0; break;
			case 5: PORT_PCR_REG(PORTB_BASE_PTR, 1) = 0; break;
			case 6: PORT_PCR_REG(PORTB_BASE_PTR, 0) = 0; break;
			case 7: PORT_PCR_REG(PORTA_BASE_PTR, 7) = 0; break;
			case 8: PORT_PCR_REG(PORTB_BASE_PTR, 11) = 0; break;
			case 9: PORT_PCR_REG(PORTB_BASE_PTR, 10) = 0; break;
			case 10: PORT_PCR_REG(PORTB_BASE_PTR, 9) = 0; break;
			case 11: PORT_PCR_REG(PORTB_BASE_PTR, 8) = 0; break;
			case 12: PORT_PCR_REG(PORTA_BASE_PTR, 0) = 0; break;
			case 13: PORT_PCR_REG(PORTB_BASE_PTR, 13) = 0; break;
		}
}

          
/****************************************************************
                      software trigger channel x
*****************************************************************/
unsigned char TriggerADC(unsigned char channel)
{
  
  if(channel == 0x1B)                                          // Bandgap is selected as input
      PMC_REGSC |= PMC_REGSC_BGBE_MASK;                        // Bandgap buffer enabled
   ADC0_SC1A = ADC_SC1_ADCH(channel);                   // update the channel value
   return 1;
}

/****************************************************************
*                      Lectura del ADC en modo encuesta
*****************************************************************/
uint16_t ADC_Read_Poll(uint8_t channel)
{
	ADC0_SC1A = ADC_SC1_ADCH(channel);
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));
    return ADC0_RA;
}

/****************************************************************
*                      Lectura del ADC en modo interrupcion
*****************************************************************/
uint16_t ADC_Read_Int(void)
{
    return ADC0_RA;
}


/****************************************************************
 *
 */
void ADC_disable(void)
{
	ADC0_SC1A = ADC_SC1_ADCH(31) | ADC_SC1_AIEN(0);
	NVIC_DisableIRQ(ADC0_IRQn);
}

void ADC_setCH_Int(uint8_t channel, uint8_t aien_bit)
{
	ADC0_SC1A = ADC_SC1_ADCH(channel) | ADC_SC1_AIEN(aien_bit);
	if (aien_bit)
		{
			NVIC_EnableIRQ(ADC0_IRQn);
		}
	else
		{
			NVIC_DisableIRQ(ADC0_IRQn);
		}
}

/******************************************************************************
Function 1. Name	AUTO CAL ROUTINE   

Parameters		ADC module pointer points to adc0.. adc3 register map 
                         base address.
Returns			Zero indicates success.
Notes         		Calibrates the ADC16. Required to meet specifications 
                        after reset and before a conversion is initiated.
******************************************************************************/
uint8_t ADC_Cal(ADC_MemMapPtr adcmap)
{

  unsigned short cal_var;
  
  SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;  // enable ADC0 clock
  
  ADC_SC2_REG(adcmap) &=  ~ADC_SC2_ADTRG_MASK ; // Enable Software Conversion Trigger for Calibration Process   
  ADC_SC3_REG(adcmap) &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); // set single conversion, clear avgs bitfield for next writing
//For best calibration results
  ADC_SC3_REG(adcmap) |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3) );  // Turn averaging ON and set at max value ( 32 )
  
  ADC_SC3_REG(adcmap) |= ADC_SC3_CAL_MASK ;      // Start CAL
  
//ADC1_SC1A
  while ( (ADC_SC1_REG(adcmap,0) & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK ); // Wait calibration end

 //COCO=1 calibration complete
  if ((ADC_SC3_REG(adcmap)& ADC_SC3_CALF_MASK) == ADC_SC3_CALF_MASK )
  {  
   return(1);    // Check for Calibration fail error and return 
  }
  // Calculate plus-side calibration
  cal_var = 0x00;
  
  cal_var =  ADC_CLP0_REG(adcmap); 
  cal_var += ADC_CLP1_REG(adcmap);
  cal_var += ADC_CLP2_REG(adcmap);
  cal_var += ADC_CLP3_REG(adcmap);
  cal_var += ADC_CLP4_REG(adcmap);
  cal_var += ADC_CLPS_REG(adcmap);

  cal_var = cal_var/2;
  cal_var |= 0x8000; // Set MSB

  ADC_PG_REG(adcmap) = ADC_PG_PG(cal_var);
 
/*
  // Calculate minus-side calibration
  cal_var = 0x00;

  cal_var =  ADC_CLM0_REG(adcmap); 
  cal_var += ADC_CLM1_REG(adcmap);
  cal_var += ADC_CLM2_REG(adcmap);
  cal_var += ADC_CLM3_REG(adcmap);
  cal_var += ADC_CLM4_REG(adcmap);
  cal_var += ADC_CLMS_REG(adcmap);

  cal_var = cal_var/2;

  cal_var |= 0x8000; // Set MSB

  ADC_MG_REG(adcmap) = ADC_MG_MG(cal_var); 
*/  
  
  ADC_SC3_REG(adcmap) &= ~ADC_SC3_CAL_MASK ; /* Clear CAL bit */

  return(0);
}

void ADC_SwitchVref( unsigned char VrefSource )
{
  ADC0_SC2 &= ~ADC_SC2_REFSEL_MASK;
  ADC0_SC2 |= ADC_SC2_REFSEL(VrefSource);
}
