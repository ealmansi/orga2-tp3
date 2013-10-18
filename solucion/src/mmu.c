/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "defines.h"

void mmu_inicializar_dir_kernel() {

	unsigned int* kernel_page_directory = (unsigned int*) ADDR_KERNEL_PAGE_DIREC;

	int i = 0;
	kernel_page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_1 + 3;
	kernel_page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_2 + 3;
	for (i = 2; i < 1024; ++i)
		kernel_page_directory[i] = 0;

}

void mmu_inicializar_tablas_kernel() {

	unsigned int* kernel_page_table_1 = (unsigned int*) ADDR_KERNEL_PAGE_TABLE_1;
	unsigned int* kernel_page_table_2 = (unsigned int*) ADDR_KERNEL_PAGE_TABLE_2;

	int i;
	for (i = 0; i < 1024; ++i)
		kernel_page_table_1[i] = ((i << 12) + 3);

	for (i = 0; i < 896; ++i)
		kernel_page_table_2[i] = ((i << 12) + 3);
}

// void mmu_inicializar_dir_tarea(int nro_tarea) {

// 	int* dir_fisica = ((nro_tarea -1) * TASK_SIZE) + AREA_MAR_INICIO;
// 	int* dir_address = TASK_1_PAGE_DIR+ ((nro_tarea-1) <<12);
// 	int* table_address = TASK_1_PAGE_TABLE_1 + (((nro_tarea-1)*2) <<12);
	
// 	for (i=0; i< 1024 ;i++) {
// 		dir_address[i] = 0;
// 	}
	
// 	dir_address[0] = table_address;
// 	dir_address[1] = table_address + (1<<12);
	
// 	for (i=0; i<0x780 ; i++) {
// 		table_address[i] = (i<<12)+3;
// 	}
// 	for (i=0x780; i<2048 ; i++){
// 		table_address[i]=0;
// 	}
		
// }

// void mmu_mapear_pagina (unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attr){
// 	int dir_index = virtual
	
	
// }


