/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "i386.h"
#include "mmu.h"
#include "utils.h"
#include "defines.h"

unsigned int game_canonear(unsigned int dir_misil_fisica, unsigned int dir_buffer_relativa) {
	
	if(AREA_MAR_INICIO <= dir_misil_fisica &&
		dir_misil_fisica <= AREA_MAR_FIN) {

		memcpy((void*)dir_misil_fisica,(void*) dir_buffer_relativa, min(97,AREA_MAR_FIN-dir_misil_fisica+1));
		return TRUE;
	}
	
    return FALSE;
}

unsigned int game_navegar(unsigned int dir_primera_pag_fisica, unsigned int dir_segunda_pag_fisica,
	unsigned int dir_ult_p1, unsigned int dir_ult_p2) {
	
	if(	AREA_MAR_INICIO <= dir_primera_pag_fisica &&
		dir_primera_pag_fisica <= AREA_MAR_FIN &&
		AREA_MAR_INICIO <= dir_segunda_pag_fisica &&
		dir_segunda_pag_fisica <= AREA_MAR_FIN		){

		memcpy((char*) dir_primera_pag_fisica, (char*) dir_ult_p1, TAMANO_PAGINA);
		memcpy((char*) dir_segunda_pag_fisica, (char*) dir_ult_p2, TAMANO_PAGINA);

		
		int cr3 = rcr3();
		mmu_unmapear_pagina(ADDR_VIRTUAL_TASK_CODE, cr3);
		mmu_unmapear_pagina(ADDR_VIRTUAL_TASK_AREA_BANDERA, cr3);
		mmu_mapear_pagina(ADDR_VIRTUAL_TASK_CODE, cr3, dir_primera_pag_fisica, PAGE_DESC_ATTR_USR_RW_P);
		mmu_mapear_pagina(ADDR_VIRTUAL_TASK_AREA_BANDERA, cr3, dir_segunda_pag_fisica, PAGE_DESC_ATTR_USR_RW_P);
		return TRUE;
	}
	
    return FALSE;
}

unsigned int game_fondear(unsigned int ancla_dir_fisica) {
	
	if(ancla_dir_fisica <= AREA_TIERRA_FIN) {

		int cr3 = rcr3();
		mmu_unmapear_pagina(TASK_ANCLA, cr3);
		mmu_mapear_pagina(TASK_ANCLA, cr3, ancla_dir_fisica, PAGE_DESC_ATTR_USR_RO_P);

		return TRUE;
	}
	
    return FALSE;
}
