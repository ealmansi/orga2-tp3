#include "defines.h"
#include "i386.h"
#include "isr.h"
#include "gdt.h"
#include "tss.h"
#include "syscall.h"
#include "game.h"
#include "mmu.h"
#include "screen.h"
#include "sched.h"
#include "utils.h"

int obtener_indice_tarea_en_ejecucion();
int es_navio(int indice);
int es_bandera(int indice);
int numero_tarea(int indice);
void desalojar_tarea(int nro_tarea, char* msj_desalojo);

#define BANDERA_BUFFER  0x40001000

int _isr32_c() {

	int ind_tarea = obtener_indice_tarea_en_ejecucion();

	if (!ind_tarea) return 0;

	if(es_bandera(ind_tarea)) {
		desalojar_tarea(numero_tarea(ind_tarea), "Bandera excedio tick");
	}

	int ind_prox = sched_proximo_indice();

	if(es_bandera(ind_prox)) {
		tss_inicializar_bandera(numero_tarea(ind_prox));
	}

	return ind_prox;
}

void _isr0x50_c(unsigned int type, unsigned int arg1, unsigned int arg2) {

	int ind_tarea = obtener_indice_tarea_en_ejecucion();
	int nro_tarea = numero_tarea(ind_tarea);
	
	if(es_bandera(ind_tarea)) {
		desalojar_tarea(nro_tarea, "Bandera llamo INT 50");
		return;
	}

	dword_t dir_ult_p1 = pagina_1_de_tarea(nro_tarea),
			dir_ult_p2 = pagina_2_de_tarea(nro_tarea),
			dir_ult_p3 = pagina_3_de_tarea(nro_tarea);

	int ret = FALSE;

	switch(type) {
	case SYS_FONDEAR:
		ret = game_fondear(arg1);
		pagina_3_de_tarea(nro_tarea) = arg1;
		if (ret == TRUE) actualizar_fondear(nro_tarea, dir_ult_p3, arg1);
		else desalojar_tarea(numero_tarea(ind_tarea), "Syscall fondear devolvio False");
		break;
	case SYS_CANONEAR:
		ret = game_canonear(arg2, arg1);
		if (ret == TRUE) actualizar_canonear(arg2);
		else desalojar_tarea(numero_tarea(ind_tarea), "Syscall canonear devolvio False");
		break;
	case SYS_NAVEGAR:
		ret = game_navegar(arg1, arg2, dir_ult_p1, dir_ult_p2);
		pagina_1_de_tarea(nro_tarea) = arg1;
		pagina_2_de_tarea(nro_tarea) = arg2;
		if (ret == TRUE) actualizar_navegar(nro_tarea, dir_ult_p1, dir_ult_p2, arg1, arg2);
		else desalojar_tarea(numero_tarea(ind_tarea), "Syscall navegar devolvio False");
		break;
	default:
		desalojar_tarea(numero_tarea(ind_tarea), "Syscall indefinida");
		break;
	}
}

void _isr0x66_c() {

	int ind_tarea = obtener_indice_tarea_en_ejecucion();
	int nro_tarea = numero_tarea(ind_tarea);

	if(es_navio(ind_tarea)) {
		desalojar_tarea(nro_tarea, "Navio llamo INT 66");
		return;
	}

	actualizar_bandera(nro_tarea, (byte_t*) BANDERA_BUFFER);
}

void desalojar_tarea(int nro_tarea, char* msj_desalojo) {

	sched_desalojar_tarea(nro_tarea);
	actualizar_desalojo(nro_tarea, msj_desalojo);
}

void _isr0_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Divide Error Exception");
}

void _isr1_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Debug Exception");
}

void _isr2_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Non Maskable Interrupt");
}

void _isr3_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Breakpoint Exception");
}

void _isr4_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Overflow Exception");
}

void _isr5_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "BOUND Range Exceeded Exception");
}

void _isr6_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Invalid Opcode Exception");
}

void _isr7_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Device Not Available Exception");
}

void _isr8_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Double Fault Exception");
}

void _isr9_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Coprocessor Segment Overrun");
}

void _isr10_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Invalid TSS Exception");
}

void _isr11_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Segment Not Present");
}

void _isr12_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Stack Fault Exception");
}

void _isr13_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "General Protection Exception");
}

void _isr14_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Page-Fault Exception");
}

void _isr15_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Reserved");
}

void _isr16_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "x87 FPU Floating-Point Error");
}

void _isr17_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Alignment Check Exception");
}

void _isr18_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "Machine-Check Exception");
}

void _isr19_c() {

	int nro_tarea = numero_tarea(obtener_indice_tarea_en_ejecucion());
	desalojar_tarea(nro_tarea, "SIMD Floating-Point Exception");
}
