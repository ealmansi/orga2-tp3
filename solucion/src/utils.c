
#include "utils.h"
#include "defines.h"



void memcpy(void* src, void* dst, int size) {
	
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
