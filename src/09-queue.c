#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "09-queue.h"

queue_t *
createQueue(void) {
	queue_t *newQueue = (queue_t *)calloc(1, sizeof(*newQueue));
	return newQueue;
}

bool
destroyQueue(queue_t **q, void(*destroyData)(void *)) {
	if (NULL == q || NULL == *q) {
		return false;
	}

    /* queue is empty */
	if (NULL == (*q)->head) {
		free(*q);
		*q = NULL;
		return true;
	}

	node_t *head = (*q)->head;
	node_t *next = head->next;

	while(NULL != head) {
		destroyData(head->data);
		free(head);
		head = next;
		if (NULL != next) {
			next = next->next;
		}
	}

	free(*q);
	*q = NULL;

	return true;
}

bool
enqueue(queue_t *q, void *data) {
	if (NULL == q) {
		return false;
	}

	node_t *newNode = (node_t *)calloc(1, sizeof(*newNode));
	if (NULL == newNode) {
		perror("Unable to allocate for new node.");
		return false;
	}

	newNode->data = data;
	if (NULL == q->tail) {
		q->tail = newNode;
		q->head = newNode;
	} else {
		q->tail->next = newNode;
		q->tail = newNode;
	}

	return true;
}

void *
dequeue(queue_t *q) {
	if (NULL == q || q->head == NULL) {
		return NULL;
	}

	void *data = q->head->data;
	node_t *temp = q->head->next;
	free(q->head);
	q->head = temp;
	
	if (NULL == q->head) {
		q->tail = NULL;
	}
	return data;
}
