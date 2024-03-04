#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes.h"

#define BLOCK_SIZE 16

void print_hex(const uint8_t *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%02x", data[i]);
  }
  printf("\n");
}

int main() {
  AES_State state;
  AES_Key key;

  printf("Enter plaintext (up to 16 characters): ");

  char plaintext[BLOCK_SIZE + 1]; // +1 for null terminator
  int c;
  int i = 0;

  // Read characters one by one, stopping at newline or reaching max characters
  while ((c = fgetc(stdin)) != EOF && c != '\n' && i < BLOCK_SIZE - 1) {
    plaintext[i++] = (char) c;
  }

  // Handle potential buffer overflow
  if (i == BLOCK_SIZE - 1 && c != EOF && c != '\n') {
    printf("Warning: Plaintext exceeds allowed characters. Truncating.\n");
  }

  // Ensure null termination
  plaintext[i] = '\0';

  // Pad the input if it's less than 16 characters
  if (i < BLOCK_SIZE) {
    memset(plaintext + i, ' ', BLOCK_SIZE - i);
  }

  printf("Plaintext (without padding): %s\n", plaintext);

  // Encryption
  aes_init(&state);
  aes_encrypt(&state, &key);
  printf("Encrypted text: ");
  print_hex(state.state[0], sizeof(state.state));

  // Decryption
  AES_State encrypted_state = state; // Make a copy of the encrypted state
  aes_decrypt(&encrypted_state, &key);

  // Remove padding (not necessary in this case, but good practice)
  encrypted_state.state[0][i] = '\0';

  printf("Decrypted text: %s\n", encrypted_state.state[0]);

  return 0;
}

