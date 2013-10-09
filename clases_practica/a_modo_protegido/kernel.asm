%macro breakpoint 0
	xchg bx,bx
%endmacro

ORG 0x1200

;---------------------------------- MODO REAL --------------------------------;

BITS 16

    cli

;---------------------- ESCRIBIMOS UN MENSAJE EN MODO REAL -------------------;

	call limpiar_pantalla_16b

	mov ax, 0xB800
	mov fs, ax

	mov byte [fs:0x00], "m"
	mov byte [fs:0x01], 010b
	mov byte [fs:0x02], "o"
	mov byte [fs:0x03], 010b
	mov byte [fs:0x04], "d"
	mov byte [fs:0x05], 010b
	mov byte [fs:0x06], "o"
	mov byte [fs:0x07], 010b
	mov byte [fs:0x08], " "
	mov byte [fs:0x09], 010b
	mov byte [fs:0x0A], "r"
	mov byte [fs:0x0B], 010b
	mov byte [fs:0x0C], "e"
	mov byte [fs:0x0D], 010b
	mov byte [fs:0x0E], "a"
	mov byte [fs:0x0F], 010b
	mov byte [fs:0x10], "l"
	mov byte [fs:0x11], 010b

	breakpoint

;--------------------------------- CARGAMOS GDT ------------------------------;

	lgdt [gdt_desc]
   
;--------------------------- PASO A MODO PROTEGIDO ---------------------------;

	mov eax, cr0				; activo bit PE
    or  eax, 1
    mov cr0, eax
    jmp 000000000001000b:mp 	; seteo cs = { index: 1 | gdt/ldt: 0 | rpl: 00 }

BITS 32
mp:									; cargo los registros de segmento
	xor eax, eax
	mov ax, 0000000000010000b 		; ds, gs, es = { index: 2 | gdt/ldt: 0 | rpl: 00 }
	mov ds, ax
	mov es, ax
	mov gs, ax
	mov ax, 0000000000011000b 		; fs = { index: 3 | gdt/ldt: 0 | rpl: 00 }
	mov fs, ax

;----------------- ESCRIBIMOS UN MENSAJE EN MODO PROTEGIDO -------------------;

	mov byte [fs:0x00], "m"
	mov byte [fs:0x01], 011b
	mov byte [fs:0x02], "o"
	mov byte [fs:0x03], 011b
	mov byte [fs:0x04], "d"
	mov byte [fs:0x05], 011b
	mov byte [fs:0x06], "o"
	mov byte [fs:0x07], 011b
	mov byte [fs:0x08], " "
	mov byte [fs:0x09], 011b
	mov byte [fs:0x0A], "t"
	mov byte [fs:0x0B], 011b
	mov byte [fs:0x0C], "r"
	mov byte [fs:0x0D], 011b
	mov byte [fs:0x0E], "u"
	mov byte [fs:0x0F], 011b
	mov byte [fs:0x10], "c"
	mov byte [fs:0x11], 011b
	mov byte [fs:0x12], "h"
	mov byte [fs:0x13], 011b
	mov byte [fs:0x14], "o"
	mov byte [fs:0x15], 011b

;----------------- ACA TERMINA NUESTRO CODIGO 'LO COLGAMOS' ------------------;

    jmp $

;=================== A PARTIR DE ESTE PUNTO PEGO LA GDT ======================;

gdt:
	; primer selector nulo
	dq 0x0

sc0: ; segmento de código
	dw 0x3FFF 				; seglimit 15:00
	dw 0x0000				; baseaddr 15:00
	db 0x00 				; baseaddr 23:16
	db 10011010b			; [7 | 6 5 | 4 | 3 2 1 0] %% [p | dpl | s | type]
	db 11000000b			; [7 | 6 | 5 | 4 | 3 2 1 0] %% [g | db | l | avl | seglimit 19:16]
	db 0x00 				; baseaddr 31:24

sd0: ; segmento de datos
	dw 0x3FFF 				; seglimit 15:00
	dw 0x0000				; baseaddr 15:00
	db 0x00 				; baseaddr 23:16
	db 10010010b			; [7 | 6 5 | 4 | 3 2 1 0] %% [p | dpl | s | type]
	db 11000000b			; [7 | 6 | 5 | 4 | 3 2 1 0] %% [g | db | l | avl | seglimit 19:16]
	db 0x00 				; baseaddr 31:24

sv: ; segmento de video
	dw 0x0FBF 				; seglimit 15:00
	dw 0x8000				; baseaddr 15:00
	db 0x0B 				; baseaddr 23:16
	db 10010010b			; [7 | 6 5 | 4 | 3 2 1 0] %% [p | dpl | s | type]
	db 01000000b			; [7 | 6 | 5 | 4 | 3 2 1 0] %% [g | db | l | avl | seglimit 19:16]
	db 0x00 				; baseaddr 31:24

gdt_desc:
	dw $-gdt 		; gdt_desc - tamaño
	dd gdt 			; gdt_desc - base


;----------------- AUXILIARES ------------------;

BITS 16

limpiar_pantalla_16b:

	mov ax, 0xB800
	mov fs, ax

.for:
	xor bx, bx

.guarda:
	cmp bx, 0x7D0 		; 80 * 25
	jge .endfor

	mov word [fs:bx], 0

	inc bx
	inc bx
	jmp .guarda
.endfor:

	ret
