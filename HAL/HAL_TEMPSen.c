/*
 * HAL_TEMPSen.c
 *
 *  Created on: 12/08/2021
 *      Author: carlo
 */
#include "HAL_TEMPSen.h"

void HAL_TEMPSen_Init()
{
	MX_I2C1_Init();
	return;
}

uint8_t HAL_TEMPSen_ReadTemperature(void)
{
	  uint16_t measure = 0x00;
	  uint8_t data[2];
	  uint8_t temp = 0;
	  data [0]= LM75B_CMD_Temp;
	  MX_I2C1_Write(1, data, TEMP_Sens_ADDR);
	  MX_I2C_Read(2, data, TEMP_Sens_ADDR);

	  for (int i=0; i<2; i++)
	  {
		  if(i==0)
		  {
			  measure = data[0];
			  measure = measure << 8;
		  }else
		  {
			  measure = measure | (data[1]);
		  }
	  }
	  measure = measure >> 5;
	  temp = (uint8_t)(measure*125)/100;

	  return temp;
}
