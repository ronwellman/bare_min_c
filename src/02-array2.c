#include <stdio.h>

#define STUDENTCNT 2
#define TESTCNT 3

int
main () {

    char students[STUDENTCNT][5] = { "Jenny", "Jimmy" };
    float grades[STUDENTCNT][TESTCNT] = { 0 };
    printf("Grades consumes %lu bytes of memory.\n", sizeof(grades));

    for(unsigned int student = 0; student < STUDENTCNT; student++) {
        for (unsigned int test = 0; test < TESTCNT; test++) {
            printf("Student %s\tTest: %u\tGrade: %f\n",
                    students[student], test, grades[student][test]);
        }
    }
    return 0;
}
