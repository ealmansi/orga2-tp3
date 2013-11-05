/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

#define FLAT_SEG_BASE       0x00000000
#define FLAT_SEG_LIMIT      ((0x70000000 / 0x1000) - 1)

#define VIDEO_SEG_BASE          0xB8000
#define VIDEO_SEG_LIMIT         (VIDEO_SEG_BASE + 80*25*2 - 1)

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (word_t) 0,                                 /* limit[0:15]  */
        (word_t) 0,                                 /* base[0:15]   */
        (byte_t) 0,                                 /* base[23:16]  */
        (byte_t) 0,                                 /* type         */
        (byte_t) 0,                                 /* s            */
        (byte_t) 0,                                 /* dpl          */
        (byte_t) 0,                                 /* p            */
        (byte_t) 0,                                 /* limit[16:19] */
        (byte_t) 0,                                 /* avl          */
        (byte_t) 0,                                 /* l            */
        (byte_t) 0,                                 /* db           */
        (byte_t) 0,                                 /* g            */
        (byte_t) 0,                                 /* base[31:24]  */
    },
    [GDT_IDX_CODIG_0] = (gdt_entry) {
        (word_t) BITS(16, 0, FLAT_SEG_LIMIT),       /* limit[0:15]  */
        (word_t) BITS(16, 0, FLAT_SEG_BASE),        /* base[0:15]   */
        (byte_t) BITS(24, 16, FLAT_SEG_BASE),       /* base[23:16]  */
        (byte_t) 0b1010,                            /* type         */
        (byte_t) 0b1,                               /* s            */
        (byte_t) 0b00,                              /* dpl          */
        (byte_t) 0b1,                               /* p            */
        (byte_t) BITS(20, 16, FLAT_SEG_LIMIT),      /* limit[16:19] */
        (byte_t) 0b0,                               /* avl          */
        (byte_t) 0b0,                               /* l            */
        (byte_t) 0b1,                               /* db           */
        (byte_t) 0b1,                               /* g            */
        (byte_t) BITS(32, 24, FLAT_SEG_BASE),       /* base[31:24]  */
    },
    [GDT_IDX_CODIG_3] = (gdt_entry) {
        (word_t) BITS(16, 0, FLAT_SEG_LIMIT),       /* limit[0:15]  */
        (word_t) BITS(16, 0, FLAT_SEG_BASE),        /* base[0:15]   */
        (byte_t) BITS(24, 16, FLAT_SEG_BASE),       /* base[23:16]  */
        (byte_t) 0b1010,                            /* type         */
        (byte_t) 0b1,                               /* s            */
        (byte_t) 0b11,                              /* dpl          */
        (byte_t) 0b1,                               /* p            */
        (byte_t) BITS(20, 16, FLAT_SEG_LIMIT),      /* limit[16:19] */
        (byte_t) 0b0,                               /* avl          */
        (byte_t) 0b0,                               /* l            */
        (byte_t) 0b1,                               /* db           */
        (byte_t) 0b1,                               /* g            */
        (byte_t) BITS(32, 24, FLAT_SEG_BASE),       /* base[31:24]  */
    },
    [GDT_IDX_DATOS_0] = (gdt_entry) {
        (word_t) BITS(16, 0, FLAT_SEG_LIMIT),       /* limit[0:15]  */
        (word_t) BITS(16, 0, FLAT_SEG_BASE),        /* base[0:15]   */
        (byte_t) BITS(24, 16, FLAT_SEG_BASE),       /* base[23:16]  */
        (byte_t) 0b0010,                            /* type         */
        (byte_t) 0b1,                               /* s            */
        (byte_t) 0b00,                              /* dpl          */
        (byte_t) 0b1,                               /* p            */
        (byte_t) BITS(20, 16, FLAT_SEG_LIMIT),      /* limit[16:19] */
        (byte_t) 0b0,                               /* avl          */
        (byte_t) 0b0,                               /* l            */
        (byte_t) 0b1,                               /* db           */
        (byte_t) 0b1,                               /* g            */
        (byte_t) BITS(32, 24, FLAT_SEG_BASE),       /* base[31:24]  */
    },
    [GDT_IDX_DATOS_3] = (gdt_entry) {
        (word_t) BITS(16, 0, FLAT_SEG_LIMIT),       /* limit[0:15]  */
        (word_t) BITS(16, 0, FLAT_SEG_BASE),        /* base[0:15]   */
        (byte_t) BITS(24, 16, FLAT_SEG_BASE),       /* base[23:16]  */
        (byte_t) 0b0010,                            /* type         */
        (byte_t) 0b1,                               /* s            */
        (byte_t) 0b11,                              /* dpl          */
        (byte_t) 0b1,                               /* p            */
        (byte_t) BITS(20, 16, FLAT_SEG_LIMIT),      /* limit[16:19] */
        (byte_t) 0b0,                               /* avl          */
        (byte_t) 0b0,                               /* l            */
        (byte_t) 0b1,                               /* db           */
        (byte_t) 0b1,                               /* g            */
        (byte_t) BITS(32, 24, FLAT_SEG_BASE),       /* base[31:24]  */
    },
    [GDT_IDX_VIDEO_0] = (gdt_entry) {
        (word_t) BITS(16, 0, VIDEO_SEG_LIMIT),      /* limit[0:15]  */
        (word_t) BITS(16, 0, VIDEO_SEG_BASE),       /* base[0:15]   */
        (byte_t) BITS(24, 16, VIDEO_SEG_BASE),      /* base[23:16]  */
        (byte_t) 0b0010,                            /* type         */
        (byte_t) 0b1,                               /* s            */
        (byte_t) 0b00,                              /* dpl          */
        (byte_t) 0b1,                               /* p            */
        (byte_t) BITS(20, 16, VIDEO_SEG_LIMIT),     /* limit[16:19] */
        (byte_t) 0b0,                               /* avl          */
        (byte_t) 0b0,                               /* l            */
        (byte_t) 0b1,                               /* db           */
        (byte_t) 0b0,                               /* g            */
        (byte_t) BITS(32, 24, VIDEO_SEG_LIMIT),     /* base[31:24]  */
    },

};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};

word_t gdt_next_index = GDT_IDX_VIDEO_0;

gdt_entry* entrada_libre_gdt(){
	
	gdt_next_index++;
	return &(gdt[gdt_next_index]);
	
}

word_t nueva_tss(tss* ptss){
	
	gdt_entry* descriptor_tss = entrada_libre_gdt();

	descriptor_tss->limit_0_15 = 0x67;
	descriptor_tss->base_0_15 = (unsigned int) (ptss) & 0xFFFF;
	descriptor_tss->base_23_16 = ((unsigned int) (ptss) >> 16) & 0xFF;
	
	
	descriptor_tss->type = 0x09;


	
	descriptor_tss->s = 0x00;
	
	//~ if(ptss == &tarea_inicial || ptss == &tarea_idle) {
		descriptor_tss->dpl = 0x00;
	//~ } else {
		//~ descriptor_tss->dpl = 0x03;
	//~ }
	
	descriptor_tss->p = 0x01;
	descriptor_tss->limit_16_19 = 0x00;
	descriptor_tss->avl = 0x00;
	descriptor_tss->l = 0x00;
	descriptor_tss->db = 0x00;
	descriptor_tss->g = 0x00;
	descriptor_tss->base_31_24 = (unsigned int) (ptss) >> 24;
	
	return (gdt_next_index << 3);
}

    //~ [0x17] = (gdt_entry) {
        //~ (word_t) BITS(16, 0, 0x67), 			     /* limit[0:15]  */
        //~ (word_t) BITS(16, 0, (dword_t)&tarea_inicial),       /* base[0:15]   */
        //~ (byte_t) BITS(24, 16, (dword_t)&tarea_inicial),      /* base[23:16]  */
        //~ (byte_t) 0b1001,                            /* type         */
        //~ (byte_t) 0b0,                               /* s            */
        //~ (byte_t) 0b00,                              /* dpl          */
        //~ (byte_t) 0b1,                               /* p            */
        //~ (byte_t) BITS(20, 16, 0x67),			     /* limit[16:19] */
        //~ (byte_t) 0b0,                               /* avl          */
        //~ (byte_t) 0b0,                               /* l            */
        //~ (byte_t) 0b0,                               /* db           */
        //~ (byte_t) 0b0,                               /* g            */
        //~ (byte_t) BITS(32, 24, (dword_t)&tarea_inicial),     /* base[31:24]  */
    //~ },
//~ 
//~ 
