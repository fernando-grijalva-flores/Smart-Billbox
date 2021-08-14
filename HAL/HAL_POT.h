/*
 * HAL_POT.h
 */

#include "adc.h"

#ifndef HAL_POT_H_
#define HAL_POT_H_

#define POT1_Channel 	ADC_Channel_1
#define POT2_Channel    ADC_Channel_2
#define POT_MAX_Voltage	ADC_Reference
#define POT_MAX_Count	ADC_Resolution

void HAL_POT_Init(void);
uint16_t HAL_POT_GetBinaryValue (uint32_t Channel);
float HAL_POT_GetVoltageValue (uint32_t Channel);
uint8_t HAL_POT_Percentage (uint32_t Channel);

#endif /* HAL_POT_H_ */
