#include <Diplays.h>
#include "HAL_POT.h"

// Estados de la FSM
typedef enum{
	E0,
  	E1,
  	E2,
  	E3,
	E4,
	E5,
	E6
}Estados;

// Estado inicial
Estados EA = E0;

// Puntero seleccion
short Puntero = 0;

// Variables almacenamiento tiempo
int Horas, Minutos, Intervalo1, Intervalo2, Intervalo3;

// Funciones por estado
void EDO_0(short btnU, short btnD, short btnL, short btnR, short btnC){
	//Configuracion de reloj
	// Codigo de estado inicio
	Horas = HAL_POT_Percentage(POT1_Channel)*23/100;
	Minutos = HAL_POT_Percentage(POT2_Channel)*59/100;
	HAL_LCD_Write_AsciiString("Configuracion",24,0);
	HAL_LCD_Write_AsciiString("Reloj",48,1);
	HAL_LCD_Write_Number(Horas,48,2);
	HAL_LCD_Write_ascii(':',60,2);
	HAL_LCD_Write_Number(Minutos,67,2);
	HAL_LCD_Write_AsciiString(">Aceptar<",36);
	// Codigo de estado fin
	// Cambio de estado
	if(btnC == 1 && btnC != btnCa){
		EA = E1;
		HAL_LCD_Clear();
	}
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
}

void EDO_1(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Codigo de estado inicio
	rgb_verde();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E2;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E0;
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
}

void EDO_2(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Codigo de estado inicio
	rgb_azul();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E3;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E1;
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
}

void EDO_3(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Codigo de estado inicio
	rgb_amarillo();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E4;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E2;
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
}

void EDO_4(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Codigo de estado inicio
	rgb_celeste();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E5;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E3;
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
}

void EDO_5(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Codigo de estado inicio
	rgb_morado();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E6;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E4;
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
}

void EDO_6(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Codigo de estado inicio
	rgb_blanco();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E0;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E5;
	btnUa = btnU;
	btnDa = btnD;
	btnLa = btnL;
	btnRa = btnR;
	btnCa = btnC;
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
		{E6,EDO_6}
};

void fsm(short btnU, short btnD,short btnL, short btnR, short btnC){
	MDE[EA].func(btnU, btnD, btnL, btnR, btnC);
}
//LL_GPIO_SetOutputPin(GPIOA,LD2_Pin);
//LL_mDelay(300);
//LL_GPIO_ResetOutputPin(GPIOA,LD2_Pin);
//LL_mDelay(300);
