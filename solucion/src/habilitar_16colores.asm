	; habilitar 16 colores
	
	MOV 		DX, 3DAH		;port of input status #1 register - clear the flip flop
	IN 			AX, DX

	MOV 		AL, 10H+20H		;move the index of the attribute register into the attribute
	MOV 		DX, 3C0H		; address register and leave PAS bit on
	OUT 		DX, AL

	MOV 		DX, 3C1H		;get the data of the attribute mode control register
	IN 			AL, DX

	AND 		AL, 0xF7		;turn on the blink bit
	MOV 		DX, 3C0H		;we have to input data in the register through the address register port
	OUT 		DX, AL

	MOV 		AX, 4C00H		;End processing
	INT 		21H

    ; Pongo el cursor afuera de la pantalla [http://wiki.osdev.org/Text_Mode_Cursor]
    
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

    