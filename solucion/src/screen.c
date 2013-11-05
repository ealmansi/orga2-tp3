/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  
*/

#include "defines.h"
#include "screen.h"
#include "utils.h"
#include "colors.h"

void insertarFormatoRectangular(unsigned char format, unsigned int X,unsigned int Y,unsigned int ancho, unsigned int alto);
void printSquareText(unsigned int X, unsigned int Y, unsigned int long, char* text);

#define 	MEM_VIDEO_CANT_BYTES 	(2 * VIDEO_FILS * VIDEO_COLS)

void inicializar_buffer_modo_estado() {

	plantillaEstado();

	unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_ESTADO;

	memcpy(buffer, mem_video, MEM_VIDEO_CANT_BYTES);
}

void inicializar_buffer_modo_mapa() {

	plantillaMapa();

	unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_MAPA;

	memcpy(buffer, mem_video, MEM_VIDEO_CANT_BYTES);
}

void pintar_pantalla_modo_estado() {

	unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_ESTADO;

	memcpy(mem_video, buffer, MEM_VIDEO_CANT_BYTES - 160);
}

void pintar_pantalla_modo_mapa() {

	unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_MAPA;

	memcpy(mem_video, buffer, MEM_VIDEO_CANT_BYTES - 160);
}

void plantillaEstado(){
	int i;
	insertarFormatoRectangular(C_BG_BLACK + C_FG_WHITE, 0,0,80,1);
	printSquareText(0,0,80,"Mate Cocido Con Tres De Azucar / Jauja");
	insertarFormatoRectangular(C_BG_LIGHT_GREY LIGHTER,0,1,80,23);
	insertarFormatoRectangular(C_BG_BLACK + C_FG_WHITE,50,1,28,14);
	insertarFormatoRectangular(C_BG_BLUE + LIGHTER,50,1,28,1);


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
	int i;

	for(i=0; i<79; i++){
		printSquareText(0,i,80,"                                                                                ");
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

void imprimirNombreEquipo(){
	printSquareText(3,3,20,"Mate Cocido Con Tres De Azucar");
}

void cuadradoColor(){
	insertarFormatoRectangular(0xA0,5,5,7,2);
}

void imprimirTextoAca(void* buffer, int X, int Y, char* texto){
	char* buf = (char*) buffer;
	buf = buf + 2*(Y*80+X);
	memcpy(buf, texto, strlen(texto));
}

void insertarFormatoRectangularAca(void* buffer, char format, int X, int Y, int ancho, int alto){
	char* buf = (char*) buffer;
	buf++;
	int i,j;
	for (i = 0; i < alto; i++) {
		for (j = 0; j < ancho; j++) {
			buf[2*(80*Y+X)+2*j] = format;
		}
		buf = buf + 160;

	}
}

void printNumberToScreen(int X, int Y, int num){
	char* start = ((char*) VIDEO + 2*(80*Y+X));
	int size = int_size(num);
	int i;

	for (i = size-1; i >= 0; i--) {
		start[2*i] = 0x30 + num % 10;
		num = num / 10;
	}
}

	
