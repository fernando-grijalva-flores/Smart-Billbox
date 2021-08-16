#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

/*Add the header file to use all BSP PWM functions*/
#include "tim.h"

//This structure is used to define the possible states of the buzzer
typedef enum
{
	On	=	1,
	Off	=	0

}Buzzer_State;

//Function to initialize the Buzzer
void HAL_Buzzer_Init(void);

//Functions used to modify the state of the Buzzer
void HAL_Buzzer_State(uint8_t state);

#endif /* HAL_BUZZER_H_ */
