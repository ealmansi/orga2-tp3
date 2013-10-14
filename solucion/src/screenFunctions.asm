global insertarFormatoRectangular
global printSquareText
global algunTexto


; ~ void insertarFormatoRectangular(unsigned char format, unsigned int X, unsigned int Y, unsigned int ancho, unsigned int alto)
%define format [ebp+8]
%define X [ebp+12]
%define Y [ebp+16]
%define ancho [ebp+20]
%define alto [ebp+24]


insertarFormatoRectangular:
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
%define format format 
%define X X
%define Y Y
%define ancho  ancho 
%define alto alto



; ~ void printSquareText (unsigned int X,unsigned int Y, unsigned int long, char* text)
%define X [ebp+8]
%define Y [ebp+12]
%define long [ebp+16]
%define text [ebp+20]

printSquareText:
	PUSH 	ebp
	MOV 	ebp, esp
	PUSH 	edi
	PUSH 	esi
	PUSH 	ebx

	MOV 	edi, 0xB8000
	MOV 	esi, X
	SAL		esi, 1
	ADD 	edi, esi
	MOV 	eax, 160
	MOV 	esi, Y
	MUL		esi
	ADD		edi, eax		; A esta altura tengo en edi el puntero a la primera posición en la que tengo que grabar.

	MOV 	ebx, text
	MOV		edx, long

.cicloExternoPrintSquareText:
	XOR		ecx, ecx

.cicloInternoPrintSquareText:
		MOV 	al, [ebx]
		CMP 	al, 0 
		JE 		.salidaPrintText
		
		MOV		[edi+2*ecx], al		;

		INC 	ecx
		INC		ebx
		CMP		ecx, edx
		JL .cicloInternoPrintSquareText
;----------- final ciclo interno ---------------
	ADD edi, 160
	JMP .cicloExternoPrintSquareText
;----------- final ciclo externo ---------------

.salidaPrintText:

	POP ebx
	POP esi
	POP edi
	POP ebp
	RET

algunTexto: DB "12345678910", 0
