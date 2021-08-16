#ifndef Diplays_H_
#define Diplays_H_
#endif


#include "main.h"

// Variables auxiliares de estado antiguo para detecion falling para cambiar de estado
short btnU, btnUa, btnD, btnDa, btnL, btnLa, btnR, btnRa, btnC, btnCa;

void EDO_0(short,short,short,short,short);
void EDO_1(short,short,short,short,short);
void EDO_2(short,short,short,short,short);
void EDO_3(short,short,short,short,short);
void EDO_4(short,short,short,short,short);
void EDO_5(short,short,short,short,short);
void EDO_6(short,short,short,short,short);

void fsm(short,short,short,short,short);

/* Word defines */

	/*This are the all the used words in order to
	display them in the LCD with a particular screen*/

#define	w_configuration				(0)
#define w_clock						(1)
#define w_accept					(2)
#define w_pillsABC					(3)
#define w_timeInterval				(4)
#define w_starting					(5)
#define w_temp						(6)
#define w_adjustClock				(7)
#define w_adjustPill				(8)
#define w_timeAndTemp				(9)
#define w_timePills					(10)
#define w_overTemp					(11)
#define w_takePill					(12)
#define w_red						(13)
#define w_green						(14)
#define	w_blue						(15)
#define w_okay						(16)

static uint8_t word[17][21]= {
		"Configuracion", //0
		"Reloj",
		">Aceptar<",
		"Pastilla  A B C",
		"Intervalo", //4
		"Iniciando",
		"Temperatura",
		"Ajustar reloj",
		"Ajustar pastilla", //8
		"Hora y temperatura",
		"Intervalos pastillas",
		"Sobrepasada",
		"Tome pastilla", //12
		"Rojo",
		"Verde",
		"Azul",
		">Entendido<" //16
};

