#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Fungsi untuk membaca gambar PNG dan mengembalikan data pikselnya
unsigned char* readPNG(const char* filename, int* width, int* height, int* channels) {
    return stbi_load(filename, width, height, channels, STBI_rgb);
}

// Fungsi untuk menyimpan gambar PNG
void savePNG(const char* filename, unsigned char* data, int width, int height) {
    stbi_write_png(filename, width, height, 3, data, width * 3);
}

// Fungsi untuk menyisipkan pesan rahasia menggunakan PVD
void embedMessage(unsigned char* coverImage, const char* secretMessage) {
    int width, height, channels, i;
    unsigned char* image = readPNG(coverImage, &width, &height, &channels);

    int secretMessageLength = strlen(secretMessage) + 4;  // Add 4 bytes for the message length
    int secretMessageIndex = 0;

    // Sisipkan panjang pesan ke dalam gambar
    *((int*)image) = secretMessageLength;

    for (i = 4; i < width * height * channels; i++) {
        if (secretMessageIndex < secretMessageLength) {
            int lsb = image[i] & 1;

            // Ambil bit rahasia
            int secretBit = (secretMessage[secretMessageIndex / 8] >> (7 - (secretMessageIndex % 8))) & 1;

            // Sesuaikan nilai piksel sesuai aturan PVD
            if (lsb != secretBit) {
                if (image[i] < 255) {
                    image[i]++;
                }
            }

            secretMessageIndex++;
        } else {
            break;
        }
    }

    // Simpan gambar stego dalam format PNG
    savePNG("stego_image.png", image, width, height);

    // Bebaskan memori
    stbi_image_free(image);
}

// Fungsi untuk mengekstraksi pesan tersembunyi menggunakan PVD
void extractMessage(const char* stegoImage) {
    int width, height, channels, i;
    unsigned char* image = readPNG(stegoImage, &width, &height, &channels);

    int secretMessageLength = *((int*)image);
    int secretMessageIndex = 32; // Start after the length field
    char secretMessage[1024];  // Adjust the size as needed

    // Initialize the secretMessage array
    memset(secretMessage, 0, sizeof(secretMessage));

    // Cetak pesan tersembunyi
    printf("Extracted Message: ");
    for (i = 0; i < secretMessageLength; i++) {
        char currentByte = 0;
        for (int j = 0; j < 8; j++) {
            // Ambil bit terakhir dari nilai piksel
            int lsb = image[secretMessageIndex] & 1;

            // Masukkan bit terakhir ke dalam currentByte
            currentByte |= lsb << (7 - j);
            secretMessageIndex++;

            // Jika sudah membaca cukup bit untuk panjang pesan, baca pesan sebenarnya
            if (secretMessageIndex >= width * height * channels) {
                break;
            }
        }
        secretMessage[i] = currentByte;
    }

    // Cetak pesan tersembunyi dalam format ASCII
    printf("%s\n", secretMessage);

    // Bebaskan memori
    stbi_image_free(image);
}


int main() {
    unsigned char* coverImage = "lena.png";
    const char* stegoImage = "stego_image.png"; 
    const char* secretMessage = "Hello";

    embedMessage(coverImage, secretMessage);
    extractMessage(stegoImage);

    return 0;
}
