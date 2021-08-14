/*
 * HAL_LCD.c
 *
 *  Created on: 08/08/2021
 *      Author: fer06
 */

/*User includes*/

#include "HAL_LCD.h"
#include "spi.h"

/*User global variables*/
uint8_t AlreadyEnterMenu=0;
uint8_t	ConfigurationStage=0;
uint8_t AlreadyEnterAlarmConfig=0;

void HAL_LCD_Init(void)
{
	/* This function initialize the LCD, this function must be call first
	before performing any operation in the LCD, the used GPIOs were initialized in the main */

	/*Before starting sending information to the LCD,
	it is necessary to initialize the SPI communication*/
	MX_SPI1_Init();

	/*We need to make sure the LCD reaches 3.3V, therefore we make a delay of 1ms after reseting the LCD
	to start sending information*/
	HAL_LCD_Reset();
	LL_mDelay(1);

	/*These commands are necessary to initialize the LCD, you can find
	them in the datasheet of the LCD NHD-C12832A1Z-FSW-FBW-3V3 or chip on glass ST7565R */

	/*We set the segment (columns) order to NORMAL*/
	HAL_LCD_Send_Command(CMD_ADC_SELECT(ADC_NORMAL));

	 /*TURNS OFF the display*/
	HAL_LCD_Send_Command(CMD_DISPLAY_ON_OFF(DISPLAY_OFF));

	/*Selects COM output scan direction to normal direction*/
	HAL_LCD_Send_Command(CMD_COM_DIRECTION(COM_DIRECTION_REVERSE));

	/*Sets the LCD drive voltage bias ratio to 1/9*/
	HAL_LCD_Send_Command(CMD_BIAS_RATIO(CMD_BIAS_19));

	/*Select internal power supply 111*/
	HAL_LCD_Send_Command(CMD_PWR_CONTROL(PWR_INTERNAL_SUPPLY));

	/*Select internal resistor ratio 001 */
	HAL_LCD_Send_Command(CMD_RES_RATIO(RES_RATIO_35));

	/*Electronic volume mode  */
	HAL_LCD_Send_Command(CMD_ELEC_VOL_MODE);

	/*SET electronic volume (contrast), please NOTE this value is different from the datasheet,
	the datasheet specifies to configure a 3F, however, the contrast is to high and we would have
	problems to see the configured pixel in further LCD configurations*/
	HAL_LCD_Send_Command(CMD_ELEC_VOL_SET_LOW);

	/* End of the initialization commands from datasheet, the following commands are just to prepare the
	 LCD before start implementing functions */

	/* With this command we want to set all the points in the LCD to work normal*/
	HAL_LCD_Send_Command(CMD_LCD_POINTS(LCD_POINTS_NORMAL));

	/*After initializating the LCD, it is necessary to clear all display because
	it could have information in RAM after it was turned off*/
	HAL_LCD_Clear();

	return;
}
void HAL_LCD_Reset(void)
{
	/*Pin PA6 is configured as RESET signal of LCD,
	when the reset signal is inactive, it is HIGH, if we want to reset the LCD
	, we reset the signal to LOW and release
	PA6   ------> LCD_RESET*/

	LL_GPIO_ResetOutputPin(LCD_RESET_GPIO_Port,LCD_RESET_Pin);
	LL_mDelay(1);
	LL_GPIO_SetOutputPin(LCD_RESET_GPIO_Port,LCD_RESET_Pin);

	return;
}

void HAL_LCD_A0_Data(void)
{
	/*Pin PA8 is configured as A0 signal of LCD,
	when the A0 is HIGH, the information is a DATA
	PA8   ------> LCD_A0*/
	LL_GPIO_SetOutputPin(LCD_A0_GPIO_Port,LCD_A0_Pin);

	return;
}
void HAL_LCD_A0_Command(void)
{
	/*Pin PA8 is configured as A0 signal of LCD,
	when the A0 is LOW, the information is a COMMAND
	PA8   ------> LCD_A0*/
	LL_GPIO_ResetOutputPin(LCD_A0_GPIO_Port,LCD_A0_Pin);

	return;
}

void HAL_LCD_Send_Command(uint8_t command)
{
	/*Function to send a command through SPI1, it configures automatically the A0=0
	therefore, it is a command. It enables CHIP SELECT signal and disables it after transmission is done */
	MX_SPI1_CS_Enable();
	HAL_LCD_A0_Command();
	MX_SPI1_Send(command);
	LL_mDelay(0.1);
	MX_SPI1_CS_Disable();

	return;
}

void HAL_LCD_Send_Data(uint8_t data)
{
	/*Function to send a data through SPI1, it configures automatically the A0=1
	therefore, it is a data. It enables CHIP SELECT signal and disables it after transmission is done */
	MX_SPI1_CS_Enable();
	HAL_LCD_A0_Data();
	MX_SPI1_Send(data);
	LL_mDelay(0.1);
	MX_SPI1_CS_Disable();

	return;
}

void HAL_LCD_Clear(void)
{
	/*Function to clear ALL LCD, from page=0, column =0,
	to page = 3, column = 127, after clear, the cursor
	is set at page=0, column=0*/
	HAL_LCD_Send_Command(CMD_DISPLAY_ON_OFF(DISPLAY_OFF));
	for (uint8_t page=0 ; page <= MAX_PAGES ; page++)
	{

		HAL_LCD_Set_Position(0,page);
		for(uint8_t column=0;column<= MAX_WIDHT ; column++)
		{
			HAL_LCD_Send_Data(ERASE_BYTE);
		}
	}
	HAL_LCD_Set_Position(0,0);
	HAL_LCD_Send_Command(CMD_DISPLAY_ON_OFF(DISPLAY_ON));

	return;
}

void HAL_LCD_Set_Position(uint8_t column, uint8_t page)
{
	/*This function sets the position of the cursor, remember that
	MAX COLUMN = 127 and MAX PAGE = 3, the cursor is not explicit showed in the LCD,
	it is just a reference word to understand where the LCD starting is*/
	HAL_LCD_Send_Command(CMD_COLUMN_MSB(column));
	HAL_LCD_Send_Command(CMD_COLUMN_LSB(column));
	HAL_LCD_Send_Command(CMD_PAGE(page));

	return;
}
void HAL_LCD_Write_ascii(uint8_t ascii, uint8_t column, uint8_t page)
{
	/*This function requires a byte to print a single ascii character in the LCD,
	this function also requires the exact page and column to print the ascii character in the lcd
	remember that, MAX_WIDTH = 127, MAX_PAGE = 3 */
	HAL_LCD_Send_Command(CMD_DISPLAY_ON_OFF(DISPLAY_ON));
	HAL_LCD_Set_Position(column,page);

	uint8_t *arr = font;
	for (uint8_t i=0; i<MAX_PIXEL_WIDTH ; i++)
	{
		HAL_LCD_Send_Data(HAL_REVERSE_BYTE(arr[(ascii*5)+i]));
	}

	HAL_LCD_Send_Data(LETTER_SEPARATOR_BYTE);

	return;
}
uint8_t HAL_REVERSE_BYTE(uint8_t byte)
{
	/*This function reverse a single BYTE, why do we need this function?
	remember when we reversed the COMs in the HAL_LCD_Init() function, due this
	the line address of the pages was flip, this means that the MSB line of each page was in the bottom
	and the LSB was at the top. You need a function to reverse the data byte */
	byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
	byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
	byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;

	return byte;
}

void HAL_LCD_Write_AsciiString(uint8_t *word, uint8_t column, uint8_t page)
{
	/*This function writes a ascii string on the display, it could be a string like
	"Hello", "123", "Hello123" or "Hello 123", this function considers also spaces*/
	HAL_LCD_Set_Position(column,page);
	for (uint8_t i=0;i<21;i++)
	{
		if (word[i]=='\0')
		{
			return;
		}//
		else
		{
		HAL_LCD_Write_ascii(word[i],column,page);
		column+=6;
		}
	}

	return;


}

void HAL_LCD_Write_Number(uint8_t *number, uint8_t column, uint8_t page)
{
	/*This function writes a number of 2 digits, it also needs the column and page where you want the
	number, if the number is less than two digits, it will print 0#. Ex. If you want to print 9, the LCD
	will print 09*/
	uint8_t AsciiFirstDigit=*number/10+ADD_VALUE_TO_ASCII;
	uint8_t AsciiSecondDigit = *number%10+ADD_VALUE_TO_ASCII;
	uint8_t numberAscii [3]= {AsciiFirstDigit, AsciiSecondDigit,'\0'};
	HAL_LCD_Write_AsciiString(numberAscii,column,page);

	return;
}

void HAL_LCD_WELCOME_ENTER_TIME(uint8_t *PotValue,uint8_t *ButtonPressed, uint8_t *configuredRTC)
{
	/*This function is to illustrated the welcome screen of the LCD, the function illustrated the welcome message and afterwars it displays
	 the time to configure*/

	uint8_t hours =  (*PotValue)*0.24; // Calculation of hours (0-24) based on potentiometer value that goes from 0 to 100
	uint8_t minutes = (*PotValue)*0.59; // Calculation of minutes (0-59) based on potentiometer value that goes from 0 to 100
	uint8_t seconds = (*PotValue)*0.59; // Calculation of seconds (0-59) based on potentiometer value that goes from 0 to 100


	if (AlreadyEnterMenu==1)
	{
		switch(ConfigurationStage) //Configuration stage is necessary to know if hours were configured, afterwards minutes and finally seconds
		{

			case 0:
				HAL_LCD_Write_Number(&hours,0,3);
				if (*ButtonPressed==1)
				{
					ConfigurationStage++;
					HAL_LCD_Write_ascii(SYMBOL_ASCII_PLUS,108,3);
					LL_mDelay(2000);
				}
				break;

			case 1:
				HAL_LCD_Write_Number(&minutes,18,3);
				if (*ButtonPressed==1)
				{
					ConfigurationStage++;
					HAL_LCD_Write_ascii(SYMBOL_ASCII_PLUS,114,3);
					LL_mDelay(2000);
				}
				break;

			case 2:
				HAL_LCD_Write_Number(&seconds,36,3);
				if (*ButtonPressed==1)
				{
					ConfigurationStage++;
					HAL_LCD_Write_ascii(SYMBOL_ASCII_PLUS,120,3);
					LL_mDelay(2000);
				}
				break;

			default:
				AlreadyEnterMenu=0;
				ConfigurationStage=0;
				*configuredRTC+=1;
				HAL_LCD_Clear();
		}
	}
	else
	{
	HAL_LCD_Write_AsciiString("WELCOME", 0,0);
	HAL_LCD_Write_AsciiString("SMART PILLBOX", 0,1);
	HAL_LCD_Write_AsciiString("PLEASE ENTER TIME(24)", 0,2);
	HAL_LCD_Write_ascii(':',12,3);
	HAL_LCD_Write_ascii(':',30,3);
	AlreadyEnterMenu++;
	}

	return;
}
void HAL_LCD_MENU(uint8_t *temperature,uint8_t *ActualHour, uint8_t *ActualMinute, uint8_t *ActualSecond)
{
	/*Function to display the menu, this menu will refresh the time and the temperature*/


	if (AlreadyEnterMenu==1)
	{
		HAL_LCD_Write_Number(ActualHour, 30,0);
		HAL_LCD_Write_Number(ActualMinute, 48,0);
		HAL_LCD_Write_Number(ActualSecond, 66,0);
		HAL_LCD_Write_Number(temperature, 42,2);
	}
	else
	{
	HAL_LCD_Write_AsciiString("TIME ", 0,0);
	HAL_LCD_Write_ascii(':', 42,0);
	HAL_LCD_Write_ascii(':', 60,0);
	HAL_LCD_Write_AsciiString("SENSOR ", 0,2);
	HAL_LCD_Write_ascii(SYMBOL_ASCII_CELSIUS, 54,2);
	HAL_LCD_Write_ascii('C', 60,2);
	AlreadyEnterMenu=1;

	}

	return;
}
void HAL_LCD_ALARM_CONFIG(uint8_t *potValue, uint8_t *ButtonPressed, uint8_t *isSet)
{
	/*Function to configure the alarm, it does not matter if it is alarm 1 or 2 or 3*/
		uint8_t hours =  (*potValue)*0.24; // Calculation of hours (0-24) based on potentiometer value that goes from 0 to 100
		uint8_t minutes = (*potValue)*0.59; // Calculation of minutes (0-59) based on potentiometer value that goes from 0 to 100
		uint8_t seconds = (*potValue)*0.59; // Calculation of seconds (0-59) based on potentiometer value that goes from 0 to 100


		if (AlreadyEnterAlarmConfig==1)
		{
			switch(ConfigurationStage) //Configuration stage is necessary to know if hours were configured, afterwards minutes and finally seconds
			{

				case 0:
					HAL_LCD_Write_Number(&hours,30,0);
					if (*ButtonPressed==1)
					{
						ConfigurationStage++;
						HAL_LCD_Write_ascii(SYMBOL_ASCII_PLUS,108,3);
						LL_mDelay(2000);
					}
					break;

				case 1:
					HAL_LCD_Write_Number(&minutes,48,0);
					if (*ButtonPressed==1)
					{
						ConfigurationStage++;
						HAL_LCD_Write_ascii(SYMBOL_ASCII_PLUS,114,3);
						LL_mDelay(2000);
					}
					break;

				case 2:
					HAL_LCD_Write_Number(&seconds,66,0);
					if (*ButtonPressed==1)
					{
						ConfigurationStage++;
						HAL_LCD_Write_ascii(SYMBOL_ASCII_PLUS,120,3);
						LL_mDelay(2000);
					}
					break;

				default:
					AlreadyEnterAlarmConfig=0;
					ConfigurationStage=0;
					HAL_LCD_Clear();
					*isSet +=1;
			}
		}
		else
		{
		HAL_LCD_Write_AsciiString("TIME ", 0,0);
		HAL_LCD_Write_ascii(':', 42,0);
		HAL_LCD_Write_ascii(':', 60,0);
		AlreadyEnterAlarmConfig=1;
		}

		return;
}

void HAL_LCD_CLEAR_LINE(uint8_t line)
{
	HAL_LCD_Set_Position(0,line);
		for(uint8_t column=0;column<= MAX_WIDHT ; column++)
		{
			HAL_LCD_Send_Data(ERASE_BYTE);
		}

	HAL_LCD_Send_Command(CMD_DISPLAY_ON_OFF(DISPLAY_ON));

	return;
}
