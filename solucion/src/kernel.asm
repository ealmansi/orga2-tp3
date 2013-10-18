; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start

;;
;; Externas.
;; -------------------------------------------------------------------------- ;;

;; GDT
extern GDT_DESC

;; IDT
extern IDT_DESC
extern idt_inicializar

;; MMU
extern mmu_inicializar_dir_kernel
extern mmu_inicializar_tablas_kernel

;; PIC
extern resetear_pic
extern habilitar_pic

;; Funciones gráficas
extern plantillaEstado
extern imprimirNombreEquipo
extern inicializar_buffer_modo_estado
extern inicializar_buffer_modo_mapa
extern pintar_pantalla_modo_estado
extern pintar_pantalla_modo_mapa

;;
;; Macros.
;; -------------------------------------------------------------------------- ;;

%macro breakpoint 0
    xchg            bx, bx
%endmacro

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;

iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    CLI

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ; habilitar A20
    CALL habilitar_A20

    %include "habilitar_16colores.asm"

    %include "_kernel/00_cargar_la_GDT.asm"

    %include "_kernel/01_setear_el_bit_PE_del_registro_CR0.asm"
    
    %include "_kernel/02_pasar_a_modo_protegido.asm"

    %include "_kernel/03_acomodar_los_segmentos.asm"

    %include "_kernel/04_setear_la_pila.asm"

    %include "_kernel/05_pintar_pantalla.asm"

    %include "_kernel/06_inicializar_el_manejador_de_memoria.asm"

    %include "_kernel/07_inicializar_el_directorio_de_paginas.asm"

    %include "_kernel/08_inicializar_memoria_de_tareas.asm"

    %include "_kernel/09_habilitar_paginacion.asm"

    %include "_kernel/10_inicializar_tarea_idle.asm"

    %include "_kernel/11_inicializar_todas_las_tsss.asm"

    %include "_kernel/12_inicializar_entradas_de_la_gdt_de_las_tsss.asm"

    %include "_kernel/13_inicializar_el_scheduler.asm"

    %include "_kernel/14_inicializar_la_IDT.asm"

    %include "_kernel/15_configurar_controlador_de_interrupciones.asm"

    %include "_kernel/16_cargar_la_tarea_inicial.asm"

    %include "_kernel/17_saltar_a_la_primer_tarea.asm"

    ; Ciclar infinitamente (por si algo sale mal...)
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
