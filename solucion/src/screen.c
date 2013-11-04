/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  
*/

#include "defines.h"
#include "screen.h"
#include "utils.h"

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

	memcpy(buffer, mem_video, MEM_VIDEO_CANT_BYTES);

}

void pintar_pantalla_modo_mapa() {

	unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_MAPA;

	memcpy(buffer,mem_video, MEM_VIDEO_CANT_BYTES);

}

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


void imprimirNombreEquipo(){
	printSquareText(3,3,20,"Mate Cocido Con Tres De Azucar");
}


void cuadradoColor(){
	insertarFormatoRectangular(0xA0,5,5,7,7);

}
