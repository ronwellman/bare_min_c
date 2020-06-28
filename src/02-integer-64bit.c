#include <stdio.h>

int
main() {
    short int si;
    int i;
    long int li;

    printf("Sizes:\nshort int: %ld\nint: %ld\nlong int: %ld\n",
            sizeof(si), sizeof(i), sizeof(li));
    return 0;
}
