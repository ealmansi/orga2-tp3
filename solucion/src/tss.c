/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "mmu.h"

tss tarea_inicial;
tss tarea_idle;

tss tss_navios[CANT_TAREAS];
tss tss_banderas[CANT_TAREAS];

void tss_inicializar_navio(unsigned int tarea){
	
	tss_navios[tarea].ptl = 0;
	tss_navios[tarea].unused0 = 0;
	tss_navios[tarea].esp0 = ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea;
	tss_navios[tarea].ss0 = 21;
	tss_navios[tarea].unused1 = 0;
	tss_navios[tarea].esp1 = 0;
	tss_navios[tarea].ss1 = 0;
	tss_navios[tarea].unused2 = 0;
	tss_navios[tarea].esp2 = 0;
	tss_navios[tarea].ss2 = 0;
	tss_navios[tarea].unused3 = 0;
	tss_navios[tarea].cr3 = ADDR_TASK_1_PAGE_DIREC + TAMANO_PAGINA * tarea;
	tss_navios[tarea].eip = ADDR_VIRTUAL_TASK_CODE;
	tss_navios[tarea].eflags = 0x202;
	tss_navios[tarea].eax = 0;
	tss_navios[tarea].ecx = 0;
	tss_navios[tarea].edx = 0;
	tss_navios[tarea].ebx = 0;
	tss_navios[tarea].esp = ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea;
	tss_navios[tarea].ebp = ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea;
	tss_navios[tarea].esi = 0;
	tss_navios[tarea].edi = 0;
	tss_navios[tarea].es = 21;
	tss_navios[tarea].unused4 = 0;
	tss_navios[tarea].cs = 19;
	tss_navios[tarea].unused5 = 0;
	tss_navios[tarea].ss = 21;
	tss_navios[tarea].unused6 = 0;
	tss_navios[tarea].ds = 21;
	tss_navios[tarea].unused7 = 0;
	tss_navios[tarea].fs = 22;
	tss_navios[tarea].unused8 = 0;
	tss_navios[tarea].gs = 21;
	tss_navios[tarea].unused9 = 0;
	tss_navios[tarea].ldt = 0;
	tss_navios[tarea].unused10 = 0;
	tss_navios[tarea].dtrap = 0;
	tss_navios[tarea].iomap = 0xFFFF;
	
}

tss* tss_inicializar_navios(){
	
	unsigned int i ;
	
	for(i = 0; i < CANT_TAREAS; i++){
		
		tss_inicializar_navio(i);
		
	}
	
	return tss_navios;
	
}

void tss_inicializar_bandera(unsigned int tarea){
	
	tss_banderas[tarea].ptl = 0;
	tss_banderas[tarea].unused0 = 0;
	tss_banderas[tarea].esp0 = ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea;
	tss_banderas[tarea].ss0 = 21;
	tss_banderas[tarea].unused1 = 0;
	tss_banderas[tarea].esp1 = 0;
	tss_banderas[tarea].ss1 = 0;
	tss_banderas[tarea].unused2 = 0;
	tss_banderas[tarea].esp2 = 0;
	tss_banderas[tarea].ss2 = 0;
	tss_banderas[tarea].unused3 = 0;
	tss_banderas[tarea].cr3 = ADDR_TASK_1_PAGE_DIREC + TAMANO_PAGINA * tarea;
	tss_banderas[tarea].eip = ADDR_VIRTUAL_TASK_CODE;
	tss_banderas[tarea].eflags = 0x202;
	tss_banderas[tarea].eax = 0;
	tss_banderas[tarea].ecx = 0;
	tss_banderas[tarea].edx = 0;
	tss_banderas[tarea].ebx = 0;
	tss_banderas[tarea].esp = ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea;
	tss_banderas[tarea].ebp = ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea;
	tss_banderas[tarea].esi = 0;
	tss_banderas[tarea].edi = 0;
	tss_banderas[tarea].es = 21;
	tss_banderas[tarea].unused4 = 0;
	tss_banderas[tarea].cs = 19;
	tss_banderas[tarea].unused5 = 0;
	tss_banderas[tarea].ss = 21;
	tss_banderas[tarea].unused6 = 0;
	tss_banderas[tarea].ds = 21;
	tss_banderas[tarea].unused7 = 0;
	tss_banderas[tarea].fs = 22;
	tss_banderas[tarea].unused8 = 0;
	tss_banderas[tarea].gs = 21;
	tss_banderas[tarea].unused9 = 0;
	tss_banderas[tarea].ldt = 0;
	tss_banderas[tarea].unused10 = 0;
	tss_banderas[tarea].dtrap = 0;
	tss_banderas[tarea].iomap = 0xFFFF;
	
}

tss* tss_inicializar_banderas(){
	
	unsigned int i ;
	
	for(i = 0; i < CANT_TAREAS; i++){
		
		tss_inicializar_bandera(i);
		
	}
	
	return tss_banderas;
	
}

tss* tss_inicializar_idle(){
	
	tarea_idle.ptl = 0;
	tarea_idle.unused0 = 0;
	tarea_idle.esp0 = ADDR_TASK_IDLE_STACK_PL_0;
	tarea_idle.ss0 = 20<<3;
	tarea_idle.unused1 = 0;
	tarea_idle.esp1 = 0;
	tarea_idle.ss1 = 0;
	tarea_idle.unused2 = 0;
	tarea_idle.esp2 = 0;
	tarea_idle.ss2 = 0;
	tarea_idle.unused3 = 0;
	tarea_idle.cr3 = ADDR_KERNEL_PAGE_DIREC;
	tarea_idle.eip = ADDR_VIRTUAL_TASK_CODE;
	tarea_idle.eflags = 0x202;
	tarea_idle.eax = 0;
	tarea_idle.ecx = 0;
	tarea_idle.edx = 0;
	tarea_idle.ebx = 0;
	tarea_idle.esp = ADDR_TASK_IDLE_STACK_PL_0;
	tarea_idle.ebp = ADDR_TASK_IDLE_STACK_PL_0;
	tarea_idle.esi = 0;
	tarea_idle.edi = 0;
	tarea_idle.es = 20<<3;
	tarea_idle.unused4 = 0;
	tarea_idle.cs = 18<<3;
	tarea_idle.unused5 = 0;
	tarea_idle.ss = 20<<3;
	tarea_idle.unused6 = 0;
	tarea_idle.ds = 20<<3;
	tarea_idle.unused7 = 0;
	tarea_idle.fs = 22<<3;
	tarea_idle.unused8 = 0;
	tarea_idle.gs = 20<<3;
	tarea_idle.unused9 = 0;
	tarea_idle.ldt = 0;
	tarea_idle.unused10 = 0;
	tarea_idle.dtrap = 0;
	tarea_idle.iomap = 0xFFFF;
	
	return &tarea_idle;
	
}

tss* tss_inicializar_inicial(){
	
	tarea_inicial.ptl = 0;
	tarea_inicial.unused0 = 0;
	tarea_inicial.esp0 = 0;
	tarea_inicial.ss0 = 0;
	tarea_inicial.unused1 = 0;
	tarea_inicial.esp1 = 0;
	tarea_inicial.ss1 = 0;
	tarea_inicial.unused2 = 0;
	tarea_inicial.esp2 = 0;
	tarea_inicial.ss2 = 0;
	tarea_inicial.unused3 = 0;
	tarea_inicial.cr3 = 0;
	tarea_inicial.eip = 0;
	tarea_inicial.eflags = 0x202;
	tarea_inicial.eax = 0;
	tarea_inicial.ecx = 0;
	tarea_inicial.edx = 0;
	tarea_inicial.ebx = 0;
	tarea_inicial.esp = 0;
	tarea_inicial.ebp = 0;
	tarea_inicial.esi = 0;
	tarea_inicial.edi = 0;
	tarea_inicial.es = 0;
	tarea_inicial.unused4 = 0;
	tarea_inicial.cs = 0;
	tarea_inicial.unused5 = 0;
	tarea_inicial.ss = 0;
	tarea_inicial.unused6 = 0;
	tarea_inicial.ds = 0;
	tarea_inicial.unused7 = 0;
	tarea_inicial.fs = 0;
	tarea_inicial.unused8 = 0;
	tarea_inicial.gs = 0;
	tarea_inicial.unused9 = 0;
	tarea_inicial.ldt = 0;
	tarea_inicial.unused10 = 0;
	tarea_inicial.dtrap = 0;
	tarea_inicial.iomap = 0;
	
	return &tarea_inicial;
	
}

void tss_inicializar() {
	
	//TODO
	
}

