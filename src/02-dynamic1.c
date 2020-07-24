#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


bool
getInput(char **, FILE *);

int
main() {
	char *buffer = NULL;
	bool result;
	result = getInput(&buffer, stdin);
	printf("result: %d\n", result);
	printf("buffer: %s\n", buffer);

	free(buffer);
	return 0;
}

bool
getInput(char **buffer, FILE *fPtr) {
	if ((NULL == buffer) || (NULL != *buffer) || (NULL == fPtr)) {
		return false;
	}

	size_t blockSize = 16;
	size_t maxSize = blockSize;
	size_t actualSize = 0;

	// intially allocate a buffer to read into
	*buffer = (char *)malloc(maxSize * sizeof(char));
	if (NULL == *buffer) {
		fprintf(stderr, "Unable to initally allocate for buffer. %s:%d.\n", 
			__FILE__, __LINE__);
		return false;
	}

	// null terminate initial buffer
	*buffer[0] = '\0';
	char * temp;

	bool keepLooping = true;
	while (keepLooping) {

		// read into the buffer avoiding writing over existing characters
		temp = fgets(*buffer + actualSize, maxSize - actualSize, fPtr);
		if (NULL == temp) {
			fprintf(stderr, "Unable to read from file pointer. %s:%d\n", 
				__FILE__, __LINE__);
			return false;
		}

		// determine if the current buffer is full
		actualSize = strlen(*buffer);
		if (((maxSize - 1) == actualSize) && ((*buffer)[actualSize-1] != '\n' )) {
			maxSize += blockSize;
			printf("Realloc maxSize: %ld\n", maxSize);
			
			// perform a realloc based on the new maxSize
			temp = (char *)realloc(*buffer, maxSize * sizeof(char));
			if (NULL == temp) {
				fprintf(stderr, "Unable to realloc buffer to %ld bytes. %s:%d.\n", 
					maxSize, __FILE__, __LINE__);
				return false;
			}
			*buffer = temp;
		}
		else {
			keepLooping = false;
		}
	}

	return true;
}