/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

#define ___word(v) (unsigned short) 0x ## v
#define ___byte(v) (unsigned char)  0x ## v
#define ___nibb(v) (unsigned char)  0x ## v
#define ___bits(v) (unsigned char)  0b ## v

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        ___word(0000),                        /* limit[0:15]  */
        ___word(0000),                        /* base[0:15]   */
        ___byte(00),                          /* base[23:16]  */
        ___bits(0000),                        /* type         */
        ___bits(0),                           /* s            */
        ___bits(00),                          /* dpl          */
        ___bits(0),                           /* p            */
        ___nibb(0),                           /* limit[16:19] */
        ___bits(0),                           /* avl          */
        ___bits(0),                           /* l            */
        ___bits(0),                           /* db           */
        ___bits(0),                           /* g            */
        ___byte(00),                          /* base[31:24]  */
    },
    [GDT_IDX_CODIG_0] = (gdt_entry) {
        ___word(FFFF),                         /* limit[0:15]  */
        ___word(0000),                         /* base[0:15]   */
        ___byte(00),                           /* base[23:16]  */
        ___bits(1010),                         /* type         */
        ___bits(1),                            /* s            */
        ___bits(00),                           /* dpl          */
        ___bits(1),                            /* p            */
        ___nibb(6),                            /* limit[16:19] */
        ___bits(0),                            /* avl          */
        ___bits(0),                            /* l            */
        ___bits(1),                            /* db           */
        ___bits(1),                            /* g            */
        ___byte(00),                           /* base[31:24]  */
    },
    [GDT_IDX_CODIG_3] = (gdt_entry) {
        ___word(FFFF),                         /* limit[0:15]  */
        ___word(0000),                         /* base[0:15]   */
        ___byte(00),                           /* base[23:16]  */
        ___bits(1010),                         /* type         */
        ___bits(1),                            /* s            */
        ___bits(11),                           /* dpl          */
        ___bits(1),                            /* p            */
        ___nibb(6),                            /* limit[16:19] */
        ___bits(0),                            /* avl          */
        ___bits(0),                            /* l            */
        ___bits(1),                            /* db           */
        ___bits(1),                            /* g            */
        ___byte(00),                           /* base[31:24]  */
    },
    [GDT_IDX_DATOS_0] = (gdt_entry) {
        ___word(FFFF),                         /* limit[0:15]  */
        ___word(0000),                         /* base[0:15]   */
        ___byte(00),                           /* base[23:16]  */
        ___bits(0010),                         /* type         */
        ___bits(1),                            /* s            */
        ___bits(00),                           /* dpl          */
        ___bits(1),                            /* p            */
        ___nibb(6),                            /* limit[16:19] */
        ___bits(0),                            /* avl          */
        ___bits(0),                            /* l            */
        ___bits(1),                            /* db           */
        ___bits(1),                            /* g            */
        ___byte(00),                           /* base[31:24]  */
    },
    [GDT_IDX_DATOS_3] = (gdt_entry) {
        ___word(FFFF),                         /* limit[0:15]  */
        ___word(0000),                         /* base[0:15]   */
        ___byte(00),                           /* base[23:16]  */
        ___bits(0010),                         /* type         */
        ___bits(1),                            /* s            */
        ___bits(11),                           /* dpl          */
        ___bits(1),                            /* p            */
        ___nibb(6),                            /* limit[16:19] */
        ___bits(0),                            /* avl          */
        ___bits(0),                            /* l            */
        ___bits(1),                            /* db           */
        ___bits(1),                            /* g            */
        ___byte(00),                           /* base[31:24]  */
    },
    [GDT_IDX_VIDEO_0] = (gdt_entry) {
        ___word(0FBF),                         /* limit[0:15]  */
        ___word(8000),                         /* base[0:15]   */
        ___byte(0B),                           /* base[23:16]  */
        ___bits(0010),                         /* type         */
        ___bits(1),                            /* s            */
        ___bits(00),                           /* dpl          */
        ___bits(1),                            /* p            */
        ___nibb(0),                            /* limit[16:19] */
        ___bits(0),                            /* avl          */
        ___bits(0),                            /* l            */
        ___bits(1),                            /* db           */
        ___bits(0),                            /* g            */
        ___byte(00),                           /* base[31:24]  */
    },
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};

#undef ___word
#undef ___byte
#undef ___nibb
#undef ___bits
