/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "gdt.h"
#include "defines.h"

int ind_navios[CANT_TAREAS];
int ind_banderas[CANT_TAREAS];
int proximo_navio;
int proxima_bandera;
int cant_navios_vivos;
int navios_pendientes;
int banderas_pendientes;

void sched_inicializar() {

	int i;
	for (i = 0; i < CANT_TAREAS; ++i) {

		ind_navios[i] = (GDT_IDX_TASK_OFFSET + i);
		ind_banderas[i] = (GDT_IDX_TASK_BANDERA_OFFSET + i);
	}
	proximo_navio = -1;
	proxima_bandera = -1;
	cant_navios_vivos = CANT_TAREAS;
	navios_pendientes = 4;
	banderas_pendientes = 0;
}

int sched_proximo_indice() {

	if(0 < navios_pendientes) {

		do {
			proximo_navio = ((proximo_navio + 1) % CANT_TAREAS);
		} while(ind_navios[proximo_navio] == 0);

		if(--navios_pendientes == 0) banderas_pendientes = cant_navios_vivos;

		return ind_navios[proximo_navio];

	} else if(0 < banderas_pendientes) {

		do {
			proxima_bandera = ((proxima_bandera + 1) % CANT_TAREAS);
		} while(ind_banderas[proxima_bandera] == 0);

		if(--banderas_pendientes == 0) navios_pendientes = 4;

		return ind_banderas[proxima_bandera];

	} else {

		return 0;
	}
}

void sched_desalojar_tarea(int nro_tarea) {

	ind_navios[nro_tarea] = 0;
	ind_banderas[nro_tarea] = 0;

	--cant_navios_vivos;
}