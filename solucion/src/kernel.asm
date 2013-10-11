; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start


;; GDT
extern GDT_DESC

;; IDT
extern IDT_DESC
extern idt_inicializar

;; PIC
extern resetear_pic
extern habilitar_pic


;; Saltear seccion de datos
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
    cli

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    ; habilitar A20
    call habilitar_A20

    ; cargar la GDT
    lgdt [GDT_DESC]

    ; setear el bit PE del registro CR0
    mov eax, cr0
    or  eax, 1
    mov cr0, eax

    ; pasar a modo protegido
    jmp 0000000010010000b:mp        ; seteo cs = { index: 18 | gdt/ldt: 0 | rpl: 00 }_

BITS 32
mp:

    ; acomodar los segmentos
    xor eax, eax
    mov ax, 0000000010100000b       ; ds, gs, es = { index: 20 | gdt/ldt: 0 | rpl: 00 }
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov ax, 0000000010110000b       ; fs = { index: 22 | gdt/ldt: 0 | rpl: 00 }
    mov fs, ax

    ; setear la pila

    ; pintar pantalla, todos los colores, que bonito!

    ; inicializar el manejador de memoria

    ; inicializar el directorio de paginas

    ; inicializar memoria de tareas

    ; habilitar paginacion

    ; inicializar tarea idle

    ; inicializar todas las tsss

    ; inicializar entradas de la gdt de las tsss

    ; inicializar el scheduler

    ; inicializar la IDT

    ; configurar controlador de interrupciones

    ; cargar la tarea inicial

    ; saltar a la primer tarea

    ; Ciclar infinitamente (por si algo sale mal...)
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
