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

tss* tss_inicializar_navios(){
	
	//TODO
	return tss_navios;
	
}

tss* tss_inicializar_banderas(){
	
	//TODO
	return tss_banderas;
	
}

tss* tss_inicializar_idle(){
	
	tarea_idle.ptl = 0;
	tarea_idle.unused0 = 0;
	tarea_idle.esp0 = ADDR_TASK_IDLE_STACK_PL_0;
	tarea_idle.ss0 = 0;
	tarea_idle.unused1 = 0;
	tarea_idle.esp1 = 0;
	tarea_idle.ss1 = 0;
	tarea_idle.unused2 = 0;
	tarea_idle.esp2 = 0;
	tarea_idle.ss2 = 0;
	tarea_idle.unused3 = 0;
	tarea_idle.cr3 = ADDR_KERNEL_PAGE_DIREC;
	tarea_idle.eip = ADDR_TASK_IDLE_CODE;
	tarea_idle.eflags = 0x202;
	tarea_idle.eax = 0;
	tarea_idle.ecx = 0;
	tarea_idle.edx = 0;
	tarea_idle.ebx = 0;
	tarea_idle.esp = ADDR_TASK_IDLE_STACK_PL_0;
	tarea_idle.ebp = ADDR_TASK_IDLE_STACK_PL_0;
	tarea_idle.esi = 0;
	tarea_idle.edi = 0;
	tarea_idle.es = 20;
	tarea_idle.unused4 = 0;
	tarea_idle.cs = 18;
	tarea_idle.unused5 = 0;
	tarea_idle.ss = 20;
	tarea_idle.unused6 = 0;
	tarea_idle.ds = 20;
	tarea_idle.unused7 = 0;
	tarea_idle.fs = 22;
	tarea_idle.unused8 = 0;
	tarea_idle.gs = 20;
	tarea_idle.unused9 = 0;
	tarea_idle.ldt = 0;
	tarea_idle.unused10 = 0;
	tarea_idle.dtrap = 0;
	tarea_idle.iomap = 0xFFFF;
	
	mmu_mapear_pagina(ADDR_VIRTUAL_TASK_CODE,ADDR_KERNEL_PAGE_DIREC,ADDR_TASK_IDLE_CODE,0x3);
	mmu_mapear_pagina(ADDR_VIRTUAL_TASK_CODE + TAMANO_PAGINA,ADDR_KERNEL_PAGE_DIREC,ADDR_TASK_IDLE_CODE + TAMANO_PAGINA,0x3);
	mmu_mapear_pagina(TASK_ANCLA,ADDR_KERNEL_PAGE_DIREC,TASK_ANCLA_FIS,0x3);
	
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

