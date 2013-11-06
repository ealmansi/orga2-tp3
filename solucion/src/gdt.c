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
