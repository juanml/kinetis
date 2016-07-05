/*
 * dac.h
 *
 *  Created on: 31/5/2016
 *      Author: Juan
 */

#ifndef INCLUDES_DAC_H_
#define INCLUDES_DAC_H_

#define DAC_BUFFER_OFF 0
#define DAC_BUFFER_EN 1

#define DAC_OFF	0
#define DAC_EN	1
#define DAC_HARD_TRIGGER	0
#define DAC_SOFT_TRIGGER	1


void DAC_init(uint8_t dac_en, uint8_t trigger, uint8_t buffer);
void DAC_Write(uint16_t val);



#endif /* INCLUDES_DAC_H_ */
