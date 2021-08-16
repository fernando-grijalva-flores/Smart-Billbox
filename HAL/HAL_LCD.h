/*
 * HAL_LCD.h
 *
 *  Created on: 08/08/2021
 *      Author: fer06
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

/*Default includes*/

#include "main.h"

/* LCD defines and macros */

#define ADC_REVERSE						(0x01)
#define ADC_NORMAL						(0x00)
#define CMD_ADC_SELECT(adc)				(0xA0 | (adc & 0x01))

#define DISPLAY_ON						(0x01)
#define DISPLAY_OFF						(0x00)
#define CMD_DISPLAY_ON_OFF(on_off)		(0xAE |(0x01 & on_off))

#define COM_DIRECTION_REVERSE			(0x08)
#define COM_DIRECTION_NORMAL			(0x00)
#define CMD_COM_DIRECTION(dir)			(0xC0 | (dir & 0x0F))

#define CMD_BIAS_17						(0x01)
#define CMD_BIAS_19						(0x02)
#define CMD_BIAS_RATIO(bias)			(0xA0 | (bias & 0x0F))

#define PWR_INTERNAL_SUPPLY				(0x07)
#define CMD_PWR_CONTROL(control)		(0x28 | (control & 0x07))

#define RES_RATIO_35					(0x01)
#define CMD_RES_RATIO(ratio)			(0x20 | (ratio & 0x07))

#define CMD_ELEC_VOL_MODE				(0x81)
#define	CMD_ELEC_VOL_SET_LOW			(0x1F)

#define LCD_POINTS_NORMAL				(0x00)
#define LCD_POINTS_ALL					(0x01)
#define CMD_LCD_POINTS(all_normal)		(0xA4 | (all_normal & 0x01))

#define MAX_WIDHT						(127)
#define MAX_PAGES						(3)
#define MAX_PIXEL_WIDTH					(5)

#define CMD_COLUMN_MSB(column)			(0x10 | ((column>>4) & 0x0F))
#define CMD_COLUMN_LSB(column)			(0x00 | (column & 0x0F))

#define CMD_PAGE(page)					(0xB0 | (page & 0x0F))

#define ERASE_BYTE						(0x00)
#define	SET_BYTE						(0xFF)
#define LETTER_SEPARATOR_BYTE			(0x00)

#define ADD_VALUE_TO_ASCII				(48)
#define	SYMBOL_ASCII_PLUS				'+'
#define SYMBOL_ASCII_CELSIUS			(248)





/* HAL LCD Functions prototypes */

void HAL_LCD_Init(void);

void HAL_LCD_Reset(void);	//Function to reset the LCD

void HAL_LCD_A0_Data(void); //Function to specify the information coming from A0 is data
void HAL_LCD_A0_Command(void); //Function to specify the information coming from A0 is command

void HAL_LCD_Send_Command(uint8_t command); //Function to send a command through SPI to the LCD
void HAL_LCD_Send_Data(uint8_t data); //Function to send a data through SPI to the LCD

void HAL_LCD_Clear(void); //Function to clear display

void HAL_LCD_Set_Position(uint8_t column, uint8_t page); //Function to set position, you need to set a column and page

void HAL_LCD_Write_ascii(uint8_t ascii, uint8_t column, uint8_t page); //Function to write a single ascii character with column and page

void HAL_LCD_Write_AsciiString(uint8_t word[21],uint8_t column, uint8_t page); //Function to write a ascii string

void HAL_LCD_Write_Number(uint8_t *number, uint8_t column, uint8_t page); //Function to write a number

uint8_t HAL_REVERSE_BYTE(uint8_t byte); //Function to reverse a BYTE

void HAL_LCD_WELCOME_ENTER_TIME(uint8_t *PotValue,uint8_t *ButtonPressed, uint8_t *configuredRTC); //Function of welcome screen

void HAL_LCD_MENU(uint8_t *temperature,uint8_t *ActualHour, uint8_t *ActualMinute, uint8_t *ActualSecond); // Function to display menu in the LCD

void HAL_LCD_ALARM_CONFIG(uint8_t *potValue, uint8_t *ButtonPressed,uint8_t *isSet); //Function to display alarm configuration
/*HAL LCD fonts*/

void HAL_LCD_CLEAR_LINE(uint8_t line); //Function to clear a single line


#endif /* HAL_LCD_H_ */
