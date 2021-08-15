#include <Diplays.h>
#include "HAL_POT.h"
#include "HAL_RGB.h"
#include "HAL_LCD.h"
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
short Puntero = 0, first = 0, inicio = 0;

// Variables almacenamiento tiempo
uint8_t Horas, Minutos, IntervaloH1, IntervaloH2, IntervaloH3, IntervaloM1, IntervaloM2, IntervaloM3;

// Estado anterior
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
	// Codigo de estado inicio
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Write_AsciiString("Configuracion",24,0);
		HAL_LCD_Write_AsciiString("Reloj",48,1);
		HAL_LCD_Write_ascii(':',60,2);
		HAL_LCD_Write_AsciiString(">Aceptar<",36,3);
		first = 1;
	}
	Horas = HAL_POT_Percentage(POT1_Channel)*23/100;
	Minutos = HAL_POT_Percentage(POT2_Channel)*59/100;
	HAL_LCD_Write_Number(&Horas,48,2);
	HAL_LCD_Write_Number(&Minutos,67,2);
	if(btnC == 1 && btnC != btnCa && inicio == 0){
		// Cambio de estado
		EA = E1;
		HAL_LCD_Clear();
		first = 0;
	}
	else if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		first = 0;
		EA = E1;
		HAL_LCD_Clear();
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_1(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Configuracion pastillas
	// Codigo de estado inicio
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Write_AsciiString("Pastilla  A B C",18,0);
		HAL_LCD_Write_AsciiString("Intervalo",36,1);
		HAL_LCD_Write_AsciiString(":",60,2);
		HAL_LCD_Write_AsciiString(">Aceptar<",36,3);
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
		HAL_LCD_Clear();
		first = 0;
		inicio = 1;
	}
	else if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		first = 0;
		EA = E3;
		HAL_LCD_Clear();
	}
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_2(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Pantalla principal
	// Codigo de estado inicio
	rgb_azul();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E3;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E1;
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_3(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Menu
	// Codigo de estado inicio
	rgb_amarillo();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E4;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E2;
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_4(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Alarma Temperatura
	// Codigo de estado inicio
	rgb_celeste();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E5;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E3;
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
}

void EDO_5(short btnU, short btnD, short btnL, short btnR, short btnC){
	// Alarma Pastilla
	// Codigo de estado inicio
	rgb_morado();
	// Codigo de estado fin
	// Cambio de estado
	if(btnU == 1 && btnU != btnUa && btnD == 0)
		EA = E6;
	else if(btnD == 1 && btnD != btnDa && btnU == 0)
		EA = E4;
	estado_Anterior(btnU, btnD, btnL, btnR, btnC);
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
		{E6,EDO_6}
};

void fsm(short btnU, short btnD,short btnL, short btnR, short btnC){
	MDE[EA].func(btnU, btnD, btnL, btnR, btnC);
}
//LL_GPIO_SetOutputPin(GPIOA,LD2_Pin);
//LL_mDelay(300);
//LL_GPIO_ResetOutputPin(GPIOA,LD2_Pin);
//LL_mDelay(300);
