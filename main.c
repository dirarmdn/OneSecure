#include <stdio.h>
#include "aes.h"

int main() {
  // Plaintext yang akan dienkripsi
  uint8_t plaintext[16] = "Hello, World!";

  // Key untuk enkripsi (sesuaikan panjang key dengan implementasi AES)
  uint8_t key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};

  // Inisialisasi state
  AES_State state;
  aes_init(&state);

  // Copy plaintext ke state
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      state.state[i][j] = plaintext[i * 4 + j];
    }
  }

  // Enkripsi data
  aes_encrypt(&state, (AES_Key*)key);

  // Tampilkan ciphertext (dalam format hex)
  printf("Ciphertext: ");
  for (int i = 0; i < 16; i++) {
    printf("%02x", state.state[i / 4][i % 4]);
  }
  printf("\n");

  // Dekripsi data
  aes_decrypt(&state, (AES_Key*)key);

  // Tampilkan plaintext yang didekripsi
  printf("Plaintext (after decryption): %s\n", state.state);

  return 0;
}

