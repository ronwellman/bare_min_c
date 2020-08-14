#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "07-queue.h"

#define ITEMS 10
#define THREADCNT 5
#define UNUSED(x) (void)(x)

queue_t *q;
mtx_t qMtx;

static int
doWork(void *);

int
main() {
	int returnCode = 0;
	int result; 
	thrd_t *threads = NULL;
	char work[ITEMS][2] = {"A","B","C","D","E","F","G","H","I","J"};

		/* create and initialize mutex */
		mtx_t qMtx = { 0 };
		if (thrd_success != mtx_init(&qMtx, mtx_plain )) {
			fprintf(stderr, "Unable to initialize queue mutex.");
			returnCode = 1;
			goto exitNow;
		}

	/* add work to a queue */
	q = createQueue();
	printf("Enqueu work.\n");
	for (int i = 0; i < ITEMS; i++) {
		result = mtx_lock(&qMtx);
		if (thrd_success == result) {
			enqueue(q, (void *)work[i]);
			mtx_unlock(&qMtx);
		}
	}

	/* create threads to begin work */
	threads = malloc(THREADCNT *  sizeof(*threads));
	for (int i = 0; i < THREADCNT; i++) {
		printf("Creating Threads.\n");
		if (thrd_success != thrd_create(&threads[i], doWork, NULL)) {
			fprintf(stderr, "Unable to create thread.\n");
			returnCode = 1;
			goto exitNow;
		}
	}

	/* wait for threads to exit */
	for (int i = 0; i < THREADCNT; i++) {
		thrd_join(threads[i], &result);
		printf("Thread %d joined with result: %d\n", i, result);
	}

exitNow:
	destroyQueue(q);
	mtx_destroy(&qMtx);
	free(threads);
	return returnCode;
}

static int
doWork(void *nothing) {
	UNUSED(nothing);
	int result;
	void *job;
	
	/* ID thread */
	thrd_t thisThread = thrd_current();
	for(;;) {
		result = mtx_lock(&qMtx);
		if (thrd_success == result) {
			job = dequeue(q);
			mtx_unlock(&qMtx);
			if (NULL != job) {
				/* perform work */
				thrd_yield();
				printf("%lu: dequeue: %s\n", thisThread, (char *)job);
			} else {
				printf("%lu: No work.\n", thisThread);
				break;
			}
		}
	}
	/* return 0 */
	thrd_exit(0);
}
