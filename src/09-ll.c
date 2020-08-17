#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "09-ll.h"

ll_t *
createList() {
	ll_t *list = calloc(1, sizeof(*list));
	return list;
}

bool
destroyList(ll_t **list, void(*destroyData)(void *)) {
	if (NULL == list) {
		return false;
	}

	node_t *temp = (*list)->head;
	node_t *next;
	while (NULL != temp) {
		next = temp->next;
		destroyData(temp->data);
		free(temp);
		temp = next;
	}

	free(*list);
	list = NULL;

	return true;
}

bool
addNode(ll_t *list, void *data) {
	if (NULL == list) {
		return false;
	}

	node_t *node = malloc(sizeof(*node));
	if (NULL == node) {
		fprintf(stderr, "Unable to allocate for new node.\n");
		return false;
	}

	node->next = NULL;
	node->data = data;

	/* no current head */
	if (NULL == list->head) {
		list->head = node;
		return true;
	}

	/* replace the head */
	node->next = list->head;
	list->head = node;
	return true;
}

void *
removeNode(ll_t *list, void *searchData, bool(*compare)(void *, void *)) {
    if (NULL == list || NULL == list->head) {
        return NULL;
    }

    node_t *temp = list->head;
    node_t *prev = temp;
    void *rData;
    bool result;
    
    /* matched node is the head */
    if (true == (result = compare(temp->data, searchData))) {
        list->head = temp->next;
        rData = temp->data;
        free(temp);
        return rData;
    }
    
    /* search through the remainder of the list */
    temp = temp->next;
    while (NULL != temp) {
       if (true == (result = compare(temp->data, searchData))) {
            prev->next = temp->next;
            rData = temp->data;
            free(temp);
            return rData;
        } 
       prev = temp;
       temp = temp->next;
    }

    /* no match */
    return NULL;
}

void
printList(ll_t *list, void(*printList)(void *)) {
    if (NULL == list || NULL == list->head) {
        return;
    }

    node_t *temp = list->head;
    while (NULL != temp) {
        printList(temp->data);
        temp = temp->next;
    }
}


