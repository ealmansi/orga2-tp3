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

byte_t* primeras_paginas[CANT_TAREAS];
byte_t* segundas_paginas[CANT_TAREAS];

void inicializar_juego(){
	int i;
	for (i = 0; i < 8; i++) {
		primeras_paginas[i] = ((byte_t*) TASK_1_CODE_ADDR +( (2*i) << 12));
		segundas_paginas[i] = ((byte_t*) TASK_1_CODE_ADDR +( (2*i+1) << 12));
	}
}


unsigned int game_fondear(unsigned int ancla_dir_fisica) {
	
	if(ancla_dir_fisica <= AREA_TIERRA_FIN){
		mmu_unmapear_pagina(TASK_ANCLA, rcr3());
		mmu_mapear_pagina(TASK_ANCLA, rcr3(), ancla_dir_fisica, PAGE_DESC_ATTR_USR_RO_P);
		return TRUE;
	}
	
    return FALSE;
    
}

unsigned int game_canonear(unsigned int dir_misil_fisica, unsigned int dir_buffer_relativa) {
	if(AREA_MAR_INICIO <= dir_misil_fisica && dir_misil_fisica <= AREA_MAR_FIN){
		memcpy((void*)dir_misil_fisica,(void*) dir_buffer_relativa, min(97,AREA_MAR_FIN-dir_misil_fisica+1));
		return TRUE;
	}
	
    return FALSE;
}

unsigned int game_navegar(unsigned int dir_primera_pag_fisica, unsigned int dir_segunda_pag_fisica) {
	
	if(	AREA_MAR_INICIO <= dir_primera_pag_fisica &&
		dir_primera_pag_fisica <= AREA_MAR_FIN &&
		AREA_MAR_INICIO <= dir_segunda_pag_fisica &&
		dir_segunda_pag_fisica <= AREA_MAR_FIN		){


		int cr3 = rcr3();			
		int nro_navio = (cr3 - TASK_1_PAGE_DIR) >> 12;
		byte_t* dir_vieja_pagina_1 = primeras_paginas[ nro_navio ];
		byte_t* dir_vieja_pagina_2 = segundas_paginas[ nro_navio ];
		primeras_paginas[ nro_navio ] = (byte_t*) dir_primera_pag_fisica;
		segundas_paginas[ nro_navio ] = (byte_t*) dir_segunda_pag_fisica;

		
		memcpy((char*)dir_primera_pag_fisica,dir_vieja_pagina_1, 1<<12);
		memcpy((char*)dir_segunda_pag_fisica,dir_vieja_pagina_2, 1<<12);
		mmu_unmapear_pagina(ADDR_VIRTUAL_TASK_CODE, rcr3());
		mmu_unmapear_pagina(ADDR_VIRTUAL_TASK_AREA_BANDERA, rcr3());
		mmu_mapear_pagina(ADDR_VIRTUAL_TASK_CODE, cr3, dir_primera_pag_fisica, PAGE_DESC_ATTR_USR_RW_P);
		mmu_mapear_pagina(ADDR_VIRTUAL_TASK_AREA_BANDERA, cr3, dir_segunda_pag_fisica, PAGE_DESC_ATTR_USR_RW_P);
		return TRUE;
	}
	
    return FALSE;
}
