/*
 * HAL_JOYSTICK.c
 *
 *  Created on: 16/08/2021
 *      Author: fer06
 */

#include "HAL_JOYSTICK.h"
#include "gpio.h"

short HAL_JOYSTICK_CenterPressed(void)
{
	return MX_Joystick_Center();
}
short HAL_JOYSTICK_UpPressed(void)
{
	return MX_Joystick_Up();
}
short HAL_JOYSTICK_DownPressed(void)
{
	return MX_Joystick_Down();
}
short HAL_JOYSTICK_RightPressed(void)
{
	return MX_Joystick_Right();
}
short HAL_JOYSTICK_LeftPressed(void)
{
	return MX_Joystick_Left();
}
