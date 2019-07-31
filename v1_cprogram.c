#include "stdio.h"
#include "stdlib.h"

void testFunction(void* variable) {
	
	int *value = (int*)variable;
	
	if (*value != 2) {
		*value = 10;
		variable = &value;
	}

}

int main(int argc, char *argv[]) {

	int value = 4;
	
	testFunction(&value);

	printf("this is the new value %d\n", value);
}
