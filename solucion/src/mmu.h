/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/


#ifndef __MMU_H__
#define __MMU_H__

void mmu_inicializar_dir_kernel();
void mmu_inicializar_tablas_kernel();

void mmu_inicializar_tareas();

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned int attr);

#endif	/* !__MMU_H__ */
