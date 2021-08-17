/* USER CODE BEGIN Header */
/*
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HAL_RGB.h"
#include "HAL_POT.h"
#include "HAL_TEMPSen.h"
#include "HAL_RTC.h"
#include "HAL_LCD.h"
#include "HAL_JOYSTICK.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// Estado inicial
uint8_t Horas, Minutos, IntervaloH1, IntervaloH2, IntervaloH3, IntervaloM1, IntervaloM2, IntervaloM3;
uint8_t Hora,Minuto,Segundo;
uint8_t alarma1,alarma2,alarma3;

typedef enum{
	E0,
  	E1,
  	E2,
  	E3,
	E4,
	E5,
	E6,
	E7,
	E8
}Estados;

typedef enum
{
	inactive,
	active

}alarm_state;

Estados EA = E0;
// Puntero seleccion
short Puntero = 0, first = 0, inicio = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t Temp = 0; //Variable para guardar la lectura de la temperatura actual
uint8_t temp_alert = inactive;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_TEMPSen_Init();
  HAL_RTC_Init();
  HAL_LCD_Init();
  HAL_POT_Init();
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  HAL_LCD_Write_AsciiString(word[iniciando],36,1);
  LL_mDelay(1000);
  HAL_LCD_Clear();
  uint8_t inicio2=0;
  while (1)
  {
	  //La temperatura se debe leer en todo momento, por lo que se llama a la funcion de ReadTemperature de la libreria HAL del sensor LM75B
	  Temp = HAL_TEMPSen_ReadTemperature();

	  HAL_Get_ActualTime(&Hora,&Minuto,&Segundo);

	  if (inicio==1)
	  	  {

		  if (IntervaloH1==Hora && IntervaloM1==Minuto && alarma1==inactive)
		  {
			  if (inicio2==0)
			  {
				  first=0;
				  inicio2=1;
			  }
		  	  EA=E5;
		  	  alarma1=active;

		  }
		  if (IntervaloH2==Hora && IntervaloM2==Minuto && alarma2==inactive)
		  {
			  if (inicio2==0)
			  {
			  first=0;
			  inicio2=1;
			  }
			  EA=E5;
		  	  alarma2=active;

		  }
		  if (IntervaloH3 == Hora && IntervaloM3 == Minuto && alarma3==inactive)
		  {
			  if (inicio2==0)
			  {
			  first=0;
			  inicio2=1;
			  }
			  EA=E5;
		  	  alarma3=active;

		  }
	  }


	  if(Temp >= Temp_limit)
	  {
		  temp_alert = active;
		  EA = E8;
	  }else
	  {
		  temp_alert = inactive;
	  }

	  short btnu = HAL_JOYSTICK_UpPressed();

	 // LL_mDelay(2);
	  short btnd = HAL_JOYSTICK_DownPressed();
	  //LL_mDelay(2);
	  short btnl = HAL_JOYSTICK_LeftPressed();
	  //LL_mDelay(2);
	  short btnr = HAL_JOYSTICK_RightPressed();
	 // LL_mDelay(2);
	  short btnc = HAL_JOYSTICK_CenterPressed();
	  fsm(btnu, btnd, btnl, btnr, btnc);

	/* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//    /* USER CODE END WHILE */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_LSI_Enable();

   /* Wait till LSI is ready */
  while(LL_RCC_LSI_IsReady() != 1)
  {

  }
  LL_PWR_EnableBkUpAccess();
  if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSI)
  {
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
  }
  LL_RCC_EnableRTC();
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_16);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_16);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(64000000);
  LL_SetSystemCoreClock(64000000);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
  LL_RCC_SetADCClockSource(LL_RCC_ADC12_CLKSRC_PLL_DIV_1);
}

/* USER CODE BEGIN 4 */
void estado_Anterior(short btnU, short btnD, short btnL, short btnR, short btnC){
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
}

// Funciones por estado
void EDO_0(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Configuracion de reloj
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Write_AsciiString(word[configuracion],24,0);
		HAL_LCD_Write_AsciiString(word[reloj],48,1);
		HAL_LCD_Write_ascii(':',60,2);
		HAL_LCD_Write_AsciiString(word[aceptar],36,3);
		first = 1;
	}
	Horas = HAL_POT_Percentage(POT1_Channel)*23/100;
	Minutos = HAL_POT_Percentage(POT2_Channel)*59/100;
	HAL_LCD_Write_Number(&Horas,48,2);
	HAL_LCD_Write_Number(&Minutos,67,2);
	if(btnC == 1 && btnC != btnCa && inicio == 0){
		// Cambio de estado
		EA = E1;
		first = 0;
		HAL_LCD_Clear();
		HAL_Set_ActualTime(Horas,Minutos,0);
	}
	else if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		EA = E3;
		first = 0;
		HAL_LCD_Clear();
		HAL_Set_ActualTime(Horas,Minutos,0);
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_1(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Configuracion pastillas
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Write_AsciiString(word[pastillasABC],18,0);
		HAL_LCD_Write_AsciiString(word[intervalo],36,1);
		HAL_LCD_Write_ascii(':',60,2);
		HAL_LCD_Write_AsciiString(word[aceptar],36,3);
		// > en A la primera vez
		HAL_LCD_Write_ascii('>',72,0);
		HAL_LCD_Write_ascii(' ',84,0);
		HAL_LCD_Write_ascii(' ',96,0);
		first = 1;
	}
	// Obtencion horas y minutos
	Horas = HAL_POT_Percentage(POT1_Channel)*23/100;
	Minutos = HAL_POT_Percentage(POT2_Channel)*59/100;
	// Mostrado valor seleccionado
	HAL_LCD_Write_Number(&Horas,48,2);
	HAL_LCD_Write_Number(&Minutos,67,2);

	if(Puntero == 0){
		// Si el puntero esta en A carga los valores a A
		IntervaloH1 = Horas;
		IntervaloM1 = Minutos;
	}
	else if(Puntero == 1){
		// Si el puntero esta en B carga los valores a B
		IntervaloH2 = Horas;
		IntervaloM2 = Minutos;
	}
	else if(Puntero == 2){
		// Si el puntero esta en C carga los valores a C
		IntervaloH3 = Horas;
		IntervaloM3 = Minutos;
	}
	// Puntero
	if(btnL == 1 && btnL != btnLa && btnR == 0){
		Puntero -= 1;
		if (Puntero < 0)
			Puntero = 2;
		switch (Puntero){
			case 0:
				HAL_LCD_Write_ascii('>',72,0);
				HAL_LCD_Write_ascii(' ',84,0);
				HAL_LCD_Write_ascii(' ',96,0);
				break;
			case 1:
				HAL_LCD_Write_ascii(' ',72,0);
				HAL_LCD_Write_ascii('>',84,0);
				HAL_LCD_Write_ascii(' ',96,0);
				break;
			case 2:
				HAL_LCD_Write_ascii(' ',72,0);
				HAL_LCD_Write_ascii(' ',84,0);
				HAL_LCD_Write_ascii('>',96,0);
				break;
		}
	}
	else if(btnR == 1 && btnR != btnRa && btnL == 0){
		Puntero += 1;
		if (Puntero > 2)
			Puntero = 0;
		switch (Puntero){
			case 0:
				HAL_LCD_Write_ascii('>',72,0);
				HAL_LCD_Write_ascii(' ',84,0);
				HAL_LCD_Write_ascii(' ',96,0);
				break;
			case 1:
				HAL_LCD_Write_ascii(' ',72,0);
				HAL_LCD_Write_ascii('>',84,0);
				HAL_LCD_Write_ascii(' ',96,0);
				break;
			case 2:
				HAL_LCD_Write_ascii(' ',72,0);
				HAL_LCD_Write_ascii(' ',84,0);
				HAL_LCD_Write_ascii('>',96,0);
				break;
		}
	}


	// Aceptar
	if(btnC == 1 && btnC != btnCa && inicio == 0){
		// Cambio de estado
		EA = E2;
		first = 0;
		inicio = 1; //cambio, se setea en 0 cuando entramos a imprimir
		HAL_LCD_Clear();
	}
	else if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		EA = E3;
		first = 0;
		HAL_LCD_Clear();
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_2(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Pantalla principal
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Write_AsciiString(word[reloj],48,0);
		HAL_LCD_Write_ascii(':',60,1);
		HAL_LCD_Write_AsciiString(word[temperatura],30,2);
		HAL_LCD_Write_ascii(SYMBOL_ASCII_CELSIUS,66,3);
		HAL_LCD_Write_ascii('C',72,3);
		first = 1;
	}
	// Obtener tiempo
	// Mostrar tiempo
	HAL_LCD_Write_Number(&Hora,48,1);
	HAL_LCD_Write_Number(&Minuto,66,1);
	// Mostrar Temperaura
	HAL_LCD_Write_Number(&Temp,54,3);
	if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		EA = E3;
		first = 0;
		HAL_LCD_Clear();
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_3(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Menu
	if(first == 0){
			// Mostrado de valores fijos
			HAL_LCD_Write_AsciiString(word[ajustarReloj],24,0);
			HAL_LCD_Write_AsciiString(word[ajustarPastilla],12,1);
			HAL_LCD_Write_AsciiString(word[HoraYtemperatura],13,2);
			HAL_LCD_Write_AsciiString(word[intervalosPastilla],6,3);
			// > en A la primera vez
			HAL_LCD_Write_ascii('>',18,0);
			HAL_LCD_Write_ascii(' ',6,1);
			HAL_LCD_Write_ascii(' ',6,2);
			HAL_LCD_Write_ascii(' ',0,3);
			first = 1;
			Puntero=0;
		}

	if(Puntero == 0 && btnC == 1 && btnC != btnCa){
		//Si puntero es igual a 0 y el boton central es presionado, ira a ajustar reloj
		EA=E0;
		HAL_LCD_Clear();
		first=0;
	}
	else if(Puntero == 1 && btnC == 1 && btnC != btnCa){
		//Si puntero es igual a 1 y el boton central es presionado, ira a ajustar intervalos pastilla
		EA=E1;
		HAL_LCD_Clear();
		first=0;
	}
	else if(Puntero == 2 && btnC == 1 && btnC != btnCa){
		//Si puntero es igual a 2 y el boton central es presionado, ira a mostrar hora actual y temp
		EA=E2;
		HAL_LCD_Clear();
		first=0;
	}
	else if(Puntero == 3 && btnC == 1 && btnC != btnCa){
		//Si puntero es igual a 3 y el boton central es presionado, ira a mostrar los intervalos configurados
		EA=E7;
		HAL_LCD_Clear();
		first=0;
		}
	// Puntero
	if(btnD == 1 && btnD != btnDa && btnU == 0){
		Puntero += 1;
		if (Puntero > 3)
			Puntero = 0;
		switch (Puntero){
			case 0:
				LL_mDelay(1);
				HAL_LCD_Write_ascii('>',18,0);
				HAL_LCD_Write_ascii(' ',6,1);
				HAL_LCD_Write_ascii(' ',6,2);
				HAL_LCD_Write_ascii(' ',0,3);
				break;
			case 1:
				LL_mDelay(1);
				HAL_LCD_Write_ascii(' ',18,0);
				HAL_LCD_Write_ascii('>',6,1);
				HAL_LCD_Write_ascii(' ',6,2);
				HAL_LCD_Write_ascii(' ',0,3);
				break;
			case 2:
				LL_mDelay(1);
				HAL_LCD_Write_ascii(' ',18,0);
				HAL_LCD_Write_ascii(' ',6,1);
				HAL_LCD_Write_ascii('>',6,2);
				HAL_LCD_Write_ascii(' ',0,3);
				break;
			case 3:
				LL_mDelay(1);
				HAL_LCD_Write_ascii(' ',18,0);
				HAL_LCD_Write_ascii(' ',6,1);
				HAL_LCD_Write_ascii(' ',6,2);
				HAL_LCD_Write_ascii('>',0,3);
							break;
		}
	}
	else if(btnU == 1 && btnU != btnUa && btnD == 0){
			Puntero -= 1;
			if (Puntero < 0)
				Puntero = 3;
			switch (Puntero){
				case 0:
					//LL_mDelay(1);
					HAL_LCD_Write_ascii('>',18,0);
					HAL_LCD_Write_ascii(' ',6,1);
					HAL_LCD_Write_ascii(' ',6,2);
					HAL_LCD_Write_ascii(' ',0,3);
					break;
				case 1:
					//LL_mDelay(1);
					HAL_LCD_Write_ascii(' ',18,0);
					HAL_LCD_Write_ascii('>',6,1);
					HAL_LCD_Write_ascii(' ',6,2);
					HAL_LCD_Write_ascii(' ',0,3);
					break;
				case 2:
					//LL_mDelay(1);
					HAL_LCD_Write_ascii(' ',18,0);
					HAL_LCD_Write_ascii(' ',6,1);
					HAL_LCD_Write_ascii('>',6,2);
					HAL_LCD_Write_ascii(' ',0,3);
					break;
				case 3:
					//LL_mDelay(1);
					HAL_LCD_Write_ascii(' ',18,0);
					HAL_LCD_Write_ascii(' ',6,1);
					HAL_LCD_Write_ascii(' ',6,2);
					HAL_LCD_Write_ascii('>',0,3);
								break;
			}
		}


	/*if(btnC == 1 && btnC != btnCa){
		// Cambio de estado

		first = 0;
		HAL_LCD_Clear();
	}*/
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_4(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Alarma Temperatura
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Write_AsciiString("Temperatura",30,1);
		HAL_LCD_Write_AsciiString("Sobrepasada",30,2);
		first = 1;
	}
	if(HAL_TEMPSen_ReadTemperature() < 40){
		// Cambio de estado
		EA = E2;
		first = 0;
		HAL_LCD_Clear();
	}
}

void EDO_5(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Alarma Pastilla
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Clear();
		HAL_LCD_Write_AsciiString(word[tomePastilla],24,0);
		HAL_LCD_Write_AsciiString(word[rojo],36,1);
		HAL_LCD_Write_AsciiString(word[verde],66,1);
		HAL_LCD_Write_AsciiString(word[azul],54,2);
		HAL_LCD_Write_AsciiString(word[entendido],30,3);
		first = 1;
	}
	if (alarma1==active && alarma2 ==inactive && alarma3 == inactive)
	{
		HAL_LCD_Write_ascii('>',30,1);
		rgb_rojo();
	}
	else if (alarma2==active && alarma1 == inactive && alarma3 == inactive)
	{
		HAL_LCD_Write_ascii('>',60,1);
		rgb_verde();
	}
	else  if (alarma3==active && alarma1 ==inactive && alarma2 ==inactive)
	{
		HAL_LCD_Write_ascii('>',48,2);
		rgb_azul();
	}
	else if (alarma1==active && alarma2 == active && alarma3 ==inactive)
		rgb_amarillo();
	else if (alarma1==inactive && alarma2 == active && alarma3 ==active)
		rgb_celeste();
	else if (alarma1==active && alarma2 == inactive && alarma3 ==active)
		rgb_morado();
	else
		rgb_blanco();





	if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		EA = E3;
		first = 0;
		HAL_LCD_Clear();
		rgb_apagado();
		alarma1=inactive;
		alarma2=inactive;
		alarma3=inactive;
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_6(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Codigo de estado inicio

	if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		EA = E3;
		first = 0;
		HAL_LCD_Clear();
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_7(short btnU, short btnD, short btnL, short btnR, short btnC){
	//Intervalos pastillas
	if (first==0)
	{
		HAL_LCD_Write_AsciiString(word[alarmas],42,0);
		HAL_LCD_Write_AsciiString(word[rojo],30,1);
		HAL_LCD_Write_AsciiString(word[verde],30,2);
		HAL_LCD_Write_AsciiString(word[azul],30,3);
		HAL_LCD_Write_ascii(':',78,1);
		HAL_LCD_Write_ascii(':',78,2);
		HAL_LCD_Write_ascii(':',78,3);
		HAL_LCD_Write_Number(&IntervaloH1,66,1);
		HAL_LCD_Write_Number(&IntervaloM1,84,1);
		HAL_LCD_Write_Number(&IntervaloH2,66,2);
		HAL_LCD_Write_Number(&IntervaloM2,84,2);
		HAL_LCD_Write_Number(&IntervaloH3,66,3);
		HAL_LCD_Write_Number(&IntervaloM3,84,3);
		first=1;
	}

	if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		first = 0;
		HAL_LCD_Clear();
		EA=E3;
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

//Función usada para el estado de "Alarma de Temperatura Activa"
void EDO_8(short btnU, short btnD, short btnL, short btnR, short btnC)
{
	if(first == 0)
	{
		// Mostrado de valores fijos
		HAL_LCD_Clear();
		HAL_LCD_Write_AsciiString(word[alerta],30,0);
		HAL_LCD_Write_AsciiString(word[de],72,0);
		HAL_LCD_Write_AsciiString(word[temperatura],24,1);
		HAL_LCD_Write_AsciiString(word[elevada],36,2);
		HAL_LCD_Write_ascii(SYMBOL_ASCII_CELSIUS,60,3);
		HAL_LCD_Write_ascii('C',66,3);
		first = 1;
	}

	HAL_LCD_Write_Number(&Temp,48,3);
	/*El estado actual se mantendrá en el Estado 8 (estado alerta de temperatura elevada) mientras  temp_alert este activa
	 esto debido a que la temperatura no a decendido del valor limite
	*/
	if(!temp_alert)
	{
		//Si la temperatura deciende del valor limite, el estado regresa a mostrar la pantalla principal
		first = 0;
		EA = E2;
	}

	estado_Anterior(btnU, btnD, btnL, btnR, btnC);

}
// Estructura para asignar una funcion a cada estado
typedef struct {
	Estados Estado;
	void (*func)(short,short,short,short,short);
} FSM;

// Maquina de estados (asignaciones)
FSM MDE[] = {
		{E0,EDO_0},
        {E1,EDO_1},
        {E2,EDO_2},
        {E3,EDO_3},
		{E4,EDO_4},
		{E5,EDO_5},
		{E6,EDO_6},
		{E7,EDO_7},
		{E8,EDO_8}
};

void fsm(short btnU, short btnD,short btnL, short btnR, short btnC){
	MDE[EA].func(btnU, btnD, btnL, btnR, btnC);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
