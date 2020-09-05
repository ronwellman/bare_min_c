#define _POSIX_C_SOURCE  200809L
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "09-stack.h"
#define MAXSIZE 3
#define ITEMSIZE 20
#define UNUSED(x) (void)(x)

static char *
getItem(void);

static void
freeData(void *);

int
main() {
	void (*fd)(void *) = &freeData;
    
	printf("Creating stack with maxsize: %d\n", MAXSIZE);
    stack_t *stack = createStack(MAXSIZE);
    if (NULL == stack) {
        fprintf(stderr, "Stack not allocated.\n");
        return 1;
    }
    
    printf("\nPushing onto stack:\n");
	bool result;
	char *msg;
    for (int i = 0; i < MAXSIZE + 1; i++) {
		msg = getItem();
		result = push(stack, (void *)msg);
		if (false == result) {
			freeData(msg);
		}
		printf("Stack full: %s\n", stackFull(stack) ? "true" : "false");
	}
 	

    printf("\nPopping from stack.\n");
    void *item; 
	for (int i = 0; i < MAXSIZE + 1; i++) {
		item = pop(stack);
    	printf("%s\n", NULL != item ? (char *)item : "NULL");
		freeData(item);
	}

    printf("\nPushing more items onto stack.\n");
    msg = getItem();
	result = push(stack, (void *)msg);
	if (false == result) {
		freeData(msg);
	}
	printf("Stack full: %s\n", stackFull(stack) ? "true" : "false");
    
    printf("\nDestroying stack.\n");
    destroyStack(&stack, fd);
    destroyStack(&stack, fd);

    return 0;
}

static char *
getItem() {
	char *msg = NULL;
	size_t readSize = 0;

	printf("Message to send: ");
	ssize_t bytes = getline(&msg, &readSize, stdin);
	if (-1 == bytes) {
		free(msg);
		return NULL;
	}

	if ('\n' == msg[bytes - 1]) {
		msg[bytes-1] = 0;
	}
	return msg;
}


static void
freeData(void *data) {
    free(data);
}
