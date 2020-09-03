#include <stdio.h>
#include <stdlib.h>
#include "09-queue.h"

void
printQueue(queue_t *);

int
main() {
    queue_t *q = createQueue();
    void *op;

    enqueue(q, (void *)"first item");
    printQueue(q);
    enqueue(q, (void *)"second item");
    printQueue(q);
    enqueue(q, (void *)"third item");
    printQueue(q);
    op = dequeue(q);
    printf("Dequeue: %s\n", (char *)op);
    printQueue(q);
    op = dequeue(q);
    printf("Dequeue: %s\n", (char *)op);
    printQueue(q);
    op = dequeue(q);
    printf("Dequeue: %s\n", (char *)op);
    printQueue(q);
    op = dequeue(q);
    printf("Dequeue: %s\n", (char *)op);
    printQueue(q);
    enqueue(q, (void *)"fourth item");
    printQueue(q);
    
    destroyQueue(&q);
    printQueue(q);
    free(q);
}

void
printQueue(queue_t *q) {
    if (NULL == q) {
        return;
    }

    struct node *next = q->head;
    while (NULL != next) {
        printf("%s\n", (char *)next->op);
        next = next->next;
    }
}


