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

void imprimir_texto_buffer(char* texto, int X, int Y, byte_t* buffer);
void insertar_formato_rectangular_buffer(char format, int X, int Y, int ancho, int alto, byte_t* buffer);
void imprimir_numero_buffer(int num, int X, int Y, byte_t* buffer);

#define 	MEM_VIDEO_CANT_BYTES 	(2 * VIDEO_FILS * VIDEO_COLS)

void inicializar_buffer_modo_estado() {

	plantillaEstado();

	// unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	// unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_ESTADO;

	// memcpy(buffer, mem_video, MEM_VIDEO_CANT_BYTES);
}

void inicializar_buffer_modo_mapa() {

	plantillaMapa();

	// unsigned char* mem_video = (unsigned char*) ADDR_MEM_VIDEO;
	// unsigned char* buffer = (unsigned char*) ADDR_BUFFER_VIDEO_MAPA;

	// memcpy(buffer, mem_video, MEM_VIDEO_CANT_BYTES);
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

	byte_t* buffer = (byte_t*) ADDR_BUFFER_VIDEO_ESTADO;

	insertar_formato_rectangular_buffer(C_BG_BLACK + C_FG_WHITE, 0, 0, 80, 1, buffer);
	imprimir_texto_buffer("Mate Cocido Con Tres De Azucar / Jauja", 0, 0, buffer);
	insertar_formato_rectangular_buffer(C_BG_LIGHT_GREY LIGHTER, 0, 1, 80, 23, buffer);
	insertar_formato_rectangular_buffer(C_BG_BLACK + C_FG_WHITE, 50, 1, 28, 14, buffer);
	insertar_formato_rectangular_buffer(C_BG_BLUE + LIGHTER, 50, 1, 28, 1, buffer);

	insertar_formato_rectangular_buffer(C_BG_BLUE LIGHTER, 2, 16, 77, 8, buffer);
	insertar_formato_rectangular_buffer(C_BG_BLACK, 0, 16, 1, 8, buffer);
	insertar_formato_rectangular_buffer(C_BG_BLACK, 79, 16, 1, 8, buffer);

	imprimir_texto_buffer("12345678", 1, 16, buffer);
	
	int i;
	for (i = 2; i < 50; i+=12) {
		imprimir_texto_buffer("NAVIO", i ,2 ,buffer);
		imprimir_numero_buffer((i-2)/12+1, i+6, 2, buffer);

		insertar_formato_rectangular_buffer(C_BG_RED,i, 3, 10, 5, buffer);
	}
	for (i = 2; i < 50; i+=12) {
		imprimir_texto_buffer("NAVIO", i ,8 ,buffer);
		imprimir_numero_buffer((i-2)/12+5, i+6, 8, buffer);
		insertar_formato_rectangular_buffer(C_BG_RED,i, 9, 10, 5, buffer);
	}
	
	for (i = 0; i < 8; i++) {
		imprimir_texto_buffer("*", 5+3*i, 24, buffer);
		imprimir_numero_buffer(i+1, 4+3*i, 24, buffer);
		insertar_formato_rectangular_buffer(C_BG_LIGHT_GREY LIGHTER,4+3*i,24,2,1, buffer);
	}

	imprimir_texto_buffer("*", 79, 24, buffer);
	imprimir_texto_buffer("*", 0, 24, buffer);
	insertar_formato_rectangular_buffer(C_BG_LIGHT_GREY LIGHTER,0,24,1,1, buffer);
}

void plantillaMapa(){

	byte_t* buffer = (byte_t*) ADDR_BUFFER_VIDEO_MAPA;

	insertar_formato_rectangular_buffer(C_BG_GREEN, 0, 0, 80, 3, buffer);
	insertar_formato_rectangular_buffer(C_BG_GREEN, 0, 3, 16, 1, buffer);
	insertar_formato_rectangular_buffer(C_BG_BLUE LIGHTER, 16, 3, 80 - 16, 1, buffer);
	insertar_formato_rectangular_buffer(C_BG_BLUE LIGHTER, 0, 4, 80, 20, buffer);

	int i;
	for(i=0; i<79; i++){
		imprimir_texto_buffer("                                                                                ", 0, i, buffer);
	}
	
	for (i = 0; i < 8; i++) {
		imprimir_texto_buffer("*", 5+3*i, 24, buffer);
		imprimir_numero_buffer(i+1, 4+3*i, 24 ,buffer);
		insertar_formato_rectangular_buffer(C_BG_LIGHT_GREY LIGHTER,4+3*i,24,2,1, buffer);
	}

	imprimir_texto_buffer("*", 79, 24, buffer);
	imprimir_texto_buffer("*", 0, 24, buffer);
	insertar_formato_rectangular_buffer(C_BG_LIGHT_GREY LIGHTER,0,24,1,1, buffer);
}

void imprimirNombreEquipo(){
	printSquareText(3,3,20,"Mate Cocido Con Tres De Azucar");
}

void cuadradoColor(){
	insertarFormatoRectangular(0xA0,5,5,7,2);
}

void imprimir_texto_buffer(char* texto, int X, int Y, byte_t* buffer) {

	int i;
	for (i = 0; i < strlen(texto); ++i)
		buffer[2 * (Y * 80 + X + i)] = texto[i];
}

void insertar_formato_rectangular_buffer(char format, int X, int Y, int ancho, int alto, byte_t* buffer) {

	buffer++;
	int i,j;
	for (i = 0; i < alto; i++) {
		for (j = 0; j < ancho; j++) {
			buffer[2*(80*Y+X)+2*j] = format;
		}
		buffer = buffer + 160;
	}
}

void imprimir_numero_buffer(int num, int X, int Y, byte_t* buffer) {

	buffer += 2 * (80 * Y + X);
	int size = int_size(num);
	int i;

	for (i = size-1; i >= 0; i--) {
		buffer[2*i] = 0x30 + num % 10;
		num = num / 10;
	}
}