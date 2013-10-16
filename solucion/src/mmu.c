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

void mmu_inicializar_dir_tarea() {
}
