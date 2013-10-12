	; pintar pantalla, todos los colores, que bonito!

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