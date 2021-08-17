/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f3xx_ll_adc.h"
#include "stm32f3xx_ll_i2c.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_rtc.h"
#include "stm32f3xx_ll_spi.h"
#include "stm32f3xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define J_RIGHT_Pin LL_GPIO_PIN_0
#define J_RIGHT_GPIO_Port GPIOC
#define J_LEFT_Pin LL_GPIO_PIN_1
#define J_LEFT_GPIO_Port GPIOC
#define J_UP_Pin LL_GPIO_PIN_4
#define J_UP_GPIO_Port GPIOA
#define LCD_RESET_Pin LL_GPIO_PIN_6
#define LCD_RESET_GPIO_Port GPIOA
#define J_DOWN_Pin LL_GPIO_PIN_0
#define J_DOWN_GPIO_Port GPIOB
#define LED_G_Pin LL_GPIO_PIN_7
#define LED_G_GPIO_Port GPIOC
#define LCD_A0_Pin LL_GPIO_PIN_8
#define LCD_A0_GPIO_Port GPIOA
#define LED_B_Pin LL_GPIO_PIN_9
#define LED_B_GPIO_Port GPIOA
#define LED_R_Pin LL_GPIO_PIN_4
#define LED_R_GPIO_Port GPIOB
#define J_CENTER_Pin LL_GPIO_PIN_5
#define J_CENTER_GPIO_Port GPIOB
#define LCD_CS_N_Pin LL_GPIO_PIN_6
#define LCD_CS_N_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* USER CODE BEGIN Private defines */
#ifndef Diplays_H_
#define Diplays_H_
#endif


#include "main.h"

// Variables auxiliares de estado antiguo para detecion falling para cambiar de estado
short btnU, btnUa, btnD, btnDa, btnL, btnLa, btnR, btnRa, btnC, btnCa;

void EDO_0(short,short,short,short,short);
void EDO_1(short,short,short,short,short);
void EDO_2(short,short,short,short,short);
void EDO_3(short,short,short,short,short);
void EDO_4(short,short,short,short,short);
void EDO_5(short,short,short,short,short);
void EDO_6(short,short,short,short,short);
void EDO_7(short,short,short,short,short);

void fsm(short,short,short,short,short);




/* Word defines */

	/*This are the all the used words in order to
	display them in the LCD with a particular screen*/
typedef enum{
	configuracion =0,
	reloj,
	aceptar,
	pastillasABC,
	intervalo,
	iniciando,
	temperatura,
	ajustarReloj,
	ajustarPastilla,
	HoraYtemperatura,
	intervalosPastilla,
	sobrepasada,
	tomePastilla,
	rojo,
	verde,
	azul,
	entendido,
	alarmas
}words;



#define	w_configuration				(0)
#define w_clock						(1)
#define w_accept					(2)
#define w_pillsABC					(3)
#define w_timeInterval				(4)
#define w_starting					(5)
#define w_temp						(6)
#define w_adjustClock				(7)
#define w_adjustPill				(8)
#define w_timeAndTemp				(9)
#define w_timePills					(10)
#define w_overTemp					(11)
#define w_takePill					(12)
#define w_red						(13)
#define w_green						(14)
#define	w_blue						(15)
#define w_okay						(16)
#define w_alarms					(17)

static uint8_t word[18][21]= {
		"Configuracion", //0
		"Reloj",
		">Aceptar<",
		"Pastilla  A B C",
		"Intervalo", //4
		"Iniciando",
		"Temperatura",
		"Ajustar reloj",
		"Ajustar pastilla", //8
		"Hora y temperatura",
		"Intervalos pastillas",
		"Sobrepasada",
		"Tome pastilla", //12
		"Rojo",
		"Verde",
		"Azul",
		">Entendido<", //16
		"Alarmas"
};


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
