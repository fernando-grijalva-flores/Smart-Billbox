#include "HAL_BUZZER.h"

//Function to initialize the Buzzer
void HAL_Buzzer_Init(void)
{
	MX_TIM2_Init();
	return;
}

//Functions used to modify the state of the Buzzer
void HAL_Buzzer_State(uint8_t state)
{
	if(!state)
	{
		MX_PWM_TurnOff();
	}else
	{
		MX_PWM_TurnOn();
	}
	return;
}
