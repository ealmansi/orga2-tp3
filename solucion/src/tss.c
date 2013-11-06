/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "gdt.h"
#include "mmu.h"


#define GDT_SEL_CODIG_0 (GDT_IDX_CODIG_0 << 3)
#define GDT_SEL_CODIG_3 ((GDT_IDX_CODIG_3 << 3) + 3)
#define GDT_SEL_DATOS_0 (GDT_IDX_DATOS_0 << 3)
#define GDT_SEL_DATOS_3 ((GDT_IDX_DATOS_3 << 3) + 3)
#define GDT_SEL_VIDEO_0 (GDT_IDX_VIDEO_0 << 3)


tss tarea_inicial = {0};
tss tarea_idle = {0};
tss tss_navios[CANT_TAREAS] = {{0}};
tss tss_banderas[CANT_TAREAS] = {{0}};

void tss_inicializar_inicial();
void tss_inicializar_idle();
void tss_inicializar_navios();
void tss_inicializar_navio(unsigned int tarea);
void tss_inicializar_banderas();
void tss_inicializar_bandera(unsigned int tarea);

void tss_inicializar_entrada_gdt_tarea_inicial();
void tss_inicializar_entrada_gdt_tarea_idle();
void tss_inicializar_entrada_gdt_navio(unsigned int tarea);
void tss_inicializar_entrada_gdt_bandera(unsigned int tarea);

/* implementaciones */

void tss_inicializar() {
	
	tss_inicializar_inicial();
	tss_inicializar_idle();
	tss_inicializar_navios();
	tss_inicializar_banderas();
}

void tss_inicializar_inicial() {
	
	tarea_inicial.ptl		= 0;
	tarea_inicial.esp0		= 0;
	tarea_inicial.ss0		= 0;
	tarea_inicial.esp1		= 0;
	tarea_inicial.ss1		= 0;
	tarea_inicial.esp2		= 0;
	tarea_inicial.ss2		= 0;
	tarea_inicial.cr3		= 0;
	tarea_inicial.eip		= 0;
	tarea_inicial.eflags	= 0x202;
	tarea_inicial.eax		= 0;
	tarea_inicial.ecx		= 0;
	tarea_inicial.edx		= 0;
	tarea_inicial.ebx		= 0;
	tarea_inicial.esp		= 0;
	tarea_inicial.ebp		= 0;
	tarea_inicial.esi		= 0;
	tarea_inicial.edi		= 0;
	tarea_inicial.es		= 0;
	tarea_inicial.cs		= 0;
	tarea_inicial.ss		= 0;
	tarea_inicial.ds		= 0;
	tarea_inicial.fs		= 0;
	tarea_inicial.gs		= 0;
	tarea_inicial.ldt		= 0;
	tarea_inicial.dtrap		= 0;
	tarea_inicial.iomap		= 0;
}

void tss_inicializar_idle() {
	
	tarea_idle.ptl			= 0;
	tarea_idle.esp0			= ADDR_TASK_IDLE_STACK_PL_0;
	tarea_idle.ss0			= GDT_SEL_DATOS_0;
	tarea_idle.esp1			= 0;
	tarea_idle.ss1			= 0;
	tarea_idle.esp2			= 0;
	tarea_idle.ss2			= 0;
	tarea_idle.cr3			= ADDR_KERNEL_PAGE_DIREC;
	tarea_idle.eip			= ADDR_VIRTUAL_TASK_CODE;
	tarea_idle.eflags		= 0x202;
	tarea_idle.eax			= 0;
	tarea_idle.ecx			= 0;
	tarea_idle.edx			= 0;
	tarea_idle.ebx			= 0;
	tarea_idle.esp			= ADDR_VIRTUAL_TASK_PILA_TAREA;
	tarea_idle.ebp			= ADDR_VIRTUAL_TASK_PILA_TAREA;
	tarea_idle.esi			= 0;
	tarea_idle.edi			= 0;
	tarea_idle.es			= GDT_SEL_DATOS_0;
	tarea_idle.cs			= GDT_SEL_CODIG_0;
	tarea_idle.ss			= GDT_SEL_DATOS_0;
	tarea_idle.ds			= GDT_SEL_DATOS_0;
	tarea_idle.fs			= GDT_SEL_VIDEO_0;
	tarea_idle.gs			= GDT_SEL_DATOS_0;
	tarea_idle.ldt			= 0;
	tarea_idle.dtrap		= 0;
	tarea_idle.iomap		= 0xFFFF;
}

void tss_inicializar_navios(){
	
	unsigned int i ;
	
	for(i = 0; i < CANT_TAREAS; i++) {
		
		tss_inicializar_navio(i);
	}
}

void tss_inicializar_navio(unsigned int tarea) {
	
	tss_navios[tarea].ptl		= 0;
	tss_navios[tarea].esp0		= ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea;
	tss_navios[tarea].ss0		= GDT_SEL_DATOS_0; 
	tss_navios[tarea].esp1		= 0;
	tss_navios[tarea].ss1		= 0;
	tss_navios[tarea].esp2		= 0;
	tss_navios[tarea].ss2		= 0;
	tss_navios[tarea].cr3		= ADDR_TASK_1_PAGE_DIREC + TAMANO_PAGINA * tarea;
	tss_navios[tarea].eip		= ADDR_VIRTUAL_TASK_CODE;
	tss_navios[tarea].eflags	= 0x202;
	tss_navios[tarea].eax		= 0;
	tss_navios[tarea].ecx		= 0;
	tss_navios[tarea].edx		= 0;
	tss_navios[tarea].ebx		= 0;
	tss_navios[tarea].esp		= ADDR_VIRTUAL_TASK_PILA_TAREA;
	tss_navios[tarea].ebp		= ADDR_VIRTUAL_TASK_PILA_TAREA;
	tss_navios[tarea].esi		= 0;
	tss_navios[tarea].edi		= 0;
	tss_navios[tarea].es		= GDT_SEL_DATOS_3;
	tss_navios[tarea].cs		= GDT_SEL_CODIG_3;
	tss_navios[tarea].ss		= GDT_SEL_DATOS_3;
	tss_navios[tarea].ds		= GDT_SEL_DATOS_3;
	tss_navios[tarea].fs		= GDT_SEL_DATOS_3;
	tss_navios[tarea].gs		= GDT_SEL_DATOS_3;
	tss_navios[tarea].ldt		= 0;
	tss_navios[tarea].dtrap		= 0;
	tss_navios[tarea].iomap		= 0xFFFF;
}

void tss_inicializar_banderas() {
	
	unsigned int i;
	
	for(i = 0; i < CANT_TAREAS; i++) {

		tss_inicializar_bandera(i);
	}
}

void tss_inicializar_bandera(unsigned int tarea) {
	
	tss_banderas[tarea].ptl			= 0;
	tss_banderas[tarea].esp0		= ADDR_TASK_1_STACK_PL_0 + TAMANO_PAGINA * tarea - 0x800 /*mitad de pagina para la pila de la bandera*/;
	tss_banderas[tarea].ss0			= GDT_SEL_DATOS_0;
	tss_banderas[tarea].esp1		= 0;
	tss_banderas[tarea].ss1			= 0;
	tss_banderas[tarea].esp2		= 0;
	tss_banderas[tarea].ss2			= 0;
	tss_banderas[tarea].cr3			= ADDR_TASK_1_PAGE_DIREC + TAMANO_PAGINA * tarea;
	tss_banderas[tarea].eip			= ADDR_VIRTUAL_TASK_CODE;
	tss_banderas[tarea].eflags		= 0x202;
	tss_banderas[tarea].eax			= 0;
	tss_banderas[tarea].ecx			= 0;
	tss_banderas[tarea].edx			= 0;
	tss_banderas[tarea].ebx			= 0;
	tss_banderas[tarea].esp			= ADDR_VIRTUAL_TASK_PILA_BANDERA;
	tss_banderas[tarea].ebp			= ADDR_VIRTUAL_TASK_PILA_BANDERA;
	tss_banderas[tarea].esi			= 0;
	tss_banderas[tarea].edi			= 0;
	tss_banderas[tarea].es			= GDT_SEL_DATOS_3;
	tss_banderas[tarea].cs			= GDT_SEL_CODIG_3;
	tss_banderas[tarea].ss			= GDT_SEL_DATOS_3;
	tss_banderas[tarea].ds			= GDT_SEL_DATOS_3;
	tss_banderas[tarea].fs			= GDT_SEL_VIDEO_0;
	tss_banderas[tarea].gs			= GDT_SEL_DATOS_3;
	tss_banderas[tarea].ldt			= 0;
	tss_banderas[tarea].dtrap		= 0;
	tss_banderas[tarea].iomap		= 0xFFFF;
}

void tss_inicializar_entradas_gdt() {

	tss_inicializar_entrada_gdt_tarea_inicial();
	tss_inicializar_entrada_gdt_tarea_idle();

	unsigned int i;
	for (i = 0; i < CANT_TAREAS; ++i) {
		tss_inicializar_entrada_gdt_navio(i);
	}
	for (i = 0; i < CANT_TAREAS; ++i) {
		tss_inicializar_entrada_gdt_bandera(i);
	}
}

void tss_inicializar_entrada_gdt_tarea_inicial() {

	gdt[GDT_IDX_TASK_INICIAL] = (gdt_entry) {
        (word_t) 0x67,                                 		/* limit[0:15]  */
        (word_t) BITS(16, 0, (dword_t) &tarea_inicial),		/* base[0:15]   */
        (byte_t) BITS(24, 16, (dword_t) &tarea_inicial),	/* base[23:16]  */
        (byte_t) 0x09,                                 		/* type         */
        (byte_t) 0,											/* s            */
        (byte_t) 0,											/* dpl          */
        (byte_t) 0x01,                                 		/* p            */
        (byte_t) 0x00,                                 		/* limit[16:19] */
        (byte_t) 0x00,                                 		/* avl          */
        (byte_t) 0x00,                                 		/* l            */
        (byte_t) 0x00,                                 		/* db           */
        (byte_t) 0x00,                                 		/* g            */
        (byte_t) BITS(32, 24, (dword_t) &tarea_inicial),	/* base[31:24]  */
    };
}

void tss_inicializar_entrada_gdt_tarea_idle() {

	gdt[GDT_IDX_TASK_IDLE] = (gdt_entry) {
        (word_t) 0x67,                                 		/* limit[0:15]  */
        (word_t) BITS(16, 0, (dword_t) &tarea_idle),		/* base[0:15]   */
        (byte_t) BITS(24, 16, (dword_t) &tarea_idle),		/* base[23:16]  */
        (byte_t) 0x09,                                 		/* type         */
        (byte_t) 0,											/* s            */
        (byte_t) 0,											/* dpl          */
        (byte_t) 0x01,                                 		/* p            */
        (byte_t) 0x00,                                 		/* limit[16:19] */
        (byte_t) 0x00,                                 		/* avl          */
        (byte_t) 0x00,                                 		/* l            */
        (byte_t) 0x00,                                 		/* db           */
        (byte_t) 0x00,                                 		/* g            */
        (byte_t) BITS(32, 24, (dword_t) &tarea_idle),		/* base[31:24]  */
    };
}

void tss_inicializar_entrada_gdt_navio(unsigned int nro_tarea) {

	gdt[GDT_IDX_TASK_OFFSET + nro_tarea] = (gdt_entry) {
        (word_t) 0x67,                                 				/* limit[0:15]  */
        (word_t) BITS(16, 0, (dword_t) &(tss_navios[nro_tarea])),	/* base[0:15]   */
        (byte_t) BITS(24, 16, (dword_t) &(tss_navios[nro_tarea])),	/* base[23:16]  */
        (byte_t) 0x09,                                 				/* type         */
        (byte_t) 0,													/* s            */
        (byte_t) 0x3,												/* dpl          */
        (byte_t) 0x01,                                 				/* p            */
        (byte_t) 0x00,                                 				/* limit[16:19] */
        (byte_t) 0x00,                                 				/* avl          */
        (byte_t) 0x00,                                 				/* l            */
        (byte_t) 0x00,                                 				/* db           */
        (byte_t) 0x00,                                 				/* g            */
        (byte_t) BITS(32, 24, (dword_t) &(tss_navios[nro_tarea])),	/* base[31:24]  */
    };
}

void tss_inicializar_entrada_gdt_bandera(unsigned int nro_tarea) {

	gdt[GDT_IDX_TASK_BANDERA_OFFSET + nro_tarea] = (gdt_entry) {
        (word_t) 0x67,                                 					/* limit[0:15]  */
        (word_t) BITS(16, 0, (dword_t) &(tss_banderas[nro_tarea])),		/* base[0:15]   */
        (byte_t) BITS(24, 16, (dword_t) &(tss_banderas[nro_tarea])),	/* base[23:16]  */
        (byte_t) 0x09,                                 					/* type         */
        (byte_t) 0,														/* s            */
        (byte_t) 0x3,													/* dpl          */
        (byte_t) 0x01,                                 					/* p            */
        (byte_t) 0x00,                                 					/* limit[16:19] */
        (byte_t) 0x00,                                 					/* avl          */
        (byte_t) 0x00,                                 					/* l            */
        (byte_t) 0x00,                                 					/* db           */
        (byte_t) 0x00,                                 					/* g            */
        (byte_t) BITS(32, 24, (dword_t) &(tss_banderas[nro_tarea])),	/* base[31:24]  */
    };
}
