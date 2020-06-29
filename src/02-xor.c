#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool
xor(char *original, size_t oLen, char *key, size_t kLen);

int
main() {
    // some character array and its length    
    char clear[] = "A sentence is made of words. " \
                    "Words are made of characters.";
    size_t clearLen = strlen(clear);

    // some key and its length
    char key[] = "X>P.X3/tMK{P\\:sr";
    size_t keyLen = strlen(key);

    printf("Original: %s\n", clear);
    
    xor(clear, clearLen, key, keyLen);

    printf("XOR'd: %s\n", clear);

    xor(clear, clearLen, key, keyLen);
    
    printf("Original: %s\n", clear);
    return 0;
}

bool
xor(char *original, size_t oLen, char *key, size_t kLen) {
    
    // quick check to see that we received a non-null array
    if (NULL == original || NULL == key || 0 == oLen || 0 == kLen) {
        return false;
    }

    // loop through each character xoring it with the key
    for (size_t i = 0; i < oLen; i++) {
        original[i] ^= key[i % kLen];
    }
    
    return true;
}


