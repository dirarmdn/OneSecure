#ifndef AES_H
#define AES_H

// Define AES Key Sizes
#define AES_128_KEY_SIZE 16
#define AES_192_KEY_SIZE 24
#define AES_256_KEY_SIZE 32

// Define AES Block Size
#define AES_BLOCK_SIZE 16

// Define Operation Mode
typedef enum {
    ECB,
    CBC,
    CTR,
} AES_MODE;

// Define AES Key Structures
typedef struct {
    int size;               // size of the key in bytes
    unsigned char *data;    // pointer to the key data
} AESKey;

// Define AES Context Structure
typedef struct {
    AESKey key;                         // encrypt/decrypt key
    unsigned char iv[AES_BLOCK_SIZE];   // initialization vector
    AES_MODE mode;                      // operation mode
} AESContext;

// Function Prototypes
void aes_init(AESContext *ctx, unsigned char *key, int key_size, unsigned char *iv, AES_MODE mode);
void aes_encrypt(AESContext *ctx, unsigned char *input, unsigned char *output, int length);
void aes_decrypt(AESContext *ctx, unsigned char *input, unsigned char *output, int length);

// AES Core Functions
void AddRoundKey(unsigned char state[AES_BLOCK_SIZE], unsigned char *roundKey);
void SubBytes(unsigned char state[AES_BLOCK_SIZE]);
void ShiftRows(unsigned char state[AES_BLOCK_SIZE]);
void MixColumns(unsigned char state[AES_BLOCK_SIZE]);

// Additional AES Functions
void KeyExpansion(unsigned char *key, AESKey *roundKeys, int keySize);
void ExpandRoundKey(unsigned char *key, unsigned char *roundKey, int round);
void InvShiftRows(unsigned char state[AES_BLOCK_SIZE]);
void InvSubBytes(unsigned char state[AES_BLOCK_SIZE]);
void InvMixColumns(unsigned char state[AES_BLOCK_SIZE]);

#endif