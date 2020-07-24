#include <stdio.h>

int
main() {
	float x;

	x = 1 / 3;
	printf("1 / 3 = %f\n", x);

	x = (float)1 / 3;
	printf("1 / 3 = %f\n", x);

	return 0;
}
