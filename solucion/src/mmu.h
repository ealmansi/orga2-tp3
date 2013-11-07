/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/


#ifndef __MMU_H__
#define __MMU_H__

#define PAGE_DESC_ATTR_SUP_RW_P 0b000000011
#define PAGE_DESC_ATTR_USR_RW_P 0b000000111
#define PAGE_DESC_ATTR_USR_RO_P 0b000000101

void mmu_inicializar_dir_kernel();
void mmu_inicializar_tablas_kernel();

void mmu_mapear_pagina (unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attr);
void mmu_unmapear_pagina (unsigned int virtual, unsigned int cr3);

void mmu_inicializar_tareas();

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attr);
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3);

#endif	/* !__MMU_H__ */
