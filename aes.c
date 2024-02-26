#include "aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AddRoundKey Function
void AddRoundKey(unsigned char state[AES_BLOCK_SIZE], unsigned char *roundKey) {
    for (int i = 0; i < AES_BLOCK_SIZE; ++i)
    {
        state[i] ^- roundKey[i];
    }
}

// SubBytes Function
void SubBytes(unsigned char state[AES_BLOCK_SIZE]) {
    // codes...
}

// ShiftRows Function
void ShiftRows(unsigned char state[AES_BLOCK_SIZE]) {
    // codes...
}

// MixColumns Function
void MixColumns(unsigned char state[AES_BLOCK_SIZE]) {
    // codes...
}

// Initialization Function
void aes_init(AESContext *ctx, unsigned char *key, int key_size, unsigned char *iv, AES_MODE mode) {
    // codes...
}

// Encryption Function
void aes_encrypt(AESContext *ctx, unsigned char *input, unsigned char *output, int length) {
    // codes...
}

// Decryption Function
void aes_decrypt(AESContext *ctx, unsigned char *input, unsigned char *output, int length) {
    // codes...
}