#include "aes.h"

#include <stdint.h>
#define NR 10  // Number of rounds for 128-bit key (adjust for other key lengths)

uint8_t inv_sbox[256];

void aes_init(AES_State *state) {
  // Set state to all zeros
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      state->state[i][j] = 0x00;
    }
  }
}


void aes_add_round_key(AES_State *state, const AES_Key *key) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      state->state[i][j] ^= key->key[i * 4 + j];
    }
  }
}


void aes_sub_bytes(AES_State *state) {
  // Implementasikan lookup table untuk S-box
  uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46,
  };

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      uint8_t value = state->state[i][j];
      uint8_t row = value >> 4;
      uint8_t col = value & 0x0F;
      state->state[i][j] = sbox[row * 16 + col];
    }
  }
}


void aes_shift_rows(AES_State *state) {
  uint8_t temp;

  // Baris 1 tidak digeser
  // Baris 2 digeser 1 byte ke kiri
  temp = state->state[0][1];
  state->state[0][1] = state->state[1][1];
  state->state[1][1] = state->state[2][1];
  state->state[2][1] = state->state[3][1];
  state->state[3][1] = temp;

  // Baris 3 digeser 2 byte ke kiri
  temp = state->state[0][2];
  state->state[0][2] = state->state[2][2];
  state->state[2][2] = temp;
  temp = state->state[1][2];
  state->state[1][2] = state->state[3][2];
  state->state[3][2] = temp;

  // Baris 4 digeser 3 byte ke kiri
  temp = state->state[0][3];
  state->state[0][3] = state->state[3][3];
  state->state[3][3] = state->state[2][3];
  state->state[2][3] = state->state[1][3];
  state->state[1][3] = temp;
}


void aes_mix_columns(AES_State *state) {
  uint8_t temp, a, b;

  for (int col = 0; col < 4; col++) {
    a = state->state[0][col];
    b = state->state[1][col];
    // Mix the first two elements
    temp = a << 1;
    temp ^= (a & 0x80) >> 7;  // Implement x^8 over GF(2^8)
    state->state[0][col] = b ^ temp ^ a;
    state->state[1][col] = a ^ b ^ temp;

    // Mix the remaining two elements
    a = state->state[2][col];
    b = state->state[3][col];
    temp = a << 1;
    temp ^= (a & 0x80) >> 7;  // Implement x^8 over GF(2^8)
    state->state[2][col] = b ^ temp ^ a;
    state->state[3][col] = a ^ b ^ temp;
  }
}

void aes_inv_shift_rows(AES_State *state) {
  // Invert the shift rows operation of aes_shift_rows

  uint8_t tmp;

  // Row 1
  tmp = state->state[1][0];
  state->state[1][0] = state->state[1][3];
  state->state[1][3] = state->state[1][2];
  state->state[1][2] = state->state[1][1];
  state->state[1][1] = tmp;

  // Row 2
  tmp = state->state[2][0];
  state->state[2][0] = state->state[2][2];
  state->state[2][2] = tmp;
  tmp = state->state[2][1];
  state->state[2][1] = state->state[2][3];
  state->state[2][3] = tmp;

  // Row 3
  tmp = state->state[3][0];
  state->state[3][0] = state->state[3][1];
  state->state[3][1] = state->state[3][2];
  state->state[3][2] = state->state[3][3];
  state->state[3][3] = tmp;
}

void aes_inv_sub_bytes(AES_State *state) {
  // Invert the substitution operation of aes_sub_bytes

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // Get the byte from the state
      uint8_t value = state->state[i][j];

      // Get the inverse using the pre-computed inverse S-box table
      state->state[i][j] = inv_sbox[value];
    }
  }
}

void aes_inv_mix_columns(AES_State *state) {
  // Implementasi inverse mix columns operation

  uint8_t a, b;

  for (int col = 0; col < 4; col++) {
    a = state->state[0][col];
    b = state->state[2][col];
    // Invert the mix columns operation (refer to AES specification)
    state->state[0][col] = a ^ (a << 1) ^ b ^ (b << 3);
    state->state[2][col] = a ^ a ^ (b << 1) ^ (b << 2);

    a = state->state[1][col];
    b = state->state[3][col];
    // Invert the mix columns operation
    state->state[1][col] = a ^ (a << 1) ^ b ^ (b << 3);
    state->state[3][col] = a ^ a ^ (b << 1) ^ (b << 2);
  }
}

void aes_inv_sub_bytes(AES_State *state, const uint8_t* inv_sbox) {
  // Invert the substitution operation of aes_sub_bytes

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // Get the byte from the state
      uint8_t value = state->state[i][j];

      // Get the inverse using the provided inverse S-box table
      state->state[i][j] = inv_sbox[value];
    }
  }
}

void aes_encrypt(AES_State *state, const AES_Key *key) {
  // Round 0: Initial round
  aes_add_round_key(state, key);

  // Main rounds
  for (int round = 1; round < NR; round++) {
    aes_sub_bytes(state);
    aes_shift_rows(state);
    aes_mix_columns(state);
    aes_add_round_key(state, (AES_Key*)key + round * 4);  // Access round key
  }

  // Final round
  aes_sub_bytes(state);
  aes_shift_rows(state);
  aes_add_round_key(state, (AES_Key*)key + NR * 4);  // Access last round key
}


void aes_decrypt(AES_State *state, const AES_Key *key) {
  // Round 0: Initial round (uses last round key)
  aes_add_round_key(state, (AES_Key*)key + NR * 4);

  // Main rounds
  for (int round = NR - 1; round > 0; round--) {
    aes_inv_shift_rows(state);  // Inverse shift rows
    aes_inv_sub_bytes(state);  // Inverse substitute bytes
    aes_add_round_key(state, (AES_Key*)key + round * 4);  // Access round key
    aes_inv_mix_columns(state);  // Inverse mix columns
  }

  // Final round
  aes_inv_shift_rows(state);
  aes_inv_sub_bytes(state);
  aes_add_round_key(state, key);  // Use first round key
}


