extern plantillaMapa

    ; Limpiar pantalla

    MOV     ecx, 80*2*25            ; cantidad total de bytes de video

.limpiarPantalla:
    MOV     byte [fs:ecx-1], 0
    LOOP    .limpiarPantalla

    ; Setear primera y ultima filas en formato de letras blancas y fondo negro

    MOV     ecx, 80                 ; Cada fila tiene 80 caracteres. Con esto puedo hacer loop.
    XOR     ebx, ebx                ; Contador de posición primera fila
    MOV     edx, 80*2*24            ; Contador de posición ultima fila

.setearFormatoFilas:
<<<<<<< HEAD
    MOV     byte [fs:ebx+1], 00001111b
    MOV     byte [fs:edx+1], 00001111b
    ADD     edx, 2
    ADD     ebx, 2
    LOOP    .setearFormatoFilas
=======
	MOV 	byte [fs:ebx+1], 00001111b
	MOV 	byte [fs:edx+1], 00001111b
	ADD		edx, 2
	ADD		ebx, 2
	LOOP 	.setearFormatoFilas

	; Colorear pantalla	
	extern plantillaMapa
	 call plantillaMapa
>>>>>>> e856b34884f23e50eb37f56a88caf996a1d0a93d

    ; Colorear pantalla    
    
<<<<<<< HEAD
    CALL    plantillaMapa
=======
    MOV     ax, -1
    AND     ax,0ffh             ;set AX to 'row'
    MOV     cl,80   
    MUL     cl                  ;row*80

    MOV     cx,bx               
    SHR     cx,8                ;set CX to 'col'
    ADD     ax,cx               ;+ col
    MOV     cx,ax               ;store 'position' in CX

    MOV     al,0fh              ;cursor LOW port to vga INDEX register
    MOV     dx,3d4h             ;VGA port 3D4h
    OUT     dx,al             

    MOV     ax,cx               ;restore 'postion' back to AX  
    MOV     dx,3d5h             ;VGA port 3D5h
    OUT     dx,al               ;send to VGA hardware

    MOV     al,0eh              ;cursor HIGH port to vga INDEX register
    MOV     dx,3d4h             ;VGA port 3D4h
    OUT     dx,al

    MOV     ax,cx               ;restore 'position' back to AX
    SHR     ax,8                ;get high byte in 'position'
    MOV     dx,3d5h             ;VGA port 3D5h
    OUT     dx,al               ;send to VGA hardware

    
>>>>>>> e856b34884f23e50eb37f56a88caf996a1d0a93d
