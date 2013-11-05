
#include "utils.h"
#include "defines.h"


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

