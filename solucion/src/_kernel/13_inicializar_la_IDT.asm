extern IDT_DESC
extern idt_inicializar

	; inicializar la IDT

	CALL		idt_inicializar

	LIDT 		[IDT_DESC]