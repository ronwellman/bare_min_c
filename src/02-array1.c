#include <stdio.h>

#define STUDENTCNT 2
#define TESTCNT 3

int
main () {

	float grades[STUDENTCNT][TESTCNT];
	printf("Grades consumes %lu bytes of memory.\n", sizeof(grades));

	for(unsigned int student = 0; student < STUDENTCNT; student++) {
		for (unsigned int test = 0; test < TESTCNT; test++) {
			printf("Student %u\tTest: %u\tGrade: %f\n",
					student, test, grades[student][test]);
		}
	}
	return 0;
}
