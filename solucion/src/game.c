/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "i386.h"
#include "mmu.h"
#include "utils.h"

unsigned int game_fondear(unsigned int ancla_dir_fisica) {
	
	if(ancla_dir_fisica < AREA_TIERRA_FIN){
		mmu_mapear_pagina(TASK_ANCLA,rcr3(),ancla_dir_fisica,0b000000101);
		return TRUE;
	}
	
    return FALSE;
    
}

unsigned int game_canonear(unsigned int dir_misil_fisica, unsigned int dir_buffer_relativa) {
	
	if(AREA_MAR_INICIO < dir_misil_fisica && dir_misil_fisica < AREA_MAR_FIN){
		memcpy((void*)dir_misil_fisica,(void*) dir_buffer_relativa, 97);
		return TRUE;
	}
	
    return FALSE;
}

unsigned int game_navegar(unsigned int dir_primera_pag_fisica, unsigned int dir_segunda_pag_fisica) {
	
	if(	AREA_MAR_INICIO < dir_primera_pag_fisica &&
		dir_primera_pag_fisica < AREA_MAR_FIN &&
		AREA_MAR_INICIO < dir_segunda_pag_fisica &&
		dir_segunda_pag_fisica < AREA_MAR_FIN		){
			
		mmu_unmapear_pagina(ADDR_VIRTUAL_TASK_CODE,rcr3());
		mmu_unmapear_pagina(ADDR_VIRTUAL_TASK_AREA_BANDERA,rcr3());
		mmu_mapear_pagina(ADDR_VIRTUAL_TASK_CODE,rcr3(),dir_primera_pag_fisica,0b000000111);
		mmu_mapear_pagina(ADDR_VIRTUAL_TASK_AREA_BANDERA,rcr3(),dir_segunda_pag_fisica,0b000000111);
		
		return TRUE;
	}
	
    return FALSE;
}
