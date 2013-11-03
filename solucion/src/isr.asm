; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32


;; PIC
extern fin_intr_pic1


;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1
_isr%1:
    imprimir_texto_mp _isr_msj_%1, _isr_msj_len_%1, 0x07, 0, 0
    jmp $
%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
reloj_numero:           dd 0x00000000
reloj:                  db '|/-\'

; Mensajes a imprimir en las ISRs
_isr_msj_0:             db 'Rutina de interrupcion nro 0'
_isr_msj_len_0          equ $ - _isr_msj_0
_isr_msj_1:             db 'Rutina de interrupcion nro 1'
_isr_msj_len_1          equ $ - _isr_msj_1
_isr_msj_2:             db 'Rutina de interrupcion nro 2'
_isr_msj_len_2          equ $ - _isr_msj_2
_isr_msj_3:             db 'Rutina de interrupcion nro 3'
_isr_msj_len_3          equ $ - _isr_msj_3
_isr_msj_4:             db 'Rutina de interrupcion nro 4'
_isr_msj_len_4          equ $ - _isr_msj_4
_isr_msj_5:             db 'Rutina de interrupcion nro 5'
_isr_msj_len_5          equ $ - _isr_msj_5
_isr_msj_6:             db 'Rutina de interrupcion nro 6'
_isr_msj_len_6          equ $ - _isr_msj_6
_isr_msj_7:             db 'Rutina de interrupcion nro 7'
_isr_msj_len_7          equ $ - _isr_msj_7
_isr_msj_8:             db 'Rutina de interrupcion nro 8'
_isr_msj_len_8          equ $ - _isr_msj_8
_isr_msj_9:             db 'Rutina de interrupcion nro 9'
_isr_msj_len_9          equ $ - _isr_msj_9
_isr_msj_10:            db 'Rutina de interrupcion nro 10'
_isr_msj_len_10         equ $ - _isr_msj_10
_isr_msj_11:            db 'Rutina de interrupcion nro 11'
_isr_msj_len_11         equ $ - _isr_msj_11
_isr_msj_12:            db 'Rutina de interrupcion nro 12'
_isr_msj_len_12         equ $ - _isr_msj_12
_isr_msj_13:            db 'Rutina de interrupcion nro 13'
_isr_msj_len_13         equ $ - _isr_msj_13
_isr_msj_14:            db 'Rutina de interrupcion nro 14'
_isr_msj_len_14         equ $ - _isr_msj_14
_isr_msj_15:            db 'Rutina de interrupcion nro 15'
_isr_msj_len_15         equ $ - _isr_msj_15
_isr_msj_16:            db 'Rutina de interrupcion nro 16'
_isr_msj_len_16         equ $ - _isr_msj_16
_isr_msj_17:            db 'Rutina de interrupcion nro 17'
_isr_msj_len_17         equ $ - _isr_msj_17
_isr_msj_18:            db 'Rutina de interrupcion nro 18'
_isr_msj_len_18         equ $ - _isr_msj_18
_isr_msj_19:            db 'Rutina de interrupcion nro 19'
_isr_msj_len_19         equ $ - _isr_msj_19

;;
;; Rutina de atención de las EXCEPCIONES
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
global _isr32
_isr32:
	cli
	pushad
	pushfd
	
	call proximo_reloj
	
	popfd
	popad
	sti
	iret
;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global _isr33
_isr33:
	
	jmp $
	
	iret
;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
global _isr80
_isr80:
	
	jmp $
	
	iret

global _isr102
_isr102:
	
	jmp $
	
	iret

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
