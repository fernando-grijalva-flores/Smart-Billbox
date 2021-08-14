#include "HAL_RGB.h"
#include "gpio.h"

void rgb_rojo(){
	MX_RGB_Red(0);
	MX_RGB_Green(1);
	MX_RGB_Blue(1);
}
void rgb_verde(){
	MX_RGB_Red(1);
	MX_RGB_Green(0);
	MX_RGB_Blue(1);
}
void rgb_azul(){
	MX_RGB_Red(1);
	MX_RGB_Green(1);
	MX_RGB_Blue(0);
}
void rgb_amarillo(){
	MX_RGB_Red(0);
	MX_RGB_Green(0);
	MX_RGB_Blue(1);
}
void rgb_celeste(){
	MX_RGB_Red(1);
	MX_RGB_Green(0);
	MX_RGB_Blue(0);
}
void rgb_morado(){
	MX_RGB_Red(0);
	MX_RGB_Green(1);
	MX_RGB_Blue(0);
}
void rgb_blanco(){
	MX_RGB_Red(0);
	MX_RGB_Green(0);
	MX_RGB_Blue(0);
}
void rgb_apagado(){
	MX_RGB_Red(1);
	MX_RGB_Green(1);
	MX_RGB_Blue(1);
}
