#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <cutils.h>
#include <stdbool.h>

#define LOG_BUF_SIZE 1024 
#define GREEN   "\e[0;32m"
#define YELLOW  "\e[0;33m"
#define RED     "\e[0;31m"
#define DEFAULT "\e[0;0m"
#define println puts

// Used by autofree and autoclose
static void _free_resource(void* p) { free(*(void**)p); } 
static void _close_file(FILE** f)   { if(*f) { fclose(*f); *f = NULL; } }

static size_t _strlen(char* s){
	size_t res = 0;
	while(*s++) res++;
	return res;
}

int swap_endian(int byte, bool q){

	if(q) {
		logger("Inputs to swap_endian() must be in hex format prefixed with '0x'",
		LOGGER_LOG);
		logger("Pass 'false' as the second argument to suppress this message",
		LOGGER_LOG);
	}
	
	int left 	  = (byte & 0x000000FF) >> 0;
	int left_mid  = (byte & 0x0000FF00) >> 8;
	int right_mid = (byte & 0x00FF0000) >> 16;
	int right 	  = (byte & 0xFF000000) >> 24;

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

static void _swap_int(int* x, int* y){

	if(x == y) return;

	int tmp = *x;
	*x = *y;
	*y = tmp;
}

static void _swap_float(float* x, float* y){

	if(x == y) return;

	float tmp = *x;
	*x = *y;
	*y = tmp;
}

#define swap(x, y) _Generic((x), \
	int*:   _swap_int,			 \
	float*: _swap_float			 \
)(x, y)

int main(int argc, char** argv){

	int x = 10;
	int y = 20;
	float z = -10.5f;
	float a = 20.0f;
	printf("%.2f %.2f\n", z, a);
	logger("Swapping.", LOGGER_LOG);
	swap(&z, &a);
	printf("%.2f %.2f\n", z, a);
	int be = 0x12345678;
	int le = 0x78563412;
	int res = swap_endian(be, false);
	int res2 = swap_endian(le, false);
    return 0;
}
