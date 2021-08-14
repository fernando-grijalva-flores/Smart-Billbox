/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  LL_RTC_InitTypeDef RTC_InitStruct = {0};
  LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
  LL_RTC_DateTypeDef RTC_DateStruct = {0};

  /* Peripheral clock enable */
  LL_RCC_EnableRTC();

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC and set the Time and Date
  */
  RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
  RTC_InitStruct.AsynchPrescaler = 127;
  RTC_InitStruct.SynchPrescaler = 255;
  LL_RTC_Init(RTC, &RTC_InitStruct);
  LL_RTC_SetAsynchPrescaler(RTC, 127);
  LL_RTC_SetSynchPrescaler(RTC, 255);
  /** Initialize RTC and set the Time and Date
  */
  if(LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0) != 0x32F2){

  RTC_TimeStruct.Hours = 0;
  RTC_TimeStruct.Minutes = 0;
  RTC_TimeStruct.Seconds = 0;
  LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &RTC_TimeStruct);
  RTC_DateStruct.WeekDay = LL_RTC_WEEKDAY_MONDAY;
  RTC_DateStruct.Month = LL_RTC_MONTH_JANUARY;
  RTC_DateStruct.Year = 0;
  LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BIN, &RTC_DateStruct);
    LL_RTC_BAK_SetRegister(RTC,LL_RTC_BKP_DR0,0x32F2);
  }
  /* USER CODE BEGIN RTC_Init 2 */
  LL_RTC_DisableWriteProtection(RTC);
  MX_RTC_Enter_InitMode();

  MX_RTC_Exit_InitMode();
  LL_RTC_EnableWriteProtection(RTC);
  /* USER CODE END RTC_Init 2 */

}

/* USER CODE BEGIN 1 */

/*This functions is to start the RTC initialization mode*/
void MX_RTC_Enter_InitMode(void)
{
	LL_RTC_EnableInitMode(RTC);
	while (!LL_RTC_IsActiveFlag_INIT(RTC));

	return;
}

/*This functions is to finish the RTC initialization mode*/
void MX_RTC_Exit_InitMode (void)
{
	LL_RTC_DisableInitMode(RTC);
	LL_RTC_ClearFlag_RS(RTC);
	while (!LL_RTC_IsActiveFlag_RS(RTC));
}

/*This function returns the actual time*/
void MX_RTC_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
	*hours   = __LL_RTC_CONVERT_BCD2BIN (LL_RTC_TIME_GetHour(RTC));
	*minutes = __LL_RTC_CONVERT_BCD2BIN (LL_RTC_TIME_GetMinute(RTC));
	*seconds = __LL_RTC_CONVERT_BCD2BIN (LL_RTC_TIME_GetSecond(RTC));
	return;
}

/*This function returns the actual date*/
void MX_RTC_GetDate(uint16_t *year, uint8_t *month, uint8_t *weekday, uint8_t *day)
{
	*year  	 = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetYear(RTC));
	*month 	 = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetMonth(RTC));
	*weekday = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetWeekDay(RTC));
	*day     = __LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetDay(RTC));
	return;
}

/*This function allows to set manually actual time*/
void MX_RTC_SetTime(uint8_t hour, uint8_t minutes, uint8_t seconds)
{
	LL_RTC_DisableWriteProtection(RTC);
	MX_RTC_Enter_InitMode();
	LL_RTC_TIME_Config(RTC,LL_RTC_HOURFORMAT_24HOUR, __LL_RTC_CONVERT_BIN2BCD (hour), __LL_RTC_CONVERT_BIN2BCD (minutes), __LL_RTC_CONVERT_BIN2BCD (seconds));
	MX_RTC_Exit_InitMode();
	LL_RTC_EnableWriteProtection(RTC);
	return;
}

/*This function allows to set manually actual date*/
void MX_RTC_SetDate (uint16_t year, uint8_t month, uint8_t weekday, uint8_t day)
{
	LL_RTC_DisableWriteProtection(RTC);
	MX_RTC_Enter_InitMode();
	LL_RTC_DATE_Config(RTC,__LL_RTC_CONVERT_BIN2BCD(weekday),__LL_RTC_CONVERT_BIN2BCD(day), __LL_RTC_CONVERT_BIN2BCD (month), __LL_RTC_CONVERT_BIN2BCD (year));
	MX_RTC_Exit_InitMode();
	LL_RTC_EnableWriteProtection(RTC);
	return;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
