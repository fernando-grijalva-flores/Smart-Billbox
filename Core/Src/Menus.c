#include <Menus.h>
#include "HAL_POT.h"
#include "HAL_RGB.h"
#include "HAL_LCD.h"
#include "HAL_RTC.h"
#include "HAL_TEMPSen.h"
// Estados de la FSM
typedef enum{
	E0,
  	E1,
  	E2,
  	E3,
	E4,
	E5,
	E6,
	E7
}Estados;

// Estado inicial
Estados EA = E0;

// Puntero seleccion
short Puntero = 0, first = 0, inicio = 0;
// Variables almacenamiento tiempo
uint8_t Horas, Minutos, IntervaloH1, IntervaloH2, IntervaloH3, IntervaloM1, IntervaloM2, IntervaloM3;
uint8_t Hora,Minuto,Segundo;

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
	if(first == 0){
		// Mostrado de valores fijos
		HAL_LCD_Write_AsciiString(word[w_configuration],24,0);
		HAL_LCD_Write_AsciiString(word[w_clock],48,1);
		HAL_LCD_Write_ascii(':',60,2);
		HAL_LCD_Write_AsciiString(word[w_accept],36,3);
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
		HAL_LCD_Write_AsciiString(word[w_pillsABC],18,0);
		HAL_LCD_Write_AsciiString(word[w_timeInterval],36,1);
		HAL_LCD_Write_ascii(':',60,2);
		HAL_LCD_Write_AsciiString(word[w_accept],36,3);
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
		HAL_LCD_Write_AsciiString(word[w_clock],48,0);
		HAL_LCD_Write_ascii(':',60,1);
		HAL_LCD_Write_AsciiString(word[w_temp],30,2);
		HAL_LCD_Write_ascii(SYMBOL_ASCII_CELSIUS,66,3);
		HAL_LCD_Write_ascii('C',72,3);
		first = 1;
	}
	// Obtener tiempo
	HAL_Get_ActualTime(&Hora,&Minuto,&Segundo);
	// Mostrar tiempo
	HAL_LCD_Write_Number(&Hora,48,1);
	HAL_LCD_Write_Number(&Minuto,66,1);
	// Temperatura
	uint8_t Temp = HAL_TEMPSen_ReadTemperature();
	LL_mDelay(1);
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
			HAL_LCD_Write_AsciiString(word[w_adjustClock],24,0);
			HAL_LCD_Write_AsciiString(word[w_adjustPill],12,1);
			HAL_LCD_Write_AsciiString(word[w_timeAndTemp],13,2);
			HAL_LCD_Write_AsciiString(word[w_timePills],6,3);
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
		HAL_LCD_Write_AsciiString("Tome pastilla",24,0);
		HAL_LCD_Write_AsciiString("Rojo Verde",36,1);
		HAL_LCD_Write_AsciiString("Azul",54,2);
		HAL_LCD_Write_AsciiString(">Entendido<",30,3);
		first = 1;
	}
	//if tiempo pastilla 1
	//HAL_LCD_Write_ascii('>',30,1);
	//else
	//HAL_LCD_Write_ascii(' ',30,1);
	//if tiempo pastilla 2
	//HAL_LCD_Write_ascii('>',60,1);
	//else
	//HAL_LCD_Write_ascii(' ',60,1);
	//if tiempo pastilla 3
	//HAL_LCD_Write_ascii('>',48,2);
	//else
	//HAL_LCD_Write_ascii(' ',48,2);

	if(btnC == 1 && btnC != btnCa){
		// Cambio de estado
		EA = E2;
		first = 0;
		HAL_LCD_Clear();
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
		HAL_LCD_Write_AsciiString(word[w_alarms],42,0);
		HAL_LCD_Write_AsciiString(word[w_red],30,1);
		HAL_LCD_Write_AsciiString(word[w_green],30,2);
		HAL_LCD_Write_AsciiString(word[w_blue],30,3);
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
		{E7,EDO_7}
};

void fsm(short btnU, short btnD,short btnL, short btnR, short btnC){
	MDE[EA].func(btnU, btnD, btnL, btnR, btnC);
}

void get_intervals(uint8_t *hr, uint8_t *min, uint8_t *H1, uint8_t *H2, uint8_t *H3, uint8_t *M1, uint8_t *M2, uint8_t *M3)
{
	*H1=IntervaloH1;
	*H2=IntervaloH2;
	*H3=IntervaloH3;
	*M1=IntervaloM1;
	*M2=IntervaloM2;
	*M3=IntervaloM3;
	*hr=Hora;
	*min=Minuto;
}

