/*
 * HAL_TEMPSen.h
 *
 *  Created on: 12/08/2021
 *      Author: carlo
 */

#ifndef HAL_TEMPSEN_H_
#define HAL_TEMPSEN_H_

#include "i2c.h"

/*This is the address of the temperature sensor used on the expansion board*/
#define TEMP_Sens_ADDR		(0x90)

/*All commands used to configure mode operation on the LM75B*/
typedef enum
{
	LM75B_CMD_Temp	 =	0x00,
	LM75B_CMD_Config =	0x01,
	LM75B_CMD_Thyst	 =	0x02,
	LM75B_CMD_Tos	 =	0x03
}LM75B_CMD;

/*Prototypes of functions declared for the temperature sensor*/
void HAL_TEMPSen_Init();
uint8_t HAL_TEMPSen_ReadTemperature(void);


#endif /* HAL_TEMPSEN_H_ */
