#include <stdio.h>

static void
anotherFunc(const char *);

int
main() {
	char msg[16] = {"Say something"};
	anotherFunc(msg);
	return 0;
}

static void
anotherFunc(const char *saying) {
	printf("Received: %s\n", saying);
}
