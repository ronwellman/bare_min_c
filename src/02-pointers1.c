#include <stdio.h>
#include <stdbool.h>

void
sort(int *, size_t);

void
swap(int *, int *);

void
printArray(int *, size_t);

int
main() {
	int numbers[] = { 1, 9, 7, 15, 42, 18, 12 };

	const size_t numElements = sizeof(numbers) / sizeof(int);

	printArray(numbers, numElements);

	sort(numbers, numElements);

	printArray(numbers, numElements);

	return 0;
}

void
sort(int *pArray, size_t numElements) {
	if ((NULL == pArray) || (0 == numElements)) {
		return;
	}

	bool complete = false;
	while (false == complete) {
		complete = true;
		for (size_t i = 0; i < (numElements - 1); i++) {
			if (pArray[i] > pArray[i+1]) {
				complete = false;
				swap(pArray + i, pArray + i + 1);
			}
		}
	}
}

void
swap(int *p1, int *p2) {
	if ((NULL == p1) || (NULL == p2)) {
		return;
	}

	int temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void
printArray(int *pArray, size_t numElements) {
	if (NULL == pArray) {
		return;
	}

	for (size_t i = 0; i < numElements; i++) {
		printf("%d ", pArray[i]);
	}
	printf("\b\n");
}
