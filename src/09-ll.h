#ifndef LL_H
#define LL_H
#include <stdbool.h>

typedef struct node {
	struct node *next;
	void *data;
} node_t;

typedef struct ll {
	unsigned int numNodes;
	node_t *head;
} ll_t;

ll_t *
createList();

bool
destroyList(ll_t **, void(*)(void *));

bool
addNode(ll_t *, void *data);

void *
removeNode(ll_t *, void *data, bool(*)(void*, void*));

void
printList(ll_t *, void(*)(void *));

#endif
