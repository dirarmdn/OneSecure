#ifndef AES_H
#define AES_H

#include <stdint.h>

#define NR 10  // Number of rounds for 128-bit key (adjust for other key lengths)

// AES State (4x4 matrix)
typedef struct {
    uint8_t state[4][4];
} AES_State;

// AES Key (128-bit key)
typedef struct {
    uint8_t key[16];
} AES_Key;

// Function to initialize AES state to all zeros
void aes_init(AES_State *state);

// Function to add round key to AES state
void aes_add_round_key(AES_State *state, const AES_Key *key);

// Function to perform AES substitution bytes operation
void aes_sub_bytes(AES_State *state);

// Function to perform AES shift rows operation
void aes_shift_rows(AES_State *state);

// Function to perform AES mix columns operation
void aes_mix_columns(AES_State *state);

// Function to perform AES encryption
void aes_encrypt(AES_State *state, const AES_Key *key);

// Function to perform AES decryption
void aes_decrypt(AES_State *state, const AES_Key *key);

// Function to multiply two numbers in GF(2^8) (used in MixColumns and InvMixColumns)
uint8_t aes_mul(uint8_t a, uint8_t b);

// Function to perform inverse shift rows operation
void aes_inv_shift_rows(AES_State *state);

// Function to perform inverse substitution bytes operation
void aes_inv_sub_bytes(AES_State *state);

// Function to perform inverse mix columns operation
void aes_inv_mix_columns(AES_State *state);

#endif /* AES_H */
