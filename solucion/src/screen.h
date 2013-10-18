/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__


/* Definicion de la pantalla */
#define VIDEO_FILS 25
#define VIDEO_COLS 80

void screen_pintar_pantalla();

void inicializar_buffer_modo_estado();
void inicializar_buffer_modo_mapa();
void pintar_pantalla_modo_estado();
void pintar_pantalla_modo_mapa();

#endif  /* !__SCREEN_H__ */
