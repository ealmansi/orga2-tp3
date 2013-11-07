/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "defines.h"
#include "screen.h"
#include "colors.h"

extern dword_t selector;

dword_t arr_navios[CANT_TAREAS];
dword_t arr_banderas[CANT_TAREAS];
byte_t navio_actual;
byte_t bandera_actual;

byte_t navios_seguidos;
byte_t banderas_restantes = CANT_TAREAS;
byte_t banderas_seguidas;


byte_t buscar_proximo();

void sched_resetear_tick(){
	
}

void sched_desalojar_tarea(){
	dword_t sel = selector >> 3;
	if (sel < 0x19) {
		dibujar_texto("El selector recibido no corresponde ni a una tarea ni a una bandera", punto(0, 0), C_WHITE, (byte_t*) ADDR_MEM_VIDEO);
		int cero = 0;
		int t = 1/cero; //Que explote todo y pare la ejecución.
		t++;
		}
	
	sel -= 0x18;

	if (sel < 0x9){

		arr_navios[navio_actual-1]=0;
		arr_banderas[navio_actual-1]=0;

	} else if (sel >= 0x9 && sel < 0x10){

		arr_navios[bandera_actual-1] = 0;
		arr_banderas[bandera_actual-1] = 0;

	} else {

		dibujar_texto("El selector recibido se va de la gdt.", punto(0, 0), C_WHITE, (byte_t*) ADDR_MEM_VIDEO);

	}
	
}

void sched_inicializar() {
	int i = 0;

	for (i = 0; i < CANT_TAREAS; i++) {
		arr_navios[i] = (0x19+i) << 3;
		arr_banderas[i] = (0x21+i) << 3 ;
	}
	navio_actual = 0;
	bandera_actual = 0;
	banderas_seguidas = 0;
	navios_seguidos = 0;

}


unsigned short sched_proximo_indice() {

	if (navios_seguidos <= 3) {

		navios_seguidos++;
		buscar_proximo(&navio_actual, &arr_navios);
		return arr_navios[navio_actual-1];

	} else if (banderas_seguidas < banderas_restantes) {

		buscar_proximo(&bandera_actual, &arr_banderas);
		banderas_seguidas++;
		return arr_banderas[bandera_actual-1];

	} else {

		navios_seguidos = 1;
		banderas_seguidas = 0;
		buscar_proximo(&navio_actual, &arr_navios);

		return arr_navios[navio_actual-1];
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
