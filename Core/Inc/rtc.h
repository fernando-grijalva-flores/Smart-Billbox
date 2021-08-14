/**
  ******************************************************************************
  * @file    rtc.h
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
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
#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
typedef enum
{
	Monday   =  LL_RTC_WEEKDAY_MONDAY,
    Tuesday  =  LL_RTC_WEEKDAY_TUESDAY,
	Wendsday =	LL_RTC_WEEKDAY_WEDNESDAY,
	Thrusday =  LL_RTC_WEEKDAY_THURSDAY,
	Friday   =  LL_RTC_WEEKDAY_FRIDAY,
	Saturday =  LL_RTC_WEEKDAY_SATURDAY,
	Sunday	 =	LL_RTC_WEEKDAY_SUNDAY
}RTC_Week_days;

typedef enum
{
	  January   =        LL_RTC_MONTH_JANUARY,
	  February  =        LL_RTC_MONTH_FEBRUARY,
	  March		=        LL_RTC_MONTH_MARCH,
	  April		=		 LL_RTC_MONTH_APRIL,
	  May		=		 LL_RTC_MONTH_MAY,
	  June      =		 LL_RTC_MONTH_JUNE,
	  July		=		 LL_RTC_MONTH_JULY,
	  August	=		 LL_RTC_MONTH_AUGUST,
	  September	=		 LL_RTC_MONTH_SEPTEMBER,
	  October	=		 LL_RTC_MONTH_OCTOBER,
	  November	=		 LL_RTC_MONTH_NOVEMBER,
	  December	=		 LL_RTC_MONTH_DECEMBER,
}RTC_Moths;
/* USER CODE END Private defines */

void MX_RTC_Init(void);

/* USER CODE BEGIN Prototypes */
void MX_RTC_Enter_InitMode(void);
void MX_RTC_Exit_InitMode (void);
void MX_RTC_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
void MX_RTC_GetDate(uint16_t *year, uint8_t *month, uint8_t *weekday, uint8_t *day);
void MX_RTC_SetTime(uint8_t hour, uint8_t minutes, uint8_t seconds);
void MX_RTC_SetDate (uint16_t year, uint8_t month, uint8_t weekday, uint8_t day);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
