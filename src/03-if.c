#include <stdio.h>

int
main() {
	unsigned proto = 17;

	if (6 == proto) {
		printf("TCP traffic detected...\n");
	}
	else if (17 == proto) {
		printf("UDP traffic detected...\n");
	}
	else {
		printf("Unknown protocol number detected...\n");
	}
	
	return 0;
}
