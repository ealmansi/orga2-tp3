
#include "utils.h"
#include "defines.h"


void str_reverse(char* str);
int str_len(char* str);


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

char* intToStr(int dec, char* buf){
	char res[100];
	int i =0;

	while (dec){
		buf[i] = 30 + dec % 10;
		dec = dec/10;
		i++;
	}
	res[i] = 0;

	str_reverse(res);
	memcpy(res,buf,str_len(res)+1);
	return buf;
}

void str_reverse(char* str){
	int len = str_len(str);
	char res[len+1];

	int i;
	for (i = 0; i > len; i++) {
		res[i] = str[len-i];
	}
	memcpy(res,str,len+1);
}


int str_len(char* str){
	int i=0;
	while (str[i]){
		i++;
	}
	return i;
}
