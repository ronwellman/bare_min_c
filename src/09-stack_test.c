#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "09-stack.h"
#define MAXSIZE 3
#define UNUSED(x) (void)(x)

void
freeData(void *);

int
main() {
    void (*ptrFreeData)(void *) = &freeData;
    printf("Createing stack with maxsize: %d\n", MAXSIZE);
    stack_t *stack = createStack(MAXSIZE);
    if (NULL == stack) {
        fprintf(stderr, "Stack not allocated.\n");
        return 1;
    }
    
    printf("\nPushing onto stack:\n");
    bool result = push(stack, (void *)"first item");
    printf("%s\n", result ? "success" : "fail");
    result = push(stack, (void *)"second item");
    printf("%s\n", result ? "success" : "fail");
    result = push(stack, (void *)"third item");
    printf("%s\n", result ? "success" : "fail");
    result = push(stack, (void *)"fourth item");
    printf("%s\n", result ? "success" : "fail");

 	printf("Stack full: %s\n", stackFull(stack) ? "true" : "false");

    printf("\nPopping from stack.\n");
    void *item = pop(stack);
    printf("%s\n", NULL != item ? (char *)item : "NULL");
    item = pop(stack);
    printf("%s\n", NULL != item ? (char *)item : "NULL");
    item = pop(stack);
    printf("%s\n", NULL != item ? (char *)item : "NULL");
    item = pop(stack);
    printf("%s\n", NULL != item ? (char *)item : "NULL");
    
 	printf("Stack full: %s\n", stackFull(stack) ? "true" : "false");

    printf("\nPushing more items onto stack.\n");
    result = push(stack, (void *)"another item");
    printf("%s\n", result ? "success" : "fail");
    
    printf("\nDestroying stack.\n");
    result = destroy(&stack, ptrFreeData);
    printf("%s\n", result ? "success" : "fail");

    return 0;
}

void
freeData(void *data) {
    UNUSED(data);
}
