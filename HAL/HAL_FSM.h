#ifndef HAL_FSM_H_
#define HAL_FSM_H_
#endif

// Variables auxiliares de estado antiguo para detecion falling para cambiar de estado
short btnU,btnUa,btnD,btnDa;

void EDO_0(int,int);
void EDO_1(int,int);
void EDO_2(int,int);
void EDO_3(int,int);
void EDO_4(int,int);
void EDO_5(int,int);
void EDO_6(int,int);

void fsm(short,short);
