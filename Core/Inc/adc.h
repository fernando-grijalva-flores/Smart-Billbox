/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* Resolution and voltage reference for ADC
 * Voltage reference is multiplied by 100
 * real voltage references is equal to 3.3 volts*/
#define ADC_Resolution 255
#define ADC_Reference  330

/*This structure is used to select the ADC Channel to use*/
typedef enum
{
	ADC_Channel_1,
	ADC_Channel_2,
	ADC_Channel_Num

}ADC_Channel_t;

/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */

void MX_ADC1_Enable(void);
void MX_ADC1_Calibration(void);
void MX_ADC1_StartConversion(void);
void MX_ADC1_SetChannel(uint32_t Channel);
uint16_t MX_ADC1_GetValue(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
