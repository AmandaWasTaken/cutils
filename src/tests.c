#include <stdio.h>
#include <cutils.h>
#include <stdlib.h>

int main(int argc, char** argv){

	int x = 10;
	int y = 20;
	logger("Before swap:", LOGGER_LOG);
	printf("%i %i\n", x, y);
	swap(&x, &y, OP_INT);
	logger("After swap:", LOGGER_LOG);
	printf("%i %i\n", x, y);


    return 0;
}
