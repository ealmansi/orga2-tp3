/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "defines.h"

void imprimir_nombre_del_grupo();

void inicializar_manejo_video();

void actualizar_canonear(dword_t dir_misil);
void actualizar_navegar(int nro_tarea, dword_t dir_ult_p1, dword_t dir_ult_p2, dword_t dir_nueva_p1, dword_t dir_nueva_p2);
void actualizar_fondear(int nro_tarea, dword_t dir_ult_p3, dword_t dir_nueva_p3);
void actualizar_desalojo(int nro_tarea, char* msj_desalojo);
void actualizar_bandera(int nro_tarea, byte_t* buffer_bandera);

void pintar_pantalla_modo_estado();
void pintar_pantalla_modo_mapa();

/* para debuggear */
#define 	punto(x,y)		(x), (y)
void dibujar_texto(char* str, int i1, int j1, byte_t color, byte_t* buffer);

extern int pantalla_activa;

#endif  /* !__SCREEN_H__ */
