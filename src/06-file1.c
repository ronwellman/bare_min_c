#include <stdio.h>
#define BUFSIZE 256

int
main() {
    // open the file
    char pathname[] = "../sample/file1";
    FILE *fp = fopen(pathname, "r");
    if (NULL == fp) {
        fprintf(stderr, "Error opening file: %s\n", pathname);
        return 1;
    }
    
    // establish a buffer
    char buffer[BUFSIZE] = { 0 };
    char *temp = NULL;

    // read from the file
    while ((temp = fgets(buffer, BUFSIZE, fp)) != NULL) {
        printf("%s", buffer);
    }

    // close the file
    int result = fclose(fp);
    if (0 != result) {
        fprintf(stderr, "Error closing file: %s\n", pathname);
        return 1;
    }
    
    return 0;
}
