/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  
*/

#include "defines.h"
#include "screen.h"
#include "utils.h"
#include "colors.h"

/* definicion de la pantalla */

#define 	VIDEO_FILS 25
#define 	VIDEO_COLS 80
#define 	MEM_VIDEO_CANT_BYTES 	(2 * VIDEO_FILS * VIDEO_COLS)

#define 	punto(x,y)		(x), (y)

/* 
*	prototipos funciones auxiliares
*
*/

/* funciones de dibujo */
void dibujar_casillero(char caracter, int i, int j, byte_t color_fg, byte_t color_bg, byte_t* buffer);
void dibujar_rectangulo(int i1, int j1, int i2, int j2, byte_t color, byte_t* buffer);
void dibujar_texto(char* str, int i1, int j1, byte_t color, byte_t* buffer);

/* inicializacion */
void inicializar_buffer_modo_estado();
void inicializar_buffer_modo_mapa();

/* modo_estado */
void dibujar_barra_superior();
void dibujar_panel_superior();
void dibujar_banderas();
void dibujar_panel_ultimo_error();
void dibujar_panel_inferior();
void dibujar_paginas_por_tarea();
void dword_a_hexa_string(dword_t nro, char buffer[9]);
void dibujar_barra_inferior();

/* modo_mapa */
void dibujar_mar_y_tierra();
void dibujar_pagina(dword_t dir_pag, char caracter, byte_t color_fg, byte_t color_bg);

/* funciones de actualizacion */
void actualizar_pagina_en_mapa(dword_t dir_pag);
void actualizar_paginas_de_tarea_en_estado(int nro_tarea);

/* 
*	implementacion
*
*/

/* inicializacion */

dword_t dir_misil_actual;

dword_t paginas_por_tarea[3 * 8];
#define pagina_1_de_tarea(tarea) 	(paginas_por_tarea[3 * (tarea) + 0])
#define pagina_2_de_tarea(tarea) 	(paginas_por_tarea[3 * (tarea) + 1])
#define pagina_3_de_tarea(tarea) 	(paginas_por_tarea[3 * (tarea) + 2])

void inicializar_manejo_video() {

	dir_misil_actual = -1;

	int n;
	for (n = 0; n < 8; ++n) {

		pagina_1_de_tarea(n) = 0;
		pagina_2_de_tarea(n) = 0;
		pagina_3_de_tarea(n) = 0;
	}

	inicializar_buffer_modo_estado();
	inicializar_buffer_modo_mapa();

	actualizar_fondear(0, 0x0007F000);
	actualizar_fondear(2, 0x0017F000);
	actualizar_fondear(4, 0x0027F000);
	actualizar_fondear(6, 0x0037F000);
	actualizar_navegar(0, 0x0047F000, 0x0011F000);
	actualizar_navegar(1, 0x0057F000, 0x0022F000);
	actualizar_navegar(3, 0x0067F000, 0x0033F000);
	actualizar_navegar(5, 0x0077A000, 0x0027F000);
	actualizar_navegar(7, 0x0000F000, 0x0057F000);
	actualizar_canonear(0x0077F000);
}

/* modo_estado */

void inicializar_buffer_modo_estado() {

	dibujar_barra_superior();
	dibujar_panel_superior();
	dibujar_panel_inferior();
	dibujar_barra_inferior();
}

void dibujar_barra_superior() {

	dibujar_rectangulo(punto(0, 0), punto(1, VIDEO_COLS), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto(NOMBRE_GRUPO_STR, punto(0, 0), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
}

void dibujar_panel_superior() {

	dibujar_rectangulo(punto(1, 0), punto(16, VIDEO_COLS), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_banderas();
	dibujar_panel_ultimo_error();
}

void dibujar_banderas() {

	char nombre_navio[] = "NAVIO n";

	int i, j, n;

	i = 2; j = 2;
	for (n = 1; n <= 4; ++n, j += 12) {
		
		nombre_navio[6] = n + '0';
		dibujar_texto(nombre_navio, punto(i, j), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
		dibujar_rectangulo(punto(i + 1, j), punto(i + 6, j + 10), C_GREEN, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
		
		nombre_navio[6] = n + 4 + '0';
		dibujar_texto(nombre_navio, punto(i + 7, j), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
		dibujar_rectangulo(punto(i + 8, j), punto(i + 13, j + 10), C_GREEN, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	}
}

void dibujar_panel_ultimo_error() {

	dibujar_rectangulo(punto(1, 50), punto(2, VIDEO_COLS - 2), C_LIGHT_BLUE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_rectangulo(punto(2, 50), punto(15, VIDEO_COLS - 2), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);

	dibujar_texto("EAX", punto( 2, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("EBX", punto( 3, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("ECX", punto( 4, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("EDX", punto( 5, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("ESI", punto( 6, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("EDI", punto( 7, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("EBP", punto( 8, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("ESP", punto( 9, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("EIP", punto(10, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("CR0", punto(11, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("CR2", punto(12, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("CR3", punto(13, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("CR4", punto(14, 51), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("CS", punto( 2, 66), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("DS", punto( 3, 66), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("ES", punto( 4, 66), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("FS", punto( 5, 66), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("GS", punto( 6, 66), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("SS", punto( 7, 66), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_texto("EFLAGS", punto( 9, 66), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
}

void dibujar_panel_inferior() {

	// fondos
	dibujar_rectangulo(punto(16, 0), punto(24, 1), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_rectangulo(punto(16, 1), punto(24, 2), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_rectangulo(punto(16, 2), punto(24, VIDEO_COLS - 1), C_LIGHT_BLUE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_rectangulo(punto(16, VIDEO_COLS - 1), punto(24, VIDEO_COLS), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	
	// numeros de tarea
	char num[] = "n";

	int n;
	for (n = 0; n < 8; ++n) {
		num[0] = n + 1 + '0';
		dibujar_texto(num, punto(16 + n, 1), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	}

	for (n = 0; n < 8; ++n)	{
		actualizar_paginas_de_tarea_en_estado(n);
	}
}

void dword_a_hexa_string(dword_t nro, char buffer[9]) {

	int i;
	for (i = 0; i < 8; ++i) {
		int hexa_digit = BITS(4 * (i + 1), 4 * i, nro);
		buffer[8 - i - 1] = (hexa_digit < 10) ? (hexa_digit + '0') : (hexa_digit - 10 + 'A');
	}
	buffer[8] = 0;
}

void dibujar_barra_inferior() {

	dibujar_texto("Barra inferior no implementada (porque me dio paja)", punto(VIDEO_FILS - 1, 0), C_WHITE, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
	dibujar_rectangulo(punto(VIDEO_FILS - 1, 0), punto(VIDEO_FILS, VIDEO_COLS), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
}

/* modo_mapa */

void inicializar_buffer_modo_mapa() {

	dibujar_mar_y_tierra();
	dibujar_barra_inferior();
}

void dibujar_mar_y_tierra() {

	int i;
	for (i = 0; i <= AREA_MAR_FIN; i += 0x1000)
		actualizar_pagina_en_mapa(i);
}

/* funciones de actualizacion */

void actualizar_canonear(dword_t dir_misil) {

	dword_t dir_ult_misil = dir_misil_actual;
	dir_misil_actual = dir_misil;

	actualizar_pagina_en_mapa(dir_ult_misil);
	actualizar_pagina_en_mapa(dir_misil_actual);
}

void actualizar_navegar(int nro_tarea, dword_t dir_nueva_p1, dword_t dir_nueva_p2) {

	dword_t ult_p1 = pagina_1_de_tarea(nro_tarea),
			ult_p2 = pagina_2_de_tarea(nro_tarea);

	pagina_1_de_tarea(nro_tarea) = dir_nueva_p1;
	pagina_2_de_tarea(nro_tarea) = dir_nueva_p2;

	actualizar_pagina_en_mapa(ult_p1);
	actualizar_pagina_en_mapa(ult_p2);
	actualizar_pagina_en_mapa(dir_nueva_p1);
	actualizar_pagina_en_mapa(dir_nueva_p2);

	actualizar_paginas_de_tarea_en_estado(nro_tarea);
}

void actualizar_fondear(int nro_tarea, dword_t dir_nueva_p3) {

	dword_t ult_p3 = pagina_3_de_tarea(nro_tarea);

	pagina_3_de_tarea(nro_tarea) = dir_nueva_p3;

	actualizar_pagina_en_mapa(ult_p3);
	actualizar_pagina_en_mapa(dir_nueva_p3);

	actualizar_paginas_de_tarea_en_estado(nro_tarea);
}

void actualizar_desalojo(int nro_tarea, void* contexto, char* msj_desalojo) {

}

void actualizar_bandera(int nro_tarea, byte_t* buffer_bandera) {

}

void actualizar_pagina_en_mapa(dword_t dir_pag) {

	if(dir_pag == dir_misil_actual) {

		dibujar_pagina(dir_pag, ' ', C_LIGHT_RED, C_LIGHT_RED);
		return;
	}

	int n, temp, contador = 0;

	for (n = 0; n < 8; ++n) {
		if(pagina_1_de_tarea(n) == dir_pag || pagina_2_de_tarea(n) == dir_pag
											|| pagina_3_de_tarea(n) == dir_pag) {
			temp = n;
			contador++;
		}
	}

	switch(contador) {
	case 0:
		if(dir_pag < AREA_MAR_INICIO)
			dibujar_pagina(dir_pag, ' ', C_GREEN, C_GREEN);
		else
			dibujar_pagina(dir_pag, ' ', C_LIGHT_BLUE, C_LIGHT_BLUE);
		break;

	case 1:
		dibujar_pagina(dir_pag, temp + 1 + '0', C_BLACK, C_LIGHT_GREY);
		break;

	default:
		dibujar_pagina(dir_pag, 'X', C_WHITE, C_BROWN);
		break;
	}
}

void actualizar_paginas_de_tarea_en_estado(int n) {

	char buffer_nro_pagina[] = "Pi:0x00000000";

	buffer_nro_pagina[1] = '1';
	dword_a_hexa_string(pagina_1_de_tarea(n), buffer_nro_pagina + 5);
	dibujar_texto(buffer_nro_pagina, punto(16 + n, 3), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);

	buffer_nro_pagina[1] = '2';
	dword_a_hexa_string(pagina_2_de_tarea(n), buffer_nro_pagina + 5);
	dibujar_texto(buffer_nro_pagina, punto(16 + n, 17), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);

	buffer_nro_pagina[1] = '3';
	dword_a_hexa_string(pagina_3_de_tarea(n), buffer_nro_pagina + 5);
	dibujar_texto(buffer_nro_pagina, punto(16 + n, 31), C_BLACK, (byte_t*) ADDR_BUFFER_VIDEO_ESTADO);
}

/* funciones buffer -> memoria video */

void pintar_pantalla_modo_estado() {

	byte_t* mem_video = (byte_t*) ADDR_MEM_VIDEO;
	byte_t* buffer = (byte_t*) ADDR_BUFFER_VIDEO_ESTADO;

	memcpy(mem_video, buffer, MEM_VIDEO_CANT_BYTES);
}

void pintar_pantalla_modo_mapa() {

	byte_t* mem_video = (byte_t*) ADDR_MEM_VIDEO;
	byte_t* buffer = (byte_t*) ADDR_BUFFER_VIDEO_MAPA;

	memcpy(mem_video, buffer, MEM_VIDEO_CANT_BYTES);
}

/* auxiliares */

void dibujar_rectangulo(int i1, int j1, int i2, int j2, byte_t color, byte_t* buffer) {

	int i, j;
	for(i = i1; i < i2; ++i) {
		for(j = j1; j < j2; ++j) {
			buffer[2 * (j + i * VIDEO_COLS) + 1] &= 0x0F;
			buffer[2 * (j + i * VIDEO_COLS) + 1] |= color << 4;
		}
	}
}

void dibujar_texto(char* str, int i, int j, byte_t color, byte_t* buffer) {

	int n;
	for(n = 0; str[n] != 0; ++n) {
		buffer[2 * (j + i * VIDEO_COLS + n)] = str[n];
		buffer[2 * (j + i * VIDEO_COLS + n) + 1] &= 0xF0;
		buffer[2 * (j + i * VIDEO_COLS + n) + 1] |= color;
	}
}

void dibujar_casillero(char caracter, int i, int j, byte_t color_fg, byte_t color_bg, byte_t* buffer) {

	char caracter_str[2] = " ";
	caracter_str[0] = caracter;

	dibujar_texto(caracter_str, punto(i, j), color_fg, buffer);
	dibujar_rectangulo(punto(i, j), punto(i + 1, j + 1), color_bg, buffer);
}

void dibujar_pagina(dword_t dir_pag, char caracter, byte_t color_fg, byte_t color_bg) {

	int nro_pag = dir_pag / TAMANO_PAGINA;
	int i = nro_pag / VIDEO_COLS, j = nro_pag % VIDEO_COLS;
	dibujar_casillero(caracter, punto(i, j), color_fg, color_bg, (byte_t*) ADDR_BUFFER_VIDEO_MAPA);
}

