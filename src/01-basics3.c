#include <stdio.h>
#include "01-helper.h"

int
main() {
	MYSTERYMEMBER member = SHAGGY;

	printf("I get %d scooby snacks!\n", distributeSnacks(member));
	return 0;
}
