#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <errno.h>

static void
usage(FILE *, char *);

typedef enum {
	ORIGINALCASE,
	LOWERCASE,
	UPPERCASE
}case_t;

int
main(int argc, char **argv) {

	case_t ul = ORIGINALCASE;
	char *endptr;
	long repeat = 1;

	int opt;
	while ((opt = getopt(argc, argv, "hulr:")) != -1) {
		switch (opt) {
			case 'u':
				ul = UPPERCASE;
				break;
			case 'l':
				ul = LOWERCASE;
				break;
			case 'r':
				repeat = strtol(optarg, &endptr, 10);
				if ((errno == ERANGE && (repeat == LONG_MAX || repeat == LONG_MIN))
				   	|| (errno != 0 && repeat == 0) || (*endptr != '\0')
				   	|| (repeat <= 0)) {
			   		fprintf(stderr, "Invalid numeric value for '-r'.\n");
					usage(stderr, argv[0]);
			   		exit(EXIT_FAILURE);
		   		}
				break;
			case 'h':
				usage(stdout, argv[0]);
				exit(EXIT_SUCCESS);
			default: /* '?' */
				usage(stderr, argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	// Test to make sure only one string was passed in
	if ((argc == optind) || (argc > (optind + 1))) {
		fprintf(stderr, "Invalid number of args.\n");
		usage(stderr, argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("Name: %s argc:%d optind:%d case:%d repeat:%ld\n",
		argv[optind],
		argc,
		optind,
		ul,
		repeat);

	return 0;
}

static void
usage(FILE *fptr, char *program) {
	fprintf(fptr, "Usage: %s [-r CNT] [-u] [-l] name\n",
			program);
	fprintf(fptr, "\t-r\tRepeat Count\n");
	fprintf(fptr, "\t-u\tUppercase\n");
	fprintf(fptr, "\t-l\tLowercase\n");
}