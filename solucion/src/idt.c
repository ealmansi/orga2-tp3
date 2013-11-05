/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"
#include "gdt.h"

idt_entry idt[256] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

#define idt_entry_attr(p, dpl, s, d, tipo, ceros, reservado)               \
    (0b ## p ## dpl ## s ## d ## tipo ## ceros ## reservado)

#define IDT_ENTRY(numero)                                                                               \
    idt[numero].offset_0_15          = (word_t) BITS(16, 0, (dword_t) &_isr ## numero);                 \
    idt[numero].offset_16_31         = (word_t) BITS(32, 16, (dword_t) &_isr ## numero);                \
    idt[numero].segsel               = (word_t) GDT_IDX_CODIG_0 << 3;                                   \
    idt[numero].attr                 = (word_t) idt_entry_attr( 1,            /* p */                   \
                                                                00,           /* dpl */                 \
                                                                0,            /* s */                   \
                                                                1,            /* d */                   \
                                                                111,          /* tipo */                \
                                                                000,          /* ceros */               \
                                                                00000);       /* reservado */

void idt_inicializar() {
    IDT_ENTRY(0);
    IDT_ENTRY(1);
    IDT_ENTRY(2);
    IDT_ENTRY(3);
    IDT_ENTRY(4);
    IDT_ENTRY(5);
    IDT_ENTRY(6);
    IDT_ENTRY(7);
    IDT_ENTRY(8);
    IDT_ENTRY(9);
    IDT_ENTRY(10);
    IDT_ENTRY(11);
    IDT_ENTRY(12);
    IDT_ENTRY(13);
    IDT_ENTRY(14);
    IDT_ENTRY(15);
    IDT_ENTRY(16);
    IDT_ENTRY(17);
    IDT_ENTRY(18);
    IDT_ENTRY(19);
    IDT_ENTRY(32);
    IDT_ENTRY(33);
    IDT_ENTRY(0x50);
    IDT_ENTRY(0x66);
}
