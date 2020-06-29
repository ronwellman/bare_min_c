#include <stdio.h>

int
main() {
    short int si;
    int i;
    unsigned int ui;
    long int li;
    long long int lli;

    si = -275;
    
    printf("Number of Bytes:\nshort int: %d\nint: %d\n",
            sizeof(si), sizeof(i));

    printf("long int: %d\nlong long int: %d\n",
            sizeof(li), sizeof(lli));

    printf("\n");
    printf("Value of signed   short: %d\n", si);
    printf("Value of unsigned short: %u\n", (unsigned short)si);
    
    printf("\n");
    i = 0x80000000; // 0b10000000000000000000000000000000
    printf("Min signed int: %d\n", i);
    i = 0x7fffffff; // 0b01111111111111111111111111111111
    printf("Max signed int: %d\n", i);

    printf("\n");
    ui = 0;         // 0b00000000000000000000000000000000
    printf("Min unsigned int: %u\n", ui);
    ui = 0xffffffff;// 0b11111111111111111111111111111111
    printf("Max unsigned int: %u\n", ui);

    return 0;
}
