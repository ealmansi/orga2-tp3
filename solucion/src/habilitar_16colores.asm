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

	MOV 		AH, 09H			;routine for displaying the character
	MOV 		AL, 01H
	MOV 		BH, 0
	MOV 		BL, 10100100B	;background: blinking blue - foreground: red
	MOV 		CX, 0001H
	INT 		10H

	MOV 		AX, 4C00H		;End processing
	INT 		21H