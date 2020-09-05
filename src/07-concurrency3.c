#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include "09-queue.h"

#define UNUSED(x) (void)(x)
#define NUMTHREADS 8
#define NUMLISTS 10
#define NUMITEMS 20

static bool processJobs = true;
static queue_t *q;
static pthread_mutex_t mtxJobs = { 0 };
static pthread_mutex_t mtxQ = { 0 };
static pthread_cond_t condJobs = { 0 };

void *
doWork(void *);

void
destroyJob(void *);

int
main() {
	int retVal = 0;
	int result;
	void(*dj)(void *) = destroyJob;
	time_t clock;
	time(&clock);
	srandom(clock);

	/* create jobs queue */
	q = createQueue();

	/* set up mutexes */
	pthread_mutex_init(&mtxJobs, NULL);
	pthread_mutex_init(&mtxQ, NULL);

	/* set up a condition variable */
	pthread_cond_init(&condJobs, NULL);

	/* create threads */
	pthread_t threads[NUMTHREADS] = { 0 };
	for (int i = 0; i < NUMTHREADS; i++) {
		result = pthread_create(&(threads[i]), NULL, doWork, NULL);
		if (result != 0) {
			fprintf(stderr, "Unable to create thread.\n");
			retVal = result;
			goto exitNow;
		}
	}

	/* give the threads time to get set */
	sleep(2);

	long jobs[NUMLISTS][NUMITEMS];
	for (int l = 0; l < NUMLISTS; l++) {
		/* create list of random numbers */
		for (int i = 0; i < NUMITEMS; i++) {
			jobs[l][i] = random() % 1000;
		}
		
		result = pthread_mutex_lock(&mtxQ);
		if (0 != result) {
			continue;
		}

		result = enqueue(q, jobs[l]);
		pthread_mutex_unlock(&mtxQ);
		if (result != true) {
			fprintf(stderr, "Unable to enqueue list.\n");
		} else {
			printf("Enqueing and signaling.\n");
			pthread_cond_signal(&condJobs);
		}
	}

	sleep(2);
	processJobs = false;
	printf("Send broadcast.\n");
	pthread_cond_broadcast(&condJobs);
	for (int i = 0; i < NUMTHREADS; i++) {
		printf("Joining %d.\n", i);
		pthread_join(threads[i], NULL);
	}

exitNow:
	destroyQueue(&q, dj);
	pthread_mutex_destroy(&mtxJobs);
	pthread_mutex_destroy(&mtxQ);
	pthread_cond_destroy(&condJobs);
	return retVal;
}

void *
doWork(void *nothing) {
	UNUSED(nothing);
	pthread_t pthreadID = pthread_self();
	int result;
	unsigned int cnt;

	while (true == processJobs) {

		/* lock job mutex */
		result = pthread_mutex_lock(&mtxJobs);
		if (0 != result) {
			fprintf(stderr, "Failure to gain lock.\n");
			pthread_exit(NULL);
		}
		if (false == processJobs) {
			break;
		}

		/* unlock job mutex and begin waiting on jobs condition variable */
		result = pthread_cond_wait(&condJobs, &mtxJobs);
		if (0 != result) {
			fprintf(stderr, "Failure to wait for condition variable.\n");
			pthread_exit(NULL);
		}

		/* unlock the job mutex again */	
		result = pthread_mutex_unlock(&mtxJobs);
		
		/* check the queue until empty */
		for (;;) {
			
			/* lock queue mutex */
			result = pthread_mutex_lock(&mtxQ);
			if (0 == result) {
				long *list = dequeue(q);
				
				/* unlock queue mutex */
				result = pthread_mutex_unlock(&mtxQ);
				
				if (NULL == list) {
					break;
				}
				
				cnt = 0;
				for (int i = 0; i < NUMITEMS; i++) {
					if (0 == list[i] % 2) {
						cnt++;
					}
				}
				printf("%ld - %d/%d items were even.\n", pthreadID, cnt, NUMITEMS);
			} else {
				/* lock failure */
				break;
			}
		}
	}
	pthread_exit(NULL);
}

void
destroyJob(void *job) {
	UNUSED(job);
}
