; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

;; PIC
extern fin_intr_pic1

;; Funciones de pantalla
extern pintar_pantalla_modo_mapa
extern pintar_pantalla_modo_estado

;; Funciones de juego
extern game_fondear
extern game_canonear
extern game_navegar

;; Funciones del Scheduler
extern sched_resetear_tick
extern sched_proximo_indice
extern hundir_navio
extern es_navio;


;; Funciones de la tss
extern tss_pisar_bandera_actual

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
extern _isr%1_c
global _isr%1
_isr%1:
    
    CALL 	_isr%1_c

    JMP  	0xC0:0
    
%endmacro

%define SYS_FONDEAR		0x923
%define SYS_CANONEAR	0x83A
%define SYS_NAVEGAR		0xAEF

%define TRUE	1
%define FALSE	0
;;
;; Datos
;; -------------------------------------------------------------------------- ;;

; Scheduler
reloj_numero:           dd 0x00000000
reloj:                  db '|/-\'

; Mensajes a imprimir en las ISRs
_isr_msj_0:             db 'Divide Error Exception'
_isr_msj_len_0          equ $ - _isr_msj_0
_isr_msj_1:             db 'Debug Exception'
_isr_msj_len_1          equ $ - _isr_msj_1
_isr_msj_2:             db 'Non Maskable Interrupt'
_isr_msj_len_2          equ $ - _isr_msj_2
_isr_msj_3:             db 'Breakpoint Exception'
_isr_msj_len_3          equ $ - _isr_msj_3
_isr_msj_4:             db 'Overflow Exception'
_isr_msj_len_4          equ $ - _isr_msj_4
_isr_msj_5:             db 'BOUND Range Exceeded Exception'
_isr_msj_len_5          equ $ - _isr_msj_5
_isr_msj_6:             db 'Invalid Opcode Exception'
_isr_msj_len_6          equ $ - _isr_msj_6
_isr_msj_7:             db 'Device Not Available Exception'
_isr_msj_len_7          equ $ - _isr_msj_7
_isr_msj_8:             db 'Double Fault Exception'
_isr_msj_len_8          equ $ - _isr_msj_8
_isr_msj_9:             db 'Coprocessor Segment Overrun'
_isr_msj_len_9          equ $ - _isr_msj_9
_isr_msj_10:            db 'Invalid TSS Exception'
_isr_msj_len_10         equ $ - _isr_msj_10
_isr_msj_11:            db 'Segment Not Present'
_isr_msj_len_11         equ $ - _isr_msj_11
_isr_msj_12:            db 'Stack Fault Exception'
_isr_msj_len_12         equ $ - _isr_msj_12
_isr_msj_13:            db 'General Protection Exception'
_isr_msj_len_13         equ $ - _isr_msj_13
_isr_msj_14:            db 'Page-Fault Exception'
_isr_msj_len_14         equ $ - _isr_msj_14
_isr_msj_15:            db 'Reserved'
_isr_msj_len_15         equ $ - _isr_msj_15
_isr_msj_16:            db 'x87 FPU Floating-Point Error'
_isr_msj_len_16         equ $ - _isr_msj_16
_isr_msj_17:            db 'Alignment Check Exception'
_isr_msj_len_17         equ $ - _isr_msj_17
_isr_msj_18:            db 'Machine-Check Exception'
_isr_msj_len_18         equ $ - _isr_msj_18
_isr_msj_19:            db 'SIMD Floating-Point Exception'
_isr_msj_len_19         equ $ - _isr_msj_19

; strings a imprimir cuando se presiona un digito
_digito_0_str:			db '0'
_digito_1_str:			db '1'
_digito_2_str:			db '2'
_digito_3_str:			db '3'
_digito_4_str:			db '4'
_digito_5_str:			db '5'
_digito_6_str:			db '6'
_digito_7_str:			db '7'
_digito_8_str:			db '8'
_digito_9_str:			db '9'

;;
;; Rutinas de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;

ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

extern _isr32_c
_isr_32_offset:		DD 0
_isr_32_selector:	DW 0
global _isr32
_isr32:
	CLI
	PUSHAD
	PUSHFD

	CALL    	fin_intr_pic1
    CALL		proximo_reloj

    CALL 		_isr32_c

    sal 		ax, 3
    MOV WORD	[_isr_32_selector], ax
    jmp far 	[_isr_32_offset]

	POPFD
	POPAD
	STI
	IRET

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global pantalla_activa
pantalla_activa: DB 	'm'
global _isr33
_isr33:
	CLI
	PUSHAD
	PUSHFD

	CALL       		fin_intr_pic1

    IN 				AL, 0x60

.switch:
.letra_m:
    CMP 			AL, 0x32			; M
    JNE 			.letra_e

    call 			pintar_pantalla_modo_mapa
    mov byte		[pantalla_activa], 'm'

    JMP 			.end_switch
.letra_e:
    CMP 			AL, 0x12			; E
    JNE 			.digito_0

    call 			pintar_pantalla_modo_estado
    mov byte		[pantalla_activa], 'e'

	JMP 			.end_switch
.digito_0:
	cmp 			AL, 0x0B			; 0
	JNE 			.digito_1

	imprimir_texto_mp 		_digito_0_str, 1, 0x0F, 0, 79

	JMP 			.end_switch
.digito_1:
	cmp 			AL, 0x02			; 1
	JNE 			.digito_2

	imprimir_texto_mp 		_digito_1_str, 1, 0x1F, 0, 79

	JMP 			.end_switch
.digito_2:
	cmp 			AL, 0x03			; 2
	JNE 			.digito_3

	imprimir_texto_mp 		_digito_2_str, 1, 0x2F, 0, 79

	JMP 			.end_switch
.digito_3:
	cmp 			AL, 0x04			; 3
	JNE 			.digito_4

	imprimir_texto_mp 		_digito_3_str, 1, 0x3F, 0, 79

	JMP 			.end_switch
.digito_4:
	cmp 			AL, 0x05			; 4
	JNE 			.digito_5

	imprimir_texto_mp 		_digito_4_str, 1, 0x4F, 0, 79

	JMP 			.end_switch
.digito_5:
	cmp 			AL, 0x06			; 5
	JNE 			.digito_6

	imprimir_texto_mp 		_digito_5_str, 1, 0x5F, 0, 79

	JMP 			.end_switch
.digito_6:
	cmp 			AL, 0x07			; 6
	JNE 			.digito_7

	imprimir_texto_mp 		_digito_6_str, 1, 0x6F, 0, 79

	JMP 			.end_switch
.digito_7:
	cmp 			AL, 0x08			; 7
	JNE 			.digito_8

	imprimir_texto_mp 		_digito_7_str, 1, 0x7F, 0, 79

	JMP 			.end_switch
.digito_8:
	cmp 			AL, 0x09			; 8
	JNE 			.digito_9

	imprimir_texto_mp 		_digito_8_str, 1, 0x8F, 0, 79

	JMP 			.end_switch
.digito_9:
	cmp 			AL, 0x0A			; 9
	JNE 			.end_switch

	imprimir_texto_mp 		_digito_9_str, 1, 0x9F, 0, 79

	JMP 			.end_switch
.end_switch:

	POPFD
	POPAD
	STI
	IRET

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

;~ Habria que checkear quien la llama? (talvez alguna tarea no tiene permiso para llamarla)
extern _isr0x50_c
global _isr0x50
_isr0x50:	
	CLI
	PUSHAD
	PUSHFD

	PUSH 		ecx
	PUSH 		ebx
	PUSH 		eax
    CALL 		_isr0x50_c
    POP 		eax
    POP 		ebx
    POP 		ecx

    JMP  		0xC0:0

	POPFD
	POPAD
	STI
	IRET

extern _isr0x66_c
global _isr0x66
_isr0x66:	
	CLI
	PUSHAD
	PUSHFD

    CALL 		_isr0x66_c

    JMP  		0xC0:0

	POPFD
	POPAD
	STI
	IRET


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;

proximo_reloj:
    pushad

    inc DWORD [reloj_numero]
    mov ebx, [reloj_numero]
    cmp ebx, 0x4
    jl .ok
        mov DWORD [reloj_numero], 0x0
        mov ebx, 0
    .ok:
        add ebx, reloj
        imprimir_texto_mp ebx, 1, 0x0f, 24, 79

    popad
    ret
