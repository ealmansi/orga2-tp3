/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  
*/

#include "defines.h"
#include "screen.h"
#include "utils.h"
#include "colors.h"

extern void insertarFormatoRectangular(unsigned char format, unsigned int X,unsigned int Y,unsigned int ancho, unsigned int alto);
extern void printSquareText(unsigned int X, unsigned int Y, unsigned int long, char* text);

#define 	MEM_VIDEO_CANT_BYTES 	(2 * VIDEO_FILS * VIDEO_COLS)

void inicializar_buffer_modo_estado() {

	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_ESTADO;

	memclear(buffer, MEM_VIDEO_CANT_BYTES);
}

void inicializar_buffer_modo_mapa() {

	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_MAPA;

	memclear(buffer, MEM_VIDEO_CANT_BYTES);
}

void pintar_pantalla_modo_estado() {

	unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_ESTADO;

	memcpy(mem_video, buffer, MEM_VIDEO_CANT_BYTES);
}

void pintar_pantalla_modo_mapa() {

	unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_MAPA;

	memcpy(mem_video, buffer, MEM_VIDEO_CANT_BYTES);
}

void plantillaEstado(){
	int i;
	insertarFormatoRectangular(C_BG_BLACK + C_FG_WHITE, 0,0,80,1);
	printSquareText(0,0,80,"Mate Cocido Con Tres De Azucar / Jauja");
	insertarFormatoRectangular(C_BG_LIGHT_GREY LIGHTER,0,1,80,23);
	insertarFormatoRectangular(0x0F,50,1,28,14);



	insertarFormatoRectangular(C_BG_BLUE LIGHTER,2,16,77,8);
	insertarFormatoRectangular(C_BG_BLACK,0,16,1,8);
	insertarFormatoRectangular(C_BG_BLACK,79,16,1,8);

	printSquareText(1,16,1,"12345678");
	
	for (i = 2; i < 50; i+=12) {
		printSquareText(i,2,5,"NAVIO");
		printNumberToScreen(i+6,2,(i-2)/12+1);

		insertarFormatoRectangular(C_BG_RED,i, 3, 10, 5);
	}
	for (i = 2; i < 50; i+=12) {
		printSquareText(i,8,5,"NAVIO");
		printNumberToScreen(i+6,8,(i-2)/12+5);
		insertarFormatoRectangular(C_BG_RED,i, 9, 10, 5);
	}
	
	for (i = 0; i < 8; i++) {
		printSquareText(5+3*i,24,1,"*");
		printNumberToScreen(4+3*i,24,i+1);
		insertarFormatoRectangular(C_BG_LIGHT_GREY LIGHTER,4+3*i,24,2,1);
	}

	printSquareText(79,24,1,"*");
	printSquareText(0,24,1,"*");
	insertarFormatoRectangular(C_BG_LIGHT_GREY LIGHTER,0,24,1,1);

}


void plantillaMapa(){
	insertarFormatoRectangular(C_BG_GREEN, 0,0,80,3);
	insertarFormatoRectangular(C_BG_GREEN, 0,3,16,1);
	insertarFormatoRectangular(C_BG_BLUE LIGHTER, 16, 3, 80 - 16, 1);
	insertarFormatoRectangular(C_BG_BLUE LIGHTER, 0, 4, 80, 20);

}



void imprimirNombreEquipo(){
	printSquareText(3,3,20,"Mate Cocido Con Tres De Azucar");
}


void cuadradoColor(){
	insertarFormatoRectangular(0xA0,5,5,7,2);

}


