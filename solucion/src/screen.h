/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "defines.h"

typedef struct str_screen_estado_tarea {
	dword_t eflags;
	dword_t edi;
	dword_t esi;
	dword_t ebp;
	dword_t esp;
	dword_t ebx;
	dword_t edx;
	dword_t ecx;
	dword_t eax;
	dword_t eip;
} screen_estado_tarea;

void imprimir_nombre_del_grupo();

void inicializar_manejo_video();

void actualizar_canonear(dword_t dir_misil);
void actualizar_navegar(int nro_tarea, dword_t dir_nueva_p1, dword_t dir_nueva_p2);
void actualizar_fondear(int nro_tarea, dword_t dir_pag_anclada);
//void actualizar_desalojo(dword_t eflags, dword_t edi, dword_t esi, dword_t ebp, dword_t esp, dword_t ebx, dword_t edx, dword_t ecx, dword_t eax, dword_t eip, int nro_tarea , char* msj_desalojo)
void actualizar_bandera(int nro_tarea, byte_t* buffer_bandera);

void pintar_pantalla_modo_estado();
void pintar_pantalla_modo_mapa();

/* para debuggear */
#define 	punto(x,y)		(x), (y)
void dibujar_texto(char* str, int i1, int j1, byte_t color, byte_t* buffer);

#endif  /* !__SCREEN_H__ */
