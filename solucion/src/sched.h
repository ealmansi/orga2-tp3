/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "defines.h"

void insertarFormatoRectangular(unsigned char format, unsigned int X,unsigned int Y,unsigned int ancho, unsigned int alto);
void printSquareText(unsigned int X, unsigned int Y, unsigned int long, char* text);

void sched_inicializar();
unsigned short sched_proximo_indice();
void sched_resetear_tick();
void hundir_navio();

extern byte_t es_navio;
extern byte_t navio_actual;
extern byte_t bandera_actual;
extern byte_t ultimo_hundido;

#endif	/* !__SCHED_H__ */
