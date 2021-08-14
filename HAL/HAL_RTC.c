/*
 * HAL_RTC.c
 *
 *  Created on: 13/08/2021
 *      Author: carlo
 */
#include "HAL_RTC.h"

/*This function initialize the RTC module*/
void HAL_RTC_Init(void)
{
	MX_RTC_Init();
	return;
}

/*This function returns the actual time, the pointers should be put in the argument as following: hour, minutes, seconds*/
void HAL_Get_ActualTime(uint8_t *hh, uint8_t *mm, uint8_t *ss)
{
	MX_RTC_GetTime(hh, mm, ss);
	LL_mDelay(50);
	return;
}

/*This function returns the actual date, the pointers should be put in the argument as following: year, month, weekday, day*/
void HAL_Get_ActualDate(uint16_t *yy, uint8_t *mm, uint8_t *wd, uint8_t *dd)
{
	MX_RTC_GetDate(yy, mm, wd, dd);
	LL_mDelay(50);
	return;
}

/*This function allow to configure a new actual time, the value of the new time should be put in the argument as
 * following: hour, minutes, seconds*/
void HAL_Set_ActualTime(uint8_t hh, uint8_t mm, uint8_t ss)
{
	MX_RTC_SetTime(hh, mm, ss);
	LL_mDelay(50);
	return;
}

/*This function allow to configure a new actual date, the value of the new date should be put in the argument as
 * following: year, month, weekday, day*/
void HAL_Set_ActualDate (uint16_t yy, uint8_t mm, uint8_t wd, uint8_t dd)
{
	MX_RTC_SetDate(yy, mm, wd, dd);
	LL_mDelay(50);
	return;
}

