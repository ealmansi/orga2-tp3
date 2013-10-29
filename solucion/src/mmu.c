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

void mmu_mapear_pagina (unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attr){
 	int dir_index = virtual >> 22;
	int table_index = ((virtual << 10)>>22) ;

	int* dir = ((int*) (cr3 & ~0xFFF));
	int* table = ((int*) (dir[dir_index] & ~0xFFF)) ;
	
	table[table_index] = fisica + attr; //Hacemos esto así porque interpretamos que física está alineada a 4kb.
	
}

void mmu_unmapear_pagina (unsigned int virtual, unsigned int cr3){
	mmu_mapear_pagina(virtual, cr3, 0x0, 0x0);
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

void memcpy (void* src, void* dst, int size){
	int i;
	char* src_char = (char*)(src);
	char* dst_char = (char*)(dst);
	for(i = 0; i<size ; i++){
		dst_char[i]=src_char[i];
	}
}

void mmu_inicializar_dir_tarea(int nro_tarea) {
	int* src = ((int*)TASK_1_CODE_SRC_ADDR) + nro_tarea*0x1000;
	int* mar_dir = ((int*)TASK_1_CODE_ADDR) + nro_tarea*0x1000;
	int size = 2<<12;
	unsigned int* page_directory = ((unsigned int*)TASK_1_PAGE_DIR) + nro_tarea*0x1000;
	unsigned int* page_table = ((unsigned int*) TASK_1_PAGE_TABLE) + nro_tarea*0x1000;
	int i;
	memcpy(src, mar_dir, size);
	
	i=0;
	page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_1 + 3;
	page_directory[i++] = ADDR_KERNEL_PAGE_TABLE_2 + 3;
	for(i=2; i<1024; i++){
		page_directory[i] = 0;
	}
	
	page_directory [0x40000000 >> 22] = (unsigned int)page_table; //Este número es un giga shifteado para obtener el index de la page_directory
	
	for(i=0; i<1024; i++){
		page_table[i] = 0;
	}
	
	mmu_mapear_pagina(0x1 << 30, (unsigned int) page_directory, (unsigned int) mar_dir, 7);
	mmu_mapear_pagina((0x1 << 30) + (0x1<<12), (unsigned int) page_directory, (unsigned int) (mar_dir + (1 << 12)), 7);

}
	



void mmu_inicializar_tareas(){
	int i;
	for(i = 0; i<8; i++){
		mmu_inicializar_dir_tarea(i);
	}
}
	
