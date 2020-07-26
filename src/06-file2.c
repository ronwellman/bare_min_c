#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENTIDSIZE 16

typedef struct __attribute__ ((__packed__)) student {
    float grade;
    char studentID[STUDENTIDSIZE];
} student_t;

typedef struct __attribute__ ((__packed__)) class {
    unsigned int numStudents;
    student_t *students;
} class_t;

int
main() {
    int returnCode = 0;

    // create student grades
    class_t myClass = { 0 };
    myClass.numStudents = 2;
    myClass.students = malloc(sizeof(*(myClass.students)) * \
            myClass.numStudents);
    myClass.students[0].grade = 90.5;
    strncpy(myClass.students[0].studentID, "rwell123456", STUDENTIDSIZE);
    myClass.students[1].grade = 87.3;
    strncpy(myClass.students[1].studentID, "rdash246810", STUDENTIDSIZE);

    // open the file
    char pathname[] = "../sample/file2";
    FILE *fp = fopen(pathname, "w+b");
    if (NULL == fp) {
        fprintf(stderr, "Error opening file: %s\n", pathname);
        returnCode = 1;
        goto exitNow;
    }
   
    // save student grades to file
    size_t items = fwrite(&myClass, sizeof(myClass) - sizeof(myClass.students),
            1, fp);
    if (1 != items) {
        fprintf(stderr, "Something went wrong when writing to: %s\n", pathname);
        returnCode = 1;
        goto exitNow;
    }
    for (unsigned int i = 0; i < myClass.numStudents; i++) {
        items = fwrite(&(myClass.students[i]), sizeof(student_t), 1, fp);
        if (1 != items) {
            fprintf(stderr, "Something went wrong when writing to: %s\n",
                    pathname);
            returnCode = 1;
            goto exitNow;
        }
    }

    // clear out current class and students
    free(myClass.students);
    memset(&myClass, 0, sizeof(myClass));
    
    // flush the output buffer
    int result = fflush(fp);
    if (0 != result) {
        fprintf(stderr, "Unable to flush output buffer to: %s\n", pathname);
        returnCode = 1;
        goto exitNow;
    }

    // move to beginning of file
    result = fseek(fp, 0, SEEK_SET);
    if (0 != result) {
        fprintf(stderr, "Unable to move to beginning of file: %s\n", pathname);
        returnCode = 1;
        goto exitNow;
    }

    // read in the class
    items = fread(&myClass, sizeof(myClass) - sizeof(myClass.students), 1, fp);
    if (1 != items) {
        fprintf(stderr, "Something went wrong reading myClass from: %s\n", 
                pathname);
        returnCode = 1;
        goto exitNow;
    }

    // allocate for number of students indicated in file
    myClass.students = malloc(sizeof(*(myClass.students)) * \
            myClass.numStudents);
    
    // read in the students
    items = fread(&(myClass.students[0]), sizeof(student_t),
            myClass.numStudents, fp);
    if (myClass.numStudents != items) {
        fprintf(stderr, "Something went wrong reading students from: "\
                "%s\n", pathname);
        returnCode = 1;
        goto exitNow;
    }
    
    printf("Number of Students: %d\n", myClass.numStudents);
    for (unsigned int i = 0; i < myClass.numStudents; i++) {
        printf("\tStudent: %-18s Grade: %f\n", myClass.students[i].studentID,
                myClass.students[i].grade);
    }

exitNow:
    // close the file
    if (NULL != fp) {
        result = fclose(fp);
        if (0 != result) {
            fprintf(stderr, "Error closing file: %s\n", pathname);
            returnCode =  1;
        }
    }

    if (NULL != myClass.students) {
        free(myClass.students);
    }
    
    return returnCode;
}
