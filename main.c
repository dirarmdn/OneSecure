#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aes.h"  // Pastikan file ini ada dan terpasang dengan benar

#define MAX_INPUT_LENGTH 256

int main() {
    int i;

    // Inisialisasi konteks AES
    AESContext ctx;
    unsigned char key[AES_128_KEY_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x98, 0x09, 0x6a, 0x6b, 0xe7};
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0, AES_BLOCK_SIZE); // Inisialisasi IV dengan nol

    // Opsional: Inisialisasi IV dengan nilai acak
    srand(time(NULL));
    for (i = 0; i < AES_BLOCK_SIZE; ++i) {
        iv[i] = rand() % 256;
    }

    aes_init(&ctx, key, AES_128_KEY_SIZE, iv, CBC); // Gunakan mode CBC

    // Dapatkan pesan dari pengguna
    printf("Masukkan pesan yang akan dienkripsi: ");
    char input[MAX_INPUT_LENGTH];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Hapus karakter newline

    // Periksa apakah input kosong
    if (strlen(input) == 0) {
        printf("Error: Pesan kosong. Masukkan pesan untuk dienkripsi.\n");
        return 1; // Tunjukkan error
    }

    // Hitung ukuran buffer yang dibutuhkan
    int required_buffer_size = ((strlen(input) + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Alokasikan buffer yang cukup besar
    unsigned char encrypted[required_buffer_size];
    unsigned char decrypted[required_buffer_size];

    // Enkripsi data
    aes_encrypt(&ctx, (unsigned char*)input, encrypted, strlen(input));

    // Cetak data terenkripsi
    printf("Terenkripsi: ");
    for (i = 0; i < required_buffer_size; i++) {
        printf("%02x ", encrypted[i]);
    }
    printf("\n");
    fflush(stdout); // Flush buffer output

    // Dekripsi data
    aes_decrypt(&ctx, encrypted, decrypted, required_buffer_size);

    // Cetak data terdekripsi
    printf("Terdekripsi: ");
    for (i = 0; i < strlen(input); i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");
    fflush(stdout); // Flush buffer output

    getchar();
    return 0;
}
