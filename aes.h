#ifndef AES_H
#define AES_H

#include <stdint.h>

typedef struct aes_state_s {
  uint8_t state[4][4];
} AES_State;

typedef struct aes_key_s {
  uint8_t key[32];
} AES_Key;

void aes_init(AES_State *state);
void aes_add_round_key(AES_State *state, const AES_Key *key);
void aes_sub_bytes(AES_State *state);
void aes_shift_rows(AES_State *state);
void aes_mix_columns(AES_State *state);
void aes_encrypt(AES_State *state, const AES_Key *key);
void aes_decrypt(AES_State *state, const AES_Key *key);

// Add declarations for inverse functions here
void aes_inv_shift_rows(AES_State *state);
void aes_inv_sub_bytes(AES_State *state);
void aes_inv_mix_columns(AES_State *state);

// Declare aes_inv_sub_bytes with an argument for the inverse S-box
void aes_inv_sub_bytes(AES_State *state, const uint8_t* inv_sbox);


#endif /* AES_H */

