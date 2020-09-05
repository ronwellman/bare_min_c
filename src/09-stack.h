#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct stack {
    size_t maxSize;
    size_t curSize;
    void **items;
} stack_t;

stack_t *
createStack(size_t);

bool
destroyStack(stack_t **, void(freeData)(void *));

bool
push(stack_t *, void *);

void *
pop(stack_t *);

bool
stackFull(stack_t *);

#endif
