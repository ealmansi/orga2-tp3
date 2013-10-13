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

.limpiarPantalla:
	MOV 	byte [fs:ecx-1], 0
	LOOP 	.limpiarPantalla

	; ; Setear primera y ultima filas en formato de letras blancas y fondo negro
	MOV 	ecx, 80 				; Cada fila tiene 80 caracteres. Con esto puedo hacer loop.
	XOR 	ebx, ebx				; Contador de posición primera fila
	MOV 	edx, 80*2*24			; Contador de posición ultima fila

.setearFormatoFilas
	MOV 	byte [fs:ebx+1], 00001111b
	MOV 	byte [fs:edx+1], 00001111b
	ADD		edx, 2
	ADD		ebx, 2
	LOOP 	.setearFormatoFilas

	; ; Colorear pantalla	

	MOV 	ecx, 80*23				; Quiero pintar todas las filas de cualquier color
	MOV 	edi, 0xB8000 			; salvo la primera y la última.
	MOV 	esi, 160

.pintarrajear:
	MOV 	byte [edi+esi+1], 01110000b
	ADD		esi, 2
	LOOP 	.pintarrajear

	xchg	bx, bx

jmp despues

; ~ void insertarFormatoRectangular(unsigned char format, unsigned int X, unsigned int Y, unsigned int ancho, unsigned int alto)
%define format [ebp+8]
%define X [ebp+12]
%define Y [ebp+16]
%define ancho [ebp+20]
%define alto [ebp+24]


__insertarFormatoRectangular:
	PUSH 	ebp
	MOV 	ebp, esp
	PUSH	edi
	PUSH	esi
	PUSH	ebx

	MOV		edi, 0xB8000
	MOV		esi, X
	SAL		esi, 1
	ADD 	edi, esi
	MOV 	eax, 160
	MOV		ecx, Y
	IMUL	ecx						; El resultado entra en EAX porque son números chicos.
	ADD		edi, eax
	INC		edi						; Se incrementa en uno porque se quiere grabar formato en las posiciones impares.
	; En este punto ya tengo en EDI la posición inicial a partir de la cuál hay que escribir.

	MOV eax, format;
	MOV ecx, alto;


.CicloExternoInsertarFormatoRectangular:
	MOV edx, ancho;
	DEC edx;

.CicloInternoinsertarFormatoRectangular:

		MOV 	[edi+2*edx], al
		DEC 	edx
		CMP 	edx, 0 
		JGE 	.CicloInternoinsertarFormatoRectangular
		; Fin ciclo interno.

	ADD 	edi, 160;
	LOOP 	.CicloExternoInsertarFormatoRectangular
	; Fin ciclo externo.
	

	POP ebx
	POP esi
	POP edi
	POP ebp
	RET


despues:



