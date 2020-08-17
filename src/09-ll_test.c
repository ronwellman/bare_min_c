#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "09-ll.h"

#define UNUSED(x) (void)(x)

struct student {
    int grade;
    int studentID;
    char name[20];
};

void
destroyData(void *);

bool
compareData(void *, void*);

void
print(void *);

int
main() {
    /* function pointers */
    void(*dd)(void *) = &destroyData;
    bool(*cmp)(void *, void *) = &compareData;
    void(*pl)(void *) = &print;
    struct student s1 = {85, 1, "Jimmy"}; 
    struct student s2 = {76, 2, "Joseph"}; 
    struct student s3 = {101, 3, "Julie"}; 
    struct student s4 = {101, 4, "Timmy"}; 
    ll_t *list = createList();
    printf("Adding nodes.\n");
    addNode(list, (void *)&s1);
    addNode(list, (void *)&s2);
    addNode(list, (void *)&s3);
    addNode(list, (void *)&s4);
    printList(list, pl);

    printf("\nRemoving Nodes:\n");
    int studentID = 2;
    print(removeNode(list, (void *)&studentID, cmp));
    studentID = 4;
    print(removeNode(list, (void *)&studentID, cmp));
    studentID = 1;
    print(removeNode(list, (void *)&studentID, cmp));
    studentID = 3;
    print(removeNode(list, (void *)&studentID, cmp));
    studentID = 5;
    print(removeNode(list, (void *)&studentID, cmp));
   
    printf("\nAdd Node.\n");
    addNode(list, (void *)&s2);
    printList(list, pl);

    printf("\nDestroy list.\n");
    destroyList(&list, dd);
    return 0;
}

void
destroyData(void *data) {
   UNUSED(data);
}

bool
compareData(void *d1, void *d2) {
    struct student s = *(struct student *)d1;
    
    return s.studentID == *(int *)d2;
}

void
print(void *data) {
    if (NULL == data) {
        printf("NULL\n");
        return;
    }
    struct student s = *(struct student *)data;
    printf("%s: %d\n", s.name, s.grade);
}
