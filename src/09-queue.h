#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

/*
 * Dequeue                        Enqueue
 *   |                              |
 *   |  head       tail             |
 *   -> node->next node->next NULL <-
 */

typedef struct node {
	void *data;
	struct node *next;
} node_t;

typedef struct queue {
	struct node * head;
	struct node * tail;    
} queue_t;

queue_t *
createQueue(void);

bool
destroyQueue(queue_t **, void(*)(void *));

bool
enqueue(queue_t *, void *);

void *
dequeue(queue_t *);

#endif
