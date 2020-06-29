#include <stdio.h>
#include <ctype.h>

int
main() {

    char c1 = 'a';
    char c2 = toupper(c1);
    
    printf("The character '%c' has the value %d\n", c1, c1);
    printf("The character '%c' has the value %d\n", c2, c2);
   
    printf("\n");
    if (0 != isalpha(c1)) {
        printf("%c - alphabetic character.\n", c1);
    } 
    else {
        printf("%c - not an alphabetic character.\n", c1);
    }

    printf("%c - %s character.\n", c1, 
            isdigit(c1) ? "numeric" : "not a numeric");

    return 0;
}
