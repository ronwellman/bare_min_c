#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define BUFFERSIZE 32

int
main() {
	int sockFD, remoteFD;
	int result;
	char address[INET_ADDRSTRLEN + 1] = { 0 };
	char recvBuf[BUFFERSIZE] = { 0 };
	const char *temp;

	ssize_t bytes;
	struct sockaddr_in addr = { 0 };
	struct sockaddr_in remote = { 0 };
	socklen_t remoteSize = sizeof(remote);
	
	/* create a socket */
	sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sockFD) {
		fprintf(stderr, "Unable to create socket.\n");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	
	/* allow for address reuse, great for testing */
	int reuse = 1;
	result = setsockopt(sockFD, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if (0 != result) {
		fprintf(stderr, "Unable to set socket option for address reuse.");
	}

	/* bind the socket */
	result = bind(sockFD, (struct sockaddr *)&addr, sizeof(addr));
	if (0 != result) {
		fprintf(stderr, "Unable to bind.\n");
		goto exitNow;
	}

	/* listen for incoming connections */
	result = listen(sockFD, 1);
	if (0 != result){
		fprintf(stderr, "Unable to listen.\n");
		goto exitNow;
	}

	/* accept connection */
	remoteFD = accept(sockFD, (struct sockaddr *)&remote, &remoteSize);
	if (-1 == remoteFD) {
		fprintf(stderr, "Accept error.\n");
		goto exitNow;
	}

	temp = inet_ntop(AF_INET, (void *)&(remote.sin_addr), address,
			INET_ADDRSTRLEN);
	if (NULL == temp) {
		fprintf(stderr, "Unable to convert address.\n");
	} else {
		int port = ntohs(remote.sin_port);
		printf("Accepted a connection from: %s:%d\n", address, port);
	}

	for (;;) {
		bytes = send(remoteFD, "Marco\n", 6, 0);
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

		if ((result = strncmp("Polo", recvBuf, 4)) != 0) {
			break;
		}
	}
	close(remoteFD);

exitNow:
	close(sockFD);
	return 0;
}
