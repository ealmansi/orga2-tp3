/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

void insertarFormatoRectangular(unsigned char format, unsigned int X,unsigned int Y,unsigned int ancho, unsigned int alto);
void printSquareText(unsigned int X, unsigned int Y, unsigned int long, char* text);

void sched_inicializar();
unsigned short sched_proximo_indice();


#endif	/* !__SCHED_H__ */
