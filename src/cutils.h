#ifndef CUTILS_H
#define CUTILS_H

#include <stdlib.h>
#include <stdio.h>

static void _free_resource(void* p);
static void _close_file(FILE** f);

#define autofree  __attribute((cleanup(_free_resource)))
#define autoclose __attribute((cleanup(_close_file)))

static size_t _strlen(char* s);
static void _xorswap_int(int* x, int* y);
static void _swap_float(float* x, float* y);


int swap_endian(int byte);
void logger(const char* const s, const int log_level);
void swap(void* x, void* y, int operand);

#endif
