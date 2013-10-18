/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#define inicioDirectorio  ((int*) 0x27000)
#define inicioTabla ((int*) 0x28000)


void mmu_inicializar() {
	int* pd= inicioDirectorio;
	int i;

	for(i = 1; i<1024;i++){
		pd[i] = 0;
		
		}
	*pd = 0x00028003;


	int* pt = inicioTabla;
	for(i = 0; i<1024;i++){
		pt[i] = (i<<12) + 3;

	}
}

void mmu_inicializar_dir_tarea(int nro_tarea) {

	int* dir_fisica = ((nro_tarea -1) * TASK_SIZE) + AREA_MAR_INICIO;
	int* dir_address = TASK_1_PAGE_DIR+ ((nro_tarea-1) <<12);
	int* table_address = TASK_1_PAGE_TABLE_1 + (((nro_tarea-1)*2) <<12);
	
	for (i=0; i< 1024 ;i++) {
		dir_address[i] = 0;
	}
	
	dir_address[0] = table_address;
	dir_address[1] = table_address + (1<<12);
	
	for (i=0; i<0x780 ; i++) {
		table_address[i] = (i<<12)+3;
	}
	for (i=0x780; i<2048 ; i++){
		table_address[i]=0;
	}
		
}

void mmu_mapear_pagina (unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attr){
	int dir_index = virtual
	
	
}


