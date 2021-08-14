/*
 * HAL_RTC.h
 *
 *  Created on: 13/08/2021
 *      Author: carlo
 */
#include "rtc.h"

/*Prototype of HAL Function for RTC module*/
void HAL_RTC_Init(void);
void HAL_Get_ActualTime(uint8_t *hh, uint8_t *mm, uint8_t *ss);
void HAL_Get_ActualDate(uint16_t *yy, uint8_t *mm, uint8_t *wd, uint8_t *dd);
void HAL_Set_ActualTime(uint8_t hour, uint8_t minutes, uint8_t seconds);
void HAL_Set_ActualDate (uint16_t year, uint8_t month, uint8_t weekday, uint8_t day);

#ifndef HAL_RTC_H_
#define HAL_RTC_H_



#endif /* HAL_RTC_H_ */
