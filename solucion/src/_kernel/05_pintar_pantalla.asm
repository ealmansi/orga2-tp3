	; pintar pantalla, todos los colores, que bonito!

    ; ; Pongo el cursor afuera de la pantalla [http://wiki.osdev.org/Text_Mode_Cursor]
    mov ax, -1
    and ax,0ffh             ;set AX to 'row'
    mov cl,80   
    mul cl                  ;row*80

    mov cx,bx               
    shr cx,8                ;set CX to 'col'
    add ax,cx               ;+ col
    mov cx,ax               ;store 'position' in CX

    mov al,0fh              ;cursor LOW port to vga INDEX register
    mov dx,3d4h             ;VGA port 3D4h
    out dx,al             

    mov ax,cx               ;restore 'postion' back to AX  
    mov dx,3d5h             ;VGA port 3D5h
    out dx,al               ;send to VGA hardware

    mov al,0eh 				;cursor HIGH port to vga INDEX register
    mov dx,3d4h             ;VGA port 3D4h
    out dx,al

    mov ax,cx               ;restore 'position' back to AX
    shr ax,8                ;get high byte in 'position'
    mov dx,3d5h             ;VGA port 3D5h
    out dx,al               ;send to VGA hardware

	; ; Limpiar pantalla
	MOV 	ecx, 80*2*25 			; cantidad total de bytes de video

.limpiar_pantalla:
	MOV 	byte [fs:ecx-1], 0
	LOOP 	.limpiar_pantalla

	; ; Setear primera y ultima filas en formato de letras blancas y fondo negro
	MOV 	ecx, 80 				; Cada fila tiene 80 caracteres. Con esto puedo hacer loop.
	XOR 	ebx, ebx				; Contador de posición primera fila
	MOV 	edx, 80*2*24			; Contador de posición ultima fila

.setear_formato_filas
	MOV 	byte [fs:ebx+1], 00001111b
	MOV 	byte [fs:edx+1], 00001111b
	ADD		edx, 2
	ADD		ebx, 2
	LOOP 	.setear_formato_filas

	; ; Colorear pantalla	
	MOV 	ecx, 80*23				; Quiero pintar todas las filas de cualquier color
	MOV 	edi, 0xB8000 			; salvo la primera y la última.
	MOV 	esi, 160
	MOV 	bx, 0000000001110000b 	; Máscara que deja como estaban sólo los bits 4, 5 y 6;

.pintarrajear:
	RDTSC
	AND		ax, bx
	MOV 	byte [edi+esi+1], al
	ADD		esi, 2
	LOOP 	.pintarrajear