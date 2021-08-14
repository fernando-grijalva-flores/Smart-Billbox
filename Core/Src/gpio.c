/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_SetOutputPin(GPIOA, LCD_RESET_Pin|LCD_A0_Pin);

  /**/
  LL_GPIO_SetOutputPin(LCD_CS_N_GPIO_Port, LCD_CS_N_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_G_GPIO_Port, LED_G_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_B_GPIO_Port, LED_B_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LED_R_GPIO_Port, LED_R_Pin);

  /**/
  GPIO_InitStruct.Pin = J_RIGHT_Pin|J_LEFT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = J_UP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(J_UP_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LCD_RESET_Pin|LCD_A0_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = J_DOWN_Pin|J_CENTER_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_G_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_G_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_B_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_B_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LED_R_Pin|LCD_CS_N_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
short MX_Joystick_Up(){
	/* Deteccion de Joystick Up */
	short v = LL_GPIO_IsInputPinSet(GPIOA,J_UP_Pin);
	return v;
}
short MX_Joystick_Down(){
	/* Deteccion de Joystick Down */
	short v = LL_GPIO_IsInputPinSet(GPIOB,J_DOWN_Pin);
	return v;
}
short MX_Joystick_Right(){
	/* Deteccion de Joystick Right */
	short v = LL_GPIO_IsInputPinSet(GPIOC,J_RIGHT_Pin);
	return v;
}
short MX_Joystick_Left(){
	/* Deteccion de Joystick Left */
	short v = LL_GPIO_IsInputPinSet(GPIOC,J_LEFT_Pin);
	return v;
}
short MX_Joystick_Center(){
	/* Deteccion de Joystick Center */
	short v = LL_GPIO_IsInputPinSet(GPIOB,J_CENTER_Pin);
	return v;
}
void MX_RGB_Red(short v){
	/* Activacion o desactivacion led R */
	if (v == 1)
		LL_GPIO_SetOutputPin(GPIOB,LED_R_Pin);
	else if (v == 0)
		LL_GPIO_ResetOutputPin(GPIOB,LED_R_Pin);
}
void MX_RGB_Green(short v){
	/* Activacion o desactivacion led G */
	if (v == 1)
		LL_GPIO_SetOutputPin(GPIOC,LED_G_Pin);
	else if (v == 0)
		LL_GPIO_ResetOutputPin(GPIOC,LED_G_Pin);
}
void MX_RGB_Blue(short v){
	/* Activacion o desactivacion led B */
	if (v == 1)
		LL_GPIO_SetOutputPin(GPIOA,LED_B_Pin);
	else if (v == 0)
		LL_GPIO_ResetOutputPin(GPIOA,LED_B_Pin);
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
