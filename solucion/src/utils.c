
#include "utils.h"
#include "defines.h"
#include "mmu.h"
#include "gdt.h"
#include "i386.h"


int int_size(int num);

void memcpy(void* dst, void* src, int size) {
	
	char* src_char = (char*) src;
	char* dst_char = (char*) dst;

	int i;
	for(i = 0; i < size ; i++) {
		dst_char[i] = src_char[i];
	}

}

void memclear(void* dst, int size){
	char* dst_char = (char*) dst;

	int i;
	for (i = 0; i < size; i++) {
		dst_char[0]=0;
	}
}

int strlen(char* str){
	int i=0;
	while (*str !=0){
		str++;
		i++;
	}
	return i;
}

int int_size(int num){

	if (num == 0) return 1;

	int i=0;
	while (num){
		num= num/10;
		i++;
	}
	return i;
}

int obtener_indice_tarea_en_ejecucion() {
	
	return (rtr() >> 3);	
}

int es_navio(int indice) {

	return (GDT_IDX_TASK_OFFSET <= indice
		&& indice < (GDT_IDX_TASK_OFFSET + CANT_TAREAS));
}

int es_bandera(int indice) {

	return (GDT_IDX_TASK_BANDERA_OFFSET <= indice
		&& indice < (GDT_IDX_TASK_BANDERA_OFFSET + CANT_TAREAS));
}

int numero_tarea(int indice) {

	if(GDT_IDX_TASK_OFFSET <= indice && indice < (GDT_IDX_TASK_OFFSET + CANT_TAREAS))
		return indice - GDT_IDX_TASK_OFFSET;
	else
		return indice - GDT_IDX_TASK_BANDERA_OFFSET;
}