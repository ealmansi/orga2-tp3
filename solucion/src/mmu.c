/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "defines.h"

typedef unsigned int ui;

void memcpy(void* src, void* dst, int size);

/* directorio y tablas del kernel */

void mmu_inicializar_dir_kernel() {

	ui* kernel_page_directory = (ui*) ADDR_KERNEL_PAGE_DIREC;

	int i = 0;
	kernel_page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_1 + 3;
	kernel_page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_2 + 3;
	for (i = 2; i < 1024; ++i) {
		kernel_page_directory[i] = 0;
	}

}

void mmu_inicializar_tablas_kernel() {

	ui* kernel_page_table_1 = (ui*) ADDR_KERNEL_PAGE_TABLE_1;
	ui* kernel_page_table_2 = (ui*) ADDR_KERNEL_PAGE_TABLE_2;

	int i;
	for (i = 0; i < 1024; ++i){
		kernel_page_table_1[i] = ((i << 12) + 3);
	}

	for (i = 0; i < 896; ++i){
		kernel_page_table_2[i] = ((i << 12) + 3);
	}
}

/* mapear y unmapear paginas */

void mmu_mapear_pagina (ui virtual, ui cr3, ui fisica, ui attr) {
 	
 	int dir_index = virtual >> 22;
	int table_index = ((virtual << 10) >> 22) ;

	ui* dir = (ui*) (cr3 & ~0xFFF);
	ui* table = (ui*) (dir[dir_index] & ~0xFFF);
	
	table[table_index] = fisica + attr; //Hacemos esto así porque interpretamos que física está alineada a 4kb.
}

void mmu_unmapear_pagina (ui virtual, ui cr3) {
	
	mmu_mapear_pagina(virtual, cr3, 0x0, 0x0);
}

/* directorios y tablas de las tareas */

void mmu_inicializar_dir_tarea(int nro_tarea);

void mmu_inicializar_tareas() {

	int i;
	for(i = 0; i < 8; i++) {
		mmu_inicializar_dir_tarea(i);
	}
}

void mmu_inicializar_dir_tarea(int nro_tarea) {

	ui* src_tierra = (ui*) (TASK_1_CODE_SRC_ADDR + nro_tarea * TAMANO_PAGINA);
	ui* dst_mar = (ui*) (TASK_1_CODE_ADDR + nro_tarea * TAMANO_PAGINA);
	memcpy(src_tierra, dst_mar, TASK_SIZE);
	
	ui* page_directory = (ui*) (TASK_1_PAGE_DIR + nro_tarea * TAMANO_PAGINA);
	ui* page_table = (ui*) (TASK_1_PAGE_TABLE + nro_tarea * TAMANO_PAGINA);

	int i = 0;
	page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_1 + 3;
	page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_2 + 3;
	for(; i < 1024; i++) {
		page_directory[i] = 0;
	}
	
	page_directory[0x40000000 >> 22] = (ui) page_table; //Este número es un giga shifteado para obtener el index de la page_directory
	
	for(i = 0; i < 1024; i++) {
		page_table[i] = 0;
	}
	
	mmu_mapear_pagina(0x1 << 30, (ui) page_directory, (ui) dst_mar, 7);
	mmu_mapear_pagina((0x1 << 30) + (0x1 << 12), (ui) page_directory, (ui) (dst_mar + (1 << 12)), 7);
}

/* auxiliares */

void memcpy(void* src, void* dst, int size) {
	
	char* src_char = (char*) src;
	char* dst_char = (char*) dst;

	int i;
	for(i = 0; i < size ; i++) {
		dst_char[i] = src_char[i];
	}
}
