#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/*
 * Dequeue                        Enqueue
 *   |                              |
 *   |  head       tail             |
 *   -> node->next node->next NULL <-
 */

struct node {
    void *op;
    struct node *next;
};

typedef struct queue {
    struct node * head;
    struct node * tail;    
} queue_t;

queue_t *
createQueue(void);

bool
destroyQueue(queue_t **);

bool
enqueue(queue_t *, void *);

void *
dequeue(queue_t *);

#endif
