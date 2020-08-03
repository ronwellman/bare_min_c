#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int
main() {
	const char *pathname = "../sample/file1";
	int result;
	struct stat statbuf = { 0 };

	// fill stat struct
	result = stat(pathname, &statbuf);
	if (-1 == result) {
		fprintf(stderr, "Could not run stat on: %s\n", pathname);
		return 1;
	}

	printf("Pathname:                   %s\n", pathname);
	printf("Is the file a regular file: %s\n",
	S_ISREG(statbuf.st_mode) ? "true" : "false");
	printf("Is the file a directory:    %s\n",
	S_ISDIR(statbuf.st_mode) ? "true" : "false");
	printf("User ID of owner:           %d\n", statbuf.st_uid);
	printf("Group ID of group owner:    %d\n", statbuf.st_gid);
	printf("Size of file:               %ld bytes\n", statbuf.st_size);
	printf("Last status change:         %s", ctime(&statbuf.st_ctime));
	printf("Last file access:           %s", ctime(&statbuf.st_atime));
	printf("Last file modification:     %s", ctime(&statbuf.st_mtime));

	return 0;
}
