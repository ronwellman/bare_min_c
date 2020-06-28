#include <stdio.h>

int
main() {
    short int si;
    int i;
    long int li;

    si = -275;
    
    printf("Sizes:\nshort int: %d\nint: %d\nlong int: %d\n",
            sizeof(si), sizeof(i), sizeof(li));

    printf("Value of signed   short: %d\n", si);
    printf("Value of unsigned short: %u\n", (unsigned short)si);
    
    return 0;
}
