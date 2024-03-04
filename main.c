#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Untuk srand()
#include "aes.h"

#define MAX_INPUT_LENGTH 256

int main() {
    int i;

    // Initialize AES context
    AESContext ctx;
    unsigned char key[AES_128_KEY_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x98, 0x09, 0x6a, 0x6b, 0xe7};
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0, AES_BLOCK_SIZE); // Inisialisasi IV dengan nol

    // Inisialisasi IV dengan nilai acak (opsional)
    srand(time(NULL));
    for (i = 0; i < AES_BLOCK_SIZE; ++i) {
        iv[i] = rand() % 256; // IV diisi dengan nilai acak dari 0 hingga 255
    }

    aes_init(&ctx, key, AES_128_KEY_SIZE, iv, CBC); // Gunakan mode CBC

    // Data yang akan dienkripsi
    printf("Masukkan pesan yang akan dienkripsi: ");
    char input[MAX_INPUT_LENGTH];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Hapus karakter newline

    // Enkripsi data
    unsigned char encrypted[MAX_INPUT_LENGTH]; // Gunakan buffer yang cukup besar
    aes_encrypt(&ctx, (unsigned char*)input, encrypted, strlen(input));

    // Print data yang terenkripsi
    printf("Terenkripsi: ");
    for (i = 0; i < strlen(input); i++) {
        printf("%02x ", encrypted[i]);
    }
    printf("\n");
    fflush(stdout); // Flush output buffer

    // Dekripsi data
    unsigned char decrypted[MAX_INPUT_LENGTH]; // Gunakan buffer yang cukup besar
    aes_decrypt(&ctx, encrypted, decrypted, strlen(input));

    // Print data yang terdekripsi
    printf("Terdekripsi: ");
    for (i = 0; i < strlen(input); i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");
    fflush(stdout); // Flush output buffer

    return 0;
}
