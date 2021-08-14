/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
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
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  LL_I2C_InitTypeDef I2C_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  /**I2C1 GPIO Configuration
  PB8   ------> I2C1_SCL
  PB9   ------> I2C1_SDA
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_8|LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  /** I2C Initialization
  */
  LL_I2C_EnableAutoEndMode(I2C1);
  LL_I2C_DisableOwnAddress2(I2C1);
  LL_I2C_DisableGeneralCall(I2C1);
  LL_I2C_EnableClockStretching(I2C1);
  I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
  I2C_InitStruct.Timing = 0x00101D7C;
  I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
  I2C_InitStruct.DigitalFilter = 0;
  I2C_InitStruct.OwnAddress1 = 0;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_10BIT;
  LL_I2C_Init(I2C1, &I2C_InitStruct);
  LL_I2C_SetOwnAddress2(I2C1, 0, LL_I2C_OWNADDRESS2_NOMASK);
  LL_I2C_SetMasterAddressingMode(I2C1, LL_I2C_ADDRESSING_MODE_10BIT);
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/* USER CODE BEGIN 1 */

void MX_I2C1_MasterInit(MX_I2C1_XferType transferType, uint8_t transferSize, uint16_t periph_addr)
{
	/*Define Addressing mode*/
	LL_I2C_SetMasterAddressingMode(I2C1, LL_I2C_ADDRESSING_MODE_7BIT);

	/*Define Slave Address*/
	LL_I2C_SetSlaveAddr(I2C1, periph_addr);

	/*Define Transfer Type*/
	if(transferType == MX_I2C1_xferRead)
	{
		LL_I2C_SetTransferRequest(I2C1, LL_I2C_REQUEST_READ);
	}
	else
	{
		LL_I2C_SetTransferRequest(I2C1, LL_I2C_REQUEST_WRITE);
	}

	/*Define transfer size*/
	LL_I2C_SetTransferSize(I2C1, transferSize);

	/*Enable Auto End Mode*/
	LL_I2C_EnableAutoEndMode(I2C1);

	return;
}

void MX_I2C_Read (uint8_t transferSize, uint8_t *dataRx, uint16_t periph_addr)
{
	/*Counter to read data*/
	uint8_t i = 0;

	/*Master Initialization*/
	MX_I2C1_MasterInit(MX_I2C1_xferRead, transferSize, periph_addr);

	/*Generate Start Condition*/
	LL_I2C_GenerateStartCondition(I2C1);

	/*Check if Stop Flag is active or not*/
	while(!LL_I2C_IsActiveFlag_STOP(I2C1))
	{
		/*This condition is used to check if the buffer is not empty, if not dataRx pointer take information from the salve*/
		if(LL_I2C_IsActiveFlag_RXNE(I2C1))
		{
			dataRx[i++] = LL_I2C_ReceiveData8(I2C1);
		}
	}

	/*Clear Stop flag when the data transmission has ended*/
	LL_I2C_ClearFlag_STOP(I2C1);

	return;
}

void MX_I2C1_Write (uint8_t transferSize, uint8_t *dataTx, uint16_t periph_addr)
{
	uint8_t i = 0;

	/*Master Initialization*/
	MX_I2C1_MasterInit(MX_I2C1_xferWrite, transferSize, periph_addr);

	/*Generate Start Condition*/
	LL_I2C_GenerateStartCondition(I2C1);

	/*Check if Stop Flag is active or not*/
	while(!LL_I2C_IsActiveFlag_STOP(I2C1))
	{
		if(LL_I2C_IsActiveFlag_TXIS(I2C1))
		{
			LL_I2C_TransmitData8(I2C1, dataTx[i++]);
		}
	}

	/*Clear Stop flag when the data transmission has ended*/
	LL_I2C_ClearFlag_STOP(I2C1);

	return;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
