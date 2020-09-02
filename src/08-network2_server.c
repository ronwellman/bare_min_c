#define _POSIX_C_SOURCE 200112L
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFFERSIZE 8

static void
handleConnection(int);

static void
sigHandler(int sig);

bool keepRepeating = true;

int
main() {
	int sockFD;
	int result;
	int returncode = 0;
	struct addrinfo hints = { 0 };
	struct addrinfo *res = NULL;
	struct addrinfo *adapter = NULL;

	/* setup sigaction handling */
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sigHandler;
	sa.sa_flags = 0;
	if(sigaction(SIGINT, &sa, 0) != 0) {
		fprintf(stderr, "Sigaction failure.");
		return -1;
	}

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	/* generate addrinfo structs based on hits */
	result = getaddrinfo(NULL, "8888", &hints, &res);
	if (0 != result) {
		fprintf(stderr, "Unable to get address info.\n");
		returncode = -1;
		goto exitNow;
	}

	/* loop through the addresses attempting to bind */
	for (adapter = res; NULL != adapter; adapter = adapter->ai_next) {
        /* create the socket */
		sockFD = socket(adapter->ai_family, adapter->ai_socktype,
				adapter->ai_protocol);
        if (-1 == sockFD) {
            continue;
        }
		
		/* allow for address reuse, great for testing */
		int reuse = 1;
		result = setsockopt(sockFD, SOL_SOCKET, SO_REUSEADDR, &reuse,
				sizeof(reuse));
		if (0 != result) {
			fprintf(stderr, "Unable to set socket option for address reuse.");
		}

		/* bind the socket */
		result = bind(sockFD, adapter->ai_addr, adapter->ai_addrlen);
		if (0 != result) {
			close(sockFD);
			continue;
		}
		break;
    }

	/* listen for incoming connections */
	result = listen(sockFD, 64);
	if (0 != result){
		fprintf(stderr, "Unable to listen.\n");
		returncode = -1;
		goto exitNow;
	}
	
	int remoteFD;
	pid_t pid;
	struct sockaddr_in remote = { 0 };
	socklen_t remoteSize = sizeof(remote);

	printf("Hit <CTRL+C> to stop server.\n");
	for (;;) {
		/* accept connection */
		remoteFD = accept(sockFD, (struct sockaddr *)&remote, &remoteSize);
		if (-1 == remoteFD) {
			/* EINTR is most likely from <CTRL+C> */
			if (EINTR == errno) {
				printf("Shutting down...\n");
			} else {
				fprintf(stderr, "Accept error.\n");
			}
			break;
		}
		
		/* fork connection */
		pid = fork();
		if (0 == pid) {
			/* child closes socket it doesn't require */
			close(sockFD);
			handleConnection(remoteFD);
			break;
		} else {
			/* parent closes socket it doesn't require */
			close(remoteFD);
		}
	}
	
	close(sockFD);
exitNow:
	/* free addrinfo struct */
	freeaddrinfo(res);
	return returncode;
}

static void
handleConnection(int remoteFD) {
	char recvBuf[BUFFERSIZE] = { 0 };
	int result;
	ssize_t bytes;

	/* send and receive */
	for (;keepRepeating;) {
		bytes = send(remoteFD, "ping\n", 6, 0);
		if (-1 == bytes) {
			fprintf(stderr, "Unable to send.\n");
			break;
		}

		bytes = recv(remoteFD, recvBuf, BUFFERSIZE -1, 0);
		if (-1 == bytes) {
			fprintf(stderr, "Error receiving.\n");
			break;
		} else if (0 == bytes) {
			printf("Remote closed connection.\n");
			break;
		}

		if ((result = strncmp("pong", recvBuf, 4)) != 0) {
			break;
		}
	}

	close(remoteFD);
}

static void
sigHandler(int sig) {
	if (sig == SIGINT) {
		keepRepeating = false;
	}
}

