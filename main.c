/* Basic implementation of AES in C
 *
 * Warning: THIS CODE IS ONLY FOR LEARNING PURPOSES
 *          NOT RECOMMENDED TO USE IT IN ANY PRODUCTS
 */

#include <stdio.h>  // for printf
#include <stdlib.h> // for malloc, free
#include "raihan.h"
#include "dhira.h"

int main(int argc, char *argv[])
{
    // the expanded keySize
    int expandedKeySize = 176;

    // the expanded key
    unsigned char expandedKey[expandedKeySize];

    // the cipher key
    unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};

    // the cipher key size
    enum keySize size = SIZE_16;

    // the plaintext
    unsigned char plaintext[16] = {'a', 'b', 'c', 'd', 'e', 'f', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    // the ciphertext
    unsigned char ciphertext[16];

    // the decrypted text
    unsigned char decryptedtext[16];

    int i;

    printf("**************************************************\n");
    printf("*   Basic implementation of AES algorithm in C   *\n");
    printf("**************************************************\n");

    printf("\nCipher Key (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        // Print characters in HEX format, 16 chars per line
        printf("%2.2x%c", key[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    // Test the Key Expansion
    expandKey(expandedKey, key, size, expandedKeySize);

    printf("\nExpanded Key (HEX format):\n");

    for (i = 0; i < expandedKeySize; i++)
    {
        printf("%2.2x%c", expandedKey[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    printf("\nPlaintext (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", plaintext[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    // AES Encryption
    aes_encrypt(plaintext, ciphertext, key, SIZE_16);

    printf("\nCiphertext (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", ciphertext[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    // AES Decryption
    aes_decrypt(ciphertext, decryptedtext, key, SIZE_16);

    printf("\nDecrypted text (HEX format):\n");

    for (i = 0; i < 16; i++)
    {
        printf("%2.2x%c", decryptedtext[i], ((i + 1) % 16) ? ' ' : '\n');
    }

    return 0;
}
