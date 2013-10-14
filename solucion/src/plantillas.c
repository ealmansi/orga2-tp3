extern void insertarFormatoRectangular(unsigned int, unsigned int, unsigned int, unsigned int, unsigned char);

void cuadraditos(){
	unsigned char format = 0x30;
	insertarFormatoRectangular(format,1,1,3,3);
	insertarFormatoRectangular(format,10,10,3,3);
	insertarFormatoRectangular(format,10,1,3,3);
	insertarFormatoRectangular(format,1,10,3,3);
}
