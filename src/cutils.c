#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <cutils.h>
#include <stdbool.h>

// Used by autofree and autoclose
void _free_resource(void* p) { free(*(void**)p); } 
void _close_file(FILE** f)   { if(*f) { fclose(*f); *f = NULL; } }

size_t _strlen(char* s){
	size_t res = 0;
	while(*s++) res++;
	return res;
}

int swap_endian(int hex){
	
	// this obviously breaks if input isn't in hex format
	int left 	  = (hex & 0x000000FF) >> 0;
	int left_mid  = (hex & 0x0000FF00) >> 8;
	int right_mid = (hex & 0x00FF0000) >> 16;
	int right 	  = (hex & 0xFF000000) >> 24;

	left      <<= 24;
	left_mid  <<= 16;
	right_mid <<= 8;
	right 	  <<= 0;
	
	return(left | left_mid | right_mid | right);
}

void logger(const char* const s, const int log_level){
	
	char log_str[LOG_BUF_SIZE];

	switch(log_level){
		case LOGGER_LOG:
			snprintf(log_str, sizeof(log_str), "%s[INFO]:  %s%s",
					GREEN, DEFAULT, s);
			break;

		case LOGGER_WARN:
			snprintf(log_str, sizeof(log_str), "%s[WARN]:  %s%s",
					YELLOW, DEFAULT, s);
			break;

		case LOGGER_ERROR:
			snprintf(log_str, sizeof(log_str), "%s[ERROR]: %s%s",
					RED, DEFAULT, s);
			break;
	}

	const size_t len = _strlen(log_str);

	// TODO magic 16
	assert(len + 16 <= LOG_BUF_SIZE);
	log_str[len] = '\0';
	println(log_str);
}

void _swap_int(int* x, int* y){

	if(x == y) return;

	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void _swap_float(float* x, float* y){

	if(x == y) return;

	float tmp = *x;
	*x = *y;
	*y = tmp;
}

void _swap_double(double* x, double* y){
	
	if(x == y) return;

	double tmp = *x;
	*x = *y;
	*y = tmp;
}

