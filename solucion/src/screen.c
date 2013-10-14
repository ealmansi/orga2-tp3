/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
extern void insertarFormatoRectangular(unsigned char format, unsigned int X,unsigned int Y,unsigned int ancho, unsigned int alto);
extern void printSquareText(unsigned int X, unsigned int Y, unsigned int long, char* text);

void plantillaEstado(){
	insertarFormatoRectangular(0x70,0,1,80,23);
	insertarFormatoRectangular(0x0F,50,1,28,14);


	insertarFormatoRectangular(0x87,2,10,77,1);
	printSquareText(2,10,10,"aaaaaaaaaa");
	insertarFormatoRectangular(0x90,2,11,77,1);
	insertarFormatoRectangular(0xA0,2,12,77,1);
	insertarFormatoRectangular(0xB0,2,13,77,1);
	insertarFormatoRectangular(0xC0,2,14,77,1);
	insertarFormatoRectangular(0xD0,2,15,77,1);
	insertarFormatoRectangular(0xE0,2,16,77,1);
	insertarFormatoRectangular(0xF0,2,17,77,1);

	insertarFormatoRectangular(0x00,2,17,77,1);
	insertarFormatoRectangular(0x10,2,18,77,1);
	insertarFormatoRectangular(0x20,2,19,77,1);
	insertarFormatoRectangular(0x30,2,20,77,1);
	insertarFormatoRectangular(0x40,2,21,77,1);
	insertarFormatoRectangular(0x50,2,22,77,1);
	insertarFormatoRectangular(0x60,2,23,77,1);
	insertarFormatoRectangular(0x70,2,24,77,1);
}



