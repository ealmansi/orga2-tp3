/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#ifndef __GDT_H__
#define __GDT_H__

#include "tss.h"


#define GDT_IDX_CODIG_0                 18
#define GDT_IDX_CODIG_3                 19
#define GDT_IDX_DATOS_0                 20
#define GDT_IDX_DATOS_3                 21
#define GDT_IDX_VIDEO_0                 22
#define GDT_IDX_TASK_INICIAL            23
#define GDT_IDX_TASK_IDLE               24
#define GDT_IDX_TASK_OFFSET             25
#define GDT_IDX_TASK_BANDERA_OFFSET     (GDT_IDX_TASK_OFFSET + 8)
#define GDT_COUNT                       (GDT_IDX_TASK_BANDERA_OFFSET + 8)

typedef struct str_gdt_descriptor {
    unsigned short  gdt_length;
    unsigned int    gdt_addr;
} __attribute__((__packed__)) gdt_descriptor;

typedef struct str_gdt_entry {
    unsigned short  limit_0_15;
    unsigned short  base_0_15;
    unsigned char   base_23_16;
    unsigned char   type:4;
    unsigned char   s:1;
    unsigned char   dpl:2;
    unsigned char   p:1;
    unsigned char   limit_16_19:4;
    unsigned char   avl:1;
    unsigned char   l:1;
    unsigned char   db:1;
    unsigned char   g:1;
    unsigned char   base_31_24;
} __attribute__((__packed__, aligned (8))) gdt_entry;

/* Tabla GDT */
extern gdt_entry gdt[];
extern gdt_descriptor GDT_DESC;

word_t nueva_tss(tss* ptss);
void init_tss(tss* arreglo_tss);


#endif  /* !__GDT_H__ */
