/*
 * This file contains the hardware abstraction
 * functions for the Potentiometers using the
 * LL Libraries for the ADC
 * HAL_POT.c
 *
 */
#include "HAL_POT.h"

/*This function initialize the ADC*/
void HAL_POT_Init(void)
{
	MX_ADC1_Init();
	MX_ADC1_Calibration();
	MX_ADC1_Enable();
}

/*This function returns the ADC value i an 8 bits format*/
uint16_t HAL_POT_GetBinaryValue (uint32_t Channel)
{
	uint16_t POT_value = 0;
	MX_ADC1_SetChannel(ADC_Channel_1);
	MX_ADC1_StartConversion();
	POT_value = MX_ADC1_GetValue();
	LL_mDelay(10);

	return POT_value;
}

/*This Function get the voltage on the Potentiometer measured by the ADC*/
float HAL_POT_GetVoltageValue (uint32_t Channel)
{
	float POT_VoltageValue = 0;
	uint16_t measure = 0;

	measure = HAL_POT_GetBinaryValue(Channel);
	POT_VoltageValue = (measure * POT_MAX_Voltage)/POT_MAX_Count;

	return POT_VoltageValue;
}

/*This function returns the value of the potentiometer as a percentage*/
uint8_t HAL_POT_Percentage (uint32_t Channel)
{
	uint8_t POT_Percent = 0;
	uint16_t measure = 0;

	measure = HAL_POT_GetBinaryValue(Channel);
	POT_Percent = (measure * 100)/POT_MAX_Count;

	return POT_Percent;
}
