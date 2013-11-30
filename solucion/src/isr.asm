; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

;; PIC
extern fin_intr_pic1

;; var global
extern pantalla_activa

;; ISR's en C
extern _isr32_c
extern _isr0x50_c
extern _isr0x66_c

;; exportadas
global _isr32
global _isr33
global _isr0x50
global _isr0x66

global _estado_eax
global _estado_ebx
global _estado_ecx
global _estado_edx
global _estado_esi
global _estado_edi
global _estado_ebp
global _estado_esp
global _estado_eip
global _estado_cr0
global _estado_cr2
global _estado_cr3
global _estado_cr4
global _estado_cs
global _estado_ds
global _estado_es
global _estado_fs
global _estado_gs
global _estado_ss
global _estado_eflags

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
extern _isr%1_c
global _isr%1
_isr%1:
	CLI
	PUSHAD
	PUSHFD

    guardar_estado

    CALL 	_isr%1_c

    JMP  	0xC0:0
	
	POPFD
	POPAD
	STI
	IRET
%endmacro

guardar_eip_en_eax:
	MOV eax, [esp];
	RET


%macro guardar_estado 0
	mov edx, eax
	MOV edi, ebx
	MOV esi, ecx
	mov dword		[_estado_eax],eax
	mov dword		[_estado_ebx], ebx
	mov dword		[_estado_ecx], ecx
	mov dword		[_estado_edx], edx
	mov dword		[_estado_esi], esi
	mov dword		[_estado_edi], edi
	mov dword		[_estado_ebp], ebp
	mov dword		[_estado_esp], esp
	CALL guardar_eip_en_eax
	mov dword		[_estado_eip], eax
	mov 			eax, cr0
	mov dword 		[_estado_cr0], eax
	mov 			eax, cr2
	mov dword 		[_estado_cr2], eax
	mov 			eax, cr3
	mov dword 		[_estado_cr3], eax
	mov 			eax, cr4
	mov dword 		[_estado_cr4], eax
	MOV ax, cs
	mov 			[_estado_cs], ax
	MOV ax, ds
	mov 			[_estado_ds], ax
	MOV ax, es
	mov 			[_estado_es], ax
	MOV ax, fs
	mov 			[_estado_fs], ax
	MOV ax, gs
	mov 			[_estado_gs], ax
	MOV ax, ss
	mov 			[_estado_ss], ax
	MOV eax, [esp]
	mov dword		[_estado_eflags], eax
	mov eax, edx
	MOV ebx, edi
	MOV ecx, esi
%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;

; Scheduler
reloj_numero:           dd 0x00000000
reloj:                  db '|/-\'

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

_estado_eax:		dd 0
_estado_ebx:		dd 0
_estado_ecx:		dd 0
_estado_edx:		dd 0
_estado_esi:		dd 0
_estado_edi:		dd 0
_estado_ebp:		dd 0
_estado_esp:		dd 0
_estado_eip:		dd 0
_estado_cr0:		dd 0
_estado_cr2:		dd 0
_estado_cr3:		dd 0
_estado_cr4:		dd 0
_estado_cs:			dd 0
_estado_ds:			dd 0
_estado_es:			dd 0
_estado_fs:			dd 0
_estado_gs:			dd 0
_estado_ss:			dd 0
_estado_eflags:		dd 0

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


_isr_32_offset:		DD 0
_isr_32_selector:	DW 0
_isr32:
	CLI
	PUSHAD
	PUSHFD

	guardar_estado

    CALL		proximo_reloj

    CALL 		_isr32_c
		CMP ax, 0 ;
		JNE saltar_isr32;
		CALL fin_intr_pic1;
		STI
		jmp fin_isr32


saltar_isr32:
    sal 		ax, 3
    MOV WORD	[_isr_32_selector], ax
	CALL    	fin_intr_pic1
	STI
    jmp far 	[_isr_32_offset]



fin_isr32:
	POPFD
	POPAD
	STI
	IRET

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;

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

    mov byte		[pantalla_activa], 'm'

    JMP 			.end_switch
.letra_e:
    CMP 			AL, 0x12			; E
    JNE 			.digito_0

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

_isr0x50:	
	CLI
	PUSHAD
	PUSHFD

	guardar_estado

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


_isr0x66:	
	CLI
	PUSHAD
	PUSHFD

	guardar_estado

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
