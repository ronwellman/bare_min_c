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
destroyQueue(queue_t *q) {
    if (NULL == q) {
        return false;
    }

    if (NULL == q->head) {
        free(q);
        return true;
    }

    struct node *head = q->head;
    struct node *next = head->next;

    while(NULL != head) {
        free(head);
        head = next;
        if (NULL != next) {
            next = next->next;
        }
    }
    q->head = NULL;
    q->tail = NULL;

    return true;
}

bool
enqueue(queue_t *q, void *op) {
    if (NULL == q) {
        return false;
    }

    struct node *newNode = (struct node *)calloc(1, sizeof(*newNode));

    if (NULL == newNode) {
        perror("Unable to allocate for new node.");
        return false;
    }
    
    newNode->op = op;

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

    void *op = q->head->op;
    struct node *temp = q->head->next;
    free(q->head);
    q->head = temp;
    if (NULL == q->head) {
        q->tail = NULL;
    }
    return op;
}
