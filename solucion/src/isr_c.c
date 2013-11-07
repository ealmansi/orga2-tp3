#include "defines.h"
#include "i386.h"
#include "isr.h"
#include "gdt.h"
#include "tss.h"
#include "syscall.h"
#include "game.h"
#include "screen.h"
#include "sched.h"

int obtener_indice_tarea_en_ejecucion();
int es_navio(int indice);
int es_bandera(int indice);
int numero_tarea(int indice);

#define BANDERA_BUFFER  0x40001000

int _isr32_c() {

	int ind_tarea = obtener_indice_tarea_en_ejecucion();

	if(es_bandera(ind_tarea)) {
		sched_desalojar_tarea(numero_tarea(ind_tarea));
	}

	int ind_prox = sched_proximo_indice();
	if(ind_prox == 0) return GDT_IDX_TASK_IDLE;

	if(es_bandera(ind_prox)) {
		tss_inicializar_bandera(numero_tarea(ind_prox));
	}

	return ind_prox;
}

void _isr0x50_c(unsigned int type, unsigned int arg1, unsigned int arg2) {

	int ind_tarea = obtener_indice_tarea_en_ejecucion();
	int nro_tarea = numero_tarea(ind_tarea);

	unsigned int ret;
	switch(type) {
	case SYS_FONDEAR:
		ret = game_fondear(arg1);
		actualizar_fondear(nro_tarea, arg1);
		break;
	case SYS_CANONEAR:
		ret = game_canonear(arg1, arg2);
		actualizar_canonear(arg1);
		break;
	case SYS_NAVEGAR:
		ret = game_navegar(arg1, arg2);
		actualizar_navegar(nro_tarea, arg1, arg2);
		break;
	default:
		ret = FALSE;
		break;
	}

	if(ret == FALSE) {
		int ind_tarea = obtener_indice_tarea_en_ejecucion();
		sched_desalojar_tarea(numero_tarea(ind_tarea));
	}
}

void _isr0x66_c() {

	int ind_tarea = obtener_indice_tarea_en_ejecucion();
	int nro_tarea = numero_tarea(ind_tarea);

	if(es_navio(ind_tarea)) {
		sched_desalojar_tarea(nro_tarea);
	}

	actualizar_bandera(nro_tarea, (byte_t*) BANDERA_BUFFER);
}

int obtener_indice_tarea_en_ejecucion() {
	
	return (rtr() >> 3);	
}

int es_navio(int indice) {

	return (GDT_IDX_TASK_OFFSET <= indice
		&& indice < (GDT_IDX_TASK_OFFSET + CANT_TAREAS));
}

int es_bandera(int indice) {

	return (GDT_IDX_TASK_BANDERA_OFFSET <= indice
		&& indice < (GDT_IDX_TASK_BANDERA_OFFSET + CANT_TAREAS));
}

int numero_tarea(int indice) {

	if(GDT_IDX_TASK_OFFSET <= indice && indice < (GDT_IDX_TASK_OFFSET + CANT_TAREAS))
		return indice - GDT_IDX_TASK_OFFSET;
	else
		return indice - GDT_IDX_TASK_BANDERA_OFFSET;
}