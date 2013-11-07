/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "defines.h"
#include "utils.h"
#include "i386.h"

void mmu_inicializar_tarea(int nro_tarea);
void mmu_copiar_codigo_tarea(int nro_tarea);
void mmu_inicializar_dir_tarea(int nro_tarea);

/* directorio y tablas del kernel */

void mmu_inicializar_dir_kernel() {

	dword_t* kernel_page_directory = (dword_t*) ADDR_KERNEL_PAGE_DIREC;

	int i = 0;
	kernel_page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_1 + PAGE_DESC_ATTR_SUP_RW_P;
	kernel_page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_2 + PAGE_DESC_ATTR_SUP_RW_P;
	for (i = 2; i < PAGE_DIR_LENGTH; ++i) {
		kernel_page_directory[i] = 0;
	}
	
	//Tabla extra para Idle
	int dir_index = BITS(32, 22, ADDR_VIRTUAL_TASK_CODE);
	kernel_page_directory[dir_index] = ADDR_IDLE_PAGE_TABLE+3;

}

void mmu_inicializar_tablas_kernel() {

	dword_t* kernel_page_table_1 = (dword_t*) ADDR_KERNEL_PAGE_TABLE_1;
	dword_t* kernel_page_table_2 = (dword_t*) ADDR_KERNEL_PAGE_TABLE_2;
	dword_t* idle_page_table = (dword_t*) ADDR_IDLE_PAGE_TABLE;

	int i;
	for (i = 0; i < PAGE_TABLE_LENGTH; ++i) {
		kernel_page_table_1[i] = ((i << 12) + PAGE_DESC_ATTR_SUP_RW_P);
	}

	for (i = 0; i < ((PAGE_TABLE_LENGTH / 8) * 7); ++i) {
		kernel_page_table_2[i] = (((i+0x400) << 12) + PAGE_DESC_ATTR_SUP_RW_P);
	}
	
	for(i = 0; i < PAGE_TABLE_LENGTH; ++i) {
		idle_page_table[i] = 0;
	}
	
	mmu_mapear_pagina(ADDR_VIRTUAL_TASK_CODE,ADDR_KERNEL_PAGE_DIREC,ADDR_TASK_IDLE_CODE,0x3);
	mmu_mapear_pagina(ADDR_VIRTUAL_TASK_CODE + TAMANO_PAGINA,ADDR_KERNEL_PAGE_DIREC,ADDR_TASK_IDLE_CODE + TAMANO_PAGINA,0x3);
	mmu_mapear_pagina(TASK_ANCLA,ADDR_KERNEL_PAGE_DIREC,TASK_ANCLA_FIS,0x3);
	
}

/* directorios y tablas de las tareas */

void mmu_inicializar_tareas() {

	int i;
	for(i = 0; i < 8; i++) {
		mmu_inicializar_tarea(i);
	}
}

void mmu_inicializar_tarea(int nro_tarea) {

	mmu_copiar_codigo_tarea(nro_tarea);
	mmu_inicializar_dir_tarea(nro_tarea);
}

void mmu_copiar_codigo_tarea(int nro_tarea) {

	dword_t* src_tierra = (dword_t*) (TASK_1_CODE_SRC_ADDR + nro_tarea * TASK_SIZE);
	dword_t* dst_mar = (dword_t*) (TASK_1_CODE_ADDR + nro_tarea * TASK_SIZE);
	memcpy(dst_mar, src_tierra, TASK_SIZE);
}

void mmu_inicializar_dir_tarea(int nro_tarea) {
	
	dword_t* page_directory = (dword_t*) (TASK_1_PAGE_DIR + nro_tarea * TAMANO_PAGINA);
	dword_t* page_table = (dword_t*) (TASK_1_PAGE_TABLE + nro_tarea * TAMANO_PAGINA);

	int i = 0;
	page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_1 + PAGE_DESC_ATTR_SUP_RW_P;
	page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_2 + PAGE_DESC_ATTR_SUP_RW_P;
	for(i = 2; i < PAGE_DIR_LENGTH; i++) {
		page_directory[i] = 0;
	}

	int dir_index = BITS(32, 22, ADDR_VIRTUAL_TASK_CODE);
	page_directory[dir_index] = (dword_t) page_table + PAGE_DESC_ATTR_USR_RW_P;
	
	for(i = 0; i < PAGE_TABLE_LENGTH; i++) {
		page_table[i] = 0;
	}
	mmu_mapear_pagina(	ADDR_VIRTUAL_TASK_CODE, 						/* virtual */
						(unsigned int) page_directory, 					/* cr3 */
						TASK_1_CODE_ADDR + nro_tarea * TASK_SIZE, 		/* fisica */
						PAGE_DESC_ATTR_USR_RW_P);						/* attr */

	mmu_mapear_pagina(	ADDR_VIRTUAL_TASK_CODE + TAMANO_PAGINA, 
						(unsigned int) page_directory, 
						TASK_1_CODE_ADDR + nro_tarea * TASK_SIZE  + TAMANO_PAGINA, 
						PAGE_DESC_ATTR_USR_RW_P);

	mmu_mapear_pagina(	ADDR_VIRTUAL_TASK_CODE + 2 * TAMANO_PAGINA, 
						(unsigned int) page_directory, 
						0, 
						PAGE_DESC_ATTR_USR_RO_P);
}

/* mapear y unmapear paginas */

void mmu_mapear_pagina (unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attr) {
 	
 	int dir_index = BITS(32, 22, virtual);
	int table_index = BITS(22, 12, virtual);

	dword_t* page_directory = (dword_t*) (cr3 & ~0xFFF);
	dword_t* page_table = (dword_t*) (page_directory[dir_index] & ~0xFFF);
	
	page_table[table_index] = fisica + attr;
}

void mmu_unmapear_pagina (unsigned int virtual, unsigned int cr3) {
	
	mmu_mapear_pagina(virtual, cr3, 0x0, 0x0);
	
	tlbflush();
}

