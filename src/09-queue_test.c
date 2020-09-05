#define _POSIX_C_SOURCE  200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "09-queue.h"

struct bottle {
	char *msg;
	char author[24];
};

struct bottle *
newMessage(void);

void
printMessage(void *);

void
destroyMessage(void *);

int
main() {
	void *msg;
	void(*dm)(void *) = &destroyMessage;

	/* create queue */
	queue_t *q = createQueue();
	
	/* add items */
	printf("Enqueue:\n");
	enqueue(q, (void *)newMessage());
	enqueue(q, (void *)newMessage());
	enqueue(q, (void *)newMessage());

	/* remove items */
	printf("Dequeue:\n");
	for (int i = 0; i < 4; i++) {
		msg = dequeue(q);
		printMessage(msg);
		destroyMessage(msg);
	}

	/* item another item */
	printf("Enqueue:\n");
	enqueue(q, (void *)newMessage());
    
    /* destroy the queue */
	printf("Destroy:\n");
	destroyQueue(&q, dm);
	destroyQueue(&q, dm);
}

struct bottle *
newMessage(void) {
	struct bottle *b = calloc(1, sizeof(*b));
	size_t readSize = 0;
	if (NULL == b) {
		fprintf(stderr, "Unable to allocate for bottle.\n");
		return NULL;
	}

	printf("Message to send: ");
	ssize_t bytes = getline(&(b->msg), &readSize, stdin);
	if (-1 == bytes) {
		fprintf(stderr, "Unable to get input.\n");
		free(b->msg);
		free(b);
		return NULL;
	}
	if ('\n' == b->msg[bytes - 1]) {
		b->msg[bytes - 1] = 0;
	}
	strncpy(b->author, "Rick Astley", 23);
	return b;
}

void
destroyMessage(void *b) {
	if (NULL == b) {
		return;
	}
	free(((struct bottle *)b)->msg);
	free(b);
}

void
printMessage(void *b) {
	if (NULL == b) {
		return;
	}
	printf("%s: %s\n", ((struct bottle *)b)->author, ((struct bottle *)b)->msg);
}
