#include <stdbool.h>
#include <stdlib.h>
#include "09-stack.h"

stack_t *
createStack(size_t maxSize) {
    stack_t *newStack = malloc(sizeof(*newStack));
    newStack->maxSize = maxSize;
    newStack->curSize = 0;
    newStack->items = malloc(maxSize * sizeof(*(newStack->items)));
    return newStack;
}

bool
push(stack_t *stack, void *data) {
    if (NULL == stack || stack->curSize == stack->maxSize) {
        return false;
    }
    stack->items[stack->curSize] = data; 
    stack->curSize++;
    return true;
}

void *
pop(stack_t *stack) {
    if (NULL == stack || 0 == stack->curSize) {
        return NULL;
    }
    
    stack->curSize--;
    return stack->items[stack->curSize];
}

bool
stackFull(stack_t *stack) {
	if (NULL == stack || stack->curSize == stack->maxSize) {
		return true;
	}
	return false;
}

bool
destroy(stack_t **stack, void(freeData)(void *)) {
    if (NULL == stack || NULL == *stack) {
        return false;
    }

    for (size_t i = 0; i < (*stack)->curSize; i++) {
        freeData((*stack)->items[i]);
    }

    free((*stack)->items);
    free(*stack);
    return true;
}

