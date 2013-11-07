/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

void sched_inicializar();
int sched_proximo_indice();
void sched_desalojar_tarea(int nro_tarea);


#endif	/* !__SCHED_H__ */
