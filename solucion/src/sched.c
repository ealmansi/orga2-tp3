/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "defines.h"
#include "screen.h"

dword_t sel_navios[CANT_TAREAS];
dword_t sel_banderas[CANT_TAREAS];
byte_t navio_actual;
byte_t bandera_actual;

byte_t navios_seguidos = 0;
byte_t banderas_restantes = CANT_TAREAS;
byte_t banderas_seguidas = 0;


byte_t buscar_proximo();


void sched_inicializar() {
	int i = 0;

	for (i = 0; i < CANT_TAREAS; i++) {
		sel_navios[i] = (0x19+i) << 3;
		sel_banderas[i] = (0x21+i) << 3 ;
	}
	navio_actual = 1;
	bandera_actual = 1;

}


unsigned short sched_proximo_indice() {

	if (navios_seguidos <= 3) {

		navios_seguidos++;
		buscar_proximo(&navio_actual, &sel_navios);
		return sel_navios[navio_actual-1];

	} else if (banderas_seguidas < banderas_restantes) {

		buscar_proximo(&bandera_actual, &sel_banderas);
		banderas_seguidas++;
		return sel_banderas[bandera_actual-1];

	} else {

		navios_seguidos = 1;
		banderas_seguidas = 0;
		buscar_proximo(&navio_actual, &sel_navios);

		return sel_navios[navio_actual-1];
	}
}

byte_t buscar_proximo(byte_t* actual, dword_t** arreglo){
	byte_t aux = *actual;
	(*actual)++;
	if (*actual>CANT_TAREAS) {
		*actual=1;
	}
	
	while ((*actual) != aux && (*arreglo)[(*actual)-1]==0) {
		(*actual)++;
		if ((*actual) == CANT_TAREAS) {
			(*actual) = 1;
		}
	}
	if ((*actual) == aux) {
		return 0;
	}
	
	return (*actual);
}
