#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void
echo(const char *, const char *);

int
main() {
	const char *shared = "I am a shared string!";

	pid_t myPid;
	pid_t parentPid;
	pid_t newPid;

	myPid = getpid();
	parentPid = getppid();
	printf("Program begins with:\n\tPID: %d\n\tParentPid: %d\n",
			myPid, parentPid);

	newPid = fork();
	
	if (-1 == newPid) {
		/* error */
		perror("Unable to fork.");
	}
	else if (0 == newPid) {
		/* child */
		parentPid = getppid();
		printf("Child Process:\n\tPID: %d\n\tParentPid: %d\n",
				newPid, parentPid);
		echo("CHILD", shared);
	} 
	else {
		/* parent */
		printf("My Child's PID: %d\n", newPid);
		echo("PARENT", shared);
	}
}

void
echo(const char *name, const char *saying) {
	/* set timer */
	struct timespec tsReq, tsRem;
	tsReq.tv_sec = 0;
	tsReq.tv_nsec = 200000000;
	
	for (int i = 0; i < 5; i++) {
		printf("%s: %s\n", name, saying);
		nanosleep(&tsReq, &tsRem);
	}
}
