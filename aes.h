#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <stddef.h>

// Data Type
typedef uint8_t byte;
typedef uint32_t word;

// Constant
#define AES_BLOCK_SIZE 16

// Size and Round Key
#ifdef AES128
#define AES_KEY_SIZE 16
#define AES_ROUNDS 10
#elif defined(AES192)
#define AES_KEY_SIZE 24
#define AES_ROUNDS 12
#elif defined(AES256)
#define AES_KEY_SIZE 32
#define AES_ROUNDS 14
#else
#error "Ukuran key tidak valid!"
#endif

// Operation Mode
typedef enum {
    AES_MODE_ECB,
    AES_MODE_CBC,
    AES_MODE_CTR,
} aes_mode_t;

// Data Structure
typedef struct {
    byte bytes[AES_BLOCK_SIZE];
} aes_state_t;

typedef struct {
    word words[AES_ROUNDS + 1];
} aes_round_key_t;

// Function Declaration
void aes_init_state(aes_state_t *state);
void aes_init_round_key(aes_round_key_t *round_key, const byte *key);
void aes_sub_bytes(aes_state_t *state);
void aes_shift_rows(aes_state_t *state);
void aes_mix_columns(aes_state_t *state);
void aes_add_round_key(aes_state_t *state, const aes_round_key_t *round_key);
void aes_encrypt_block(aes_state_t *state, const byte *input, byte *output);
void aes_decrypt_block(aes_state_t *state, const byte *input, byte *output);
void aes_encrypt(const byte *input, byte *output, size_t length, aes_mode_t mode, const byte *iv);
void aes_decrypt(const byte *input, byte *output, size_t length, aes_mode_t mode, const byte *iv);

// Macro
#define AES_GET_BYTE(state, i) state->bytes[i]
#define AES_SET_BYTE(state, i, value) state->bytes[i] = value

#endif