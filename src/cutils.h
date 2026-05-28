#ifndef CUTILS_H
#define CUTILS_H

#include <stdlib.h>
#include <stdio.h>

#define LOG_BUF_SIZE 1024 
#define GREEN   "\e[0;32m"
#define YELLOW  "\e[0;33m"
#define RED     "\e[0;31m"
#define DEFAULT "\e[0;0m"
#define println puts

enum {
	LOGGER_LOG,
	LOGGER_WARN,
	LOGGER_ERROR
};

void _free_resource(void* p);
void _close_file(FILE** f);

#define autofree  __attribute((cleanup(_free_resource)))
#define autoclose __attribute((cleanup(_close_file)))

size_t _strlen(char* s);
void _swap_int(int* x, int* y);
void _swap_float(float* x, float* y);

#define swap(x, y) _Generic((x), \
	int*:    _swap_int,			 \
	float*:  _swap_float		 \
	double*: _swap_double		 \
)(x, y)

int swap_endian(int hex);
void logger(const char* const s, const int log_level);

#endif
