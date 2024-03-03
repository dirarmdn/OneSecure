#include <stdio.h>
#include <string.h>
#include "aes.h" // Assuming your AES implementation (header file)

// Function to pad the plaintext using PKCS#7 padding
int pad_plaintext_length(int plaintext_length) {
    return ((plaintext_length + 15) / 16) * 16; // Calculate the padded length
}

void pad_plaintext(uint8_t *plaintext, int plaintext_length) {
    int padding_size = pad_plaintext_length(plaintext_length) - plaintext_length;
    for (int i = 0; i < padding_size; i++) {
        plaintext[plaintext_length + i] = padding_size; // Add padding bytes with value equal to padding size
    }
}

// Function to unpad the ciphertext after decryption (assuming PKCS#7 padding)
int unpad_plaintext_length(uint8_t *state) {
    int padding_size = state[15]; // Get the padding size from the last byte
    return 16 - padding_size; // Return the unpadded plaintext length
}

int main() {
    // Plaintext yang akan dienkripsi (manually entered)
    char plaintext[1024]; // Example, adjust size as needed

    // Key untuk enkripsi (sesuaikan panjang key dengan implementasi AES)
    uint8_t key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};

    // Inisialisasi state
    AES_State state;
    aes_init(&state);

    // Plaintext input
    printf("Enter plaintext: ");
    if (fgets(plaintext, sizeof(plaintext), stdin) == NULL) {
        fprintf(stderr, "Failed to read plaintext input\n");
        return 1;
    }
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    // Pad the plaintext before encryption (assuming PKCS#7)
    int plaintext_length = strlen(plaintext);
    int padded_plaintext_length = pad_plaintext_length(plaintext_length);
    uint8_t padded_plaintext[padded_plaintext_length];
    memcpy(padded_plaintext, plaintext, plaintext_length);
    pad_plaintext(padded_plaintext, plaintext_length);

    // Copy padded plaintext into state
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state.state[i][j] = padded_plaintext[i * 4 + j];
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

		// Print the decrypted state for debugging
		printf("Decrypted state: ");
		for (int i = 0; i < 16; i++) {
		    printf("%c", state.state[i / 4][i % 4]);
		}
		printf("\n");

		// Unpad the decrypted state (assuming PKCS#7)
		int unpadded_plaintext_length = unpad_plaintext_length((uint8_t*)state.state);
		if (unpadded_plaintext_length == -1) {
		    fprintf(stderr, "Error: Invalid padding detected\n");
		    return 1;
		}

    // Tampilkan plaintext yang didekripsi
    printf("Plaintext (after decryption): ");
    for (int i = 0; i < unpadded_plaintext_length; i++) {
        printf("%c", state.state[i / 4][i % 4]);
    }
    printf("\n");

    return 0;
}

