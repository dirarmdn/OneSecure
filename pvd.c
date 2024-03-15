#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dhira.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


// Tujuan: membaca gambar PNG dan mengembalikan data pikselnya
// Param : filename (nama file gambar yang akan dibaca), 
//         width (lebar gambar dalam pixel), height (tinggi gambar dalam pixel), 
//         channels (jumlah saluran warna RGB)
unsigned char* readPNG(const char* filename, int* width, int* height, int* channels) {
    return stbi_load(filename, width, height, channels, STBI_rgb);
}


// Tujuan: menyimpan gambar PNG
// Param : filename (nama file gambar yang akan disimpan), 
//         data (hasil pemrosesan gambar), width (lebar gambar dalam pixel), height (tinggi gambar dalam pixel)
void savePNG(const char* filename, unsigned char* data, int width, int height) {
    stbi_write_png(filename, width, height, 3, data, width * 3);
}


// Tujuan: untuk menyisipkan pesan rahasia menggunakan PVD
// Param : coverImage (nama file gambar yang akan digunakan sebagai penutup),
//         secretMessage (pesan rahasia yang akan disembunyikan)
void embedMessage(const char* coverImage, const char* secretMessage)
{
    int width, height, channels, i; // deklarasi var untuk menyimpan informasi gambar
    // membaca gambar dari file
    unsigned char* image = readPNG(coverImage, &width, &height, &channels);

    int secretMessageLength = strlen(secretMessage); // menghitung panjang pesan rahasia
    int secretMessageIndex = 0; // indeks untuk melacak posisi saat menyisipkan pesan

    // Periksa apakah pesan rahasia dapat disisipkan dalam gambar
    int maxMessageLength = (width * height * channels - 4) / 8; // Panjang maksimum pesan dalam byte
    if (secretMessageLength > maxMessageLength) {
        printf("Pesan rahasia terlalu panjang untuk disisipkan dalam gambar.\n");
        return;
    }

    // Sisipkan panjang pesan ke dalam empat byte pertama dari gambar
    *((int*)image) = secretMessageLength;

    // Loop untuk menyisipkan pesan rahasia ke dalam gambar
    for (i = 4; i < width * height * channels; i++) {
        if (secretMessageIndex < secretMessageLength) { // Jika masih ada pesan yang harus disisipkan
            // Ekstrak bit terakhir dari nilai warna piksel dan bit pesan rahasia
            int lsb = image[i] & 1;
            int secretBit = (secretMessage[secretMessageIndex / 8] >> (7 - (secretMessageIndex % 8))) & 1;

            // Sesuaikan nilai piksel sesuai aturan PVD
            if (lsb != secretBit && image[i] < 255) {
                image[i]++; // Tambahkan satu ke nilai piksel jika perlu
            }

            secretMessageIndex++; // Pindah ke bit pesan rahasia berikutnya
        } else {
            break; // Keluar dari loop jika pesan telah disisipkan semua
        }
    }

    // Simpan gambar stego dalam format PNG
    savePNG("stego_image.png", image, width, height);

    // Bebaskan memori
    free(image);
}


// Fungsi untuk mengekstraksi pesan tersembunyi menggunakan PVD (failed)
void extractMessage(const char* stegoImage) {
    int width, height, channels, i;
    unsigned char* image = readPNG(stegoImage, &width, &height, &channels);

    int secretMessageLength = *((int*)image);
    int secretMessageIndex = 32;
    char secretMessage[1024];

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
    const char* secretMessage = "Hi";

    embedMessage(coverImage, secretMessage);
    extractMessage(stegoImage);

    return 0;
}
