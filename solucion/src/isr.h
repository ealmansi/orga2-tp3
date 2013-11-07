/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#ifndef __ISR_H__
#define __ISR_H__

void _isr0();
void _isr1();
void _isr2();
void _isr3();
void _isr4();
void _isr5();
void _isr6();
void _isr7();
void _isr8();
void _isr9();
void _isr10();
void _isr11();
void _isr12();
void _isr13();
void _isr14();
void _isr15();
void _isr16();
void _isr17();
void _isr18();
void _isr19();
void _isr32();
void _isr33();
void _isr0x50();
void _isr0x66();

void _isr0_c();
void _isr1_c();
void _isr2_c();
void _isr3_c();
void _isr4_c();
void _isr5_c();
void _isr6_c();
void _isr7_c();
void _isr8_c();
void _isr9_c();
void _isr10_c();
void _isr11_c();
void _isr12_c();
void _isr13_c();
void _isr14_c();
void _isr15_c();
void _isr16_c();
void _isr17_c();
void _isr18_c();
void _isr19_c();
int _isr32_c();
void _isr0x50_c(unsigned int type, unsigned int arg1, unsigned int arg2);
void _isr0x66_c();

#endif  /* !__ISR_H__ */
