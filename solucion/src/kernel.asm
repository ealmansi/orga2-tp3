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


;;;;;;;;; Setear primera fila en letras blancas y fondo negro:

	MOV ecx, 80 ; Cada fila tiene 80 caracteres. Con esto puedo hacer loop.
	XOR edx, edx; Contador de posición.

__setear_primera_fila:
		MOV byte [fs:edx+1], 00001111b
		ADD edx, 2;
		loop __setear_primera_fila

;;;;;;;;; Setear última fila en letras blancas y fondo negro:

	MOV ecx, 80;
	MOV edx, 80*2*24; 80 caracteres, cada uno formado por 2 bytes, deseo saltearme las primeras 24 filas para arrancar por la ultima.

__setar_ultima_fila:
		MOV byte [fs:edx+1], 00001111b
		ADD edx, 2;
		loop __setear_primera_fila


    ; setear la pila

	MOV ebp, 0x27000; TODO TODO. Esto parece setear la pila en esa posición... sin embargo a mi me parece que esto debería ser mas segmentoso
	MOV esp, 0x27000;

    ; pintar pantalla, todos los colores, que bonito! TODO esto no anda aún

	MOV ecx, 80; Quiero pintar todas las filas de cualquier color salvo la primera y la última.
	XOR edx, edx;
	MOV bx, 0000000001110000b ; Máscara que deja como estaban sólo los bits 4, 5 y 6;

__pintarrajear:
	RDRAND ax
	AND ax, bx;
	MOV byte [fs:edx+1], "a"
	ADD edx, 2;
	loop __pintarrajear

	xchg bx, bx




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
