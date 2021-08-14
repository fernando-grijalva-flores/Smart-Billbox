#include "HAL_FSM.h"

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

// Funciones por estado
void EDO_0(int btnU, int btnD){
	// Codigo de estado inicio
	rgb_rojo();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E1;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E6;
	btnUa = btnU;
	btnDa = btnD;
}

void EDO_1(int btnU, int btnD){
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
}

void EDO_2(int btnU, int btnD){
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
}

void EDO_3(int btnU, int btnD){
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
}

void EDO_4(int btnU, int btnD){
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
}

void EDO_5(int btnU, int btnD){
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
}

void EDO_6(int btnU, int btnD){
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
}

// Estructura para asignar una funcion a cada estado
typedef struct {
	Estados Estado;
	void (*func)(int,int);
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

void fsm(short btnu, short btnd){
	MDE[EA].func(btnu,btnd);
}
//LL_GPIO_SetOutputPin(GPIOA,LD2_Pin);
//LL_mDelay(300);
//LL_GPIO_ResetOutputPin(GPIOA,LD2_Pin);
//LL_mDelay(300);