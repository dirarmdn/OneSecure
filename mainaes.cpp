#include <stdio.h>
#include <stdlib.h>
#include "alya.h" // Saya asumsikan file "alya.h" berisi definisi fungsi-fungsi yang diperlukan untuk AES

int main() {
    // Key yang digunakan untuk enkripsi dan dekripsi
    unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};

    // Plaintext yang akan dienkripsi
    unsigned char plaintext[16];

    // Meminta pengguna untuk memasukkan plaintext
    printf("Masukkan plaintext (16 karakter): ");
    for (int i = 0; i < 16; i++) {
        scanf(" %c", &plaintext[i]);
    }

    // Variabel untuk menyimpan ciphertext hasil enkripsi dan decryptedtext hasil dekripsi
    unsigned char ciphertext[16];
    unsigned char decryptedtext[16];

    // Ukuran kunci (disesuaikan dengan implementasi)
    enum keySize size = SIZE_16;

    // Memperoleh expanded key
    int expandedKeySize = 176;
    unsigned char expandedKey[expandedKeySize];
    expandKey(expandedKey, key, size, expandedKeySize);

    // Enkripsi
    aes_encrypt(plaintext, ciphertext, expandedKey, size);

    // Dekripsi
    aes_decrypt(ciphertext, decryptedtext, expandedKey, size);

    // Menampilkan hasil
    printf("Plaintext: ");
    for (int i = 0; i < 16; i++) {
        printf("%c ", plaintext[i]);
    }
    printf("\n");

    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    printf("Decryptedtext: ");
    for (int i = 0; i < 16; i++) {
        printf("%c ", decryptedtext[i]);
    }
    printf("\n");

    return 0;
}

