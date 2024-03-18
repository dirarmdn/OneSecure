#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dhira.h"
#include "syahid.h"

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
void embedMessage(const char* coverImage, const char* secretMessage) {
    int width, height, channels;
    unsigned char* image = readPNG(coverImage, &width, &height, &channels);

    if (image == NULL) {
        printf("Error: Gagal membaca gambar %s.\n", coverImage);
        return;
    }

    // Ubah panjang pesan ke dalam bit
    int secretMessageLength = strlen(secretMessage) * 8;
    int secretMessageIndex = 0;

    // Hitung kapasitas gambar, dikurangi 4 byte pertama untuk menyimpan panjang pesan
    int maxMessageLength = (width * height * channels - 4) * 8;

    // Pastikan panjang pesan tidak melebihi kapasitas gambar
    if (secretMessageLength > maxMessageLength) {
        printf("Error: Panjang pesan terlalu panjang untuk disisipkan dalam gambar.\n");
        free(image); // Bebaskan memori gambar
        return;
    }

    // Simpan panjang pesan ke empat byte pertama gambar
    *((int*)image) = strlen(secretMessage); 

    // Mulai penyisipan pesan
    for (int i = 4; i < width * height * channels; i++) {
        // Pastikan masih ada pesan yang akan disisipkan
        if (secretMessageIndex < secretMessageLength) {
            int lsb = image[i] & 1;
            int secretBit = (secretMessage[secretMessageIndex / 8] >> (7 - (secretMessageIndex % 8))) & 1;

            // Sesuaikan nilai piksel sesuai dengan bit pesan
            if (lsb != secretBit) {
                if (lsb == 0) {
                    if (image[i] < 255) { // Naikkan nilai piksel jika masih memungkinkan
                        image[i]++;
                    }
                } else {
                    if (image[i] > 0) { // Turunkan nilai piksel jika masih memungkinkan
                        image[i]--;
                    }
                }
            }

            // Pindah ke bit pesan berikutnya
            secretMessageIndex++;
        } else {
            break;
        }
    }

    // Simpan gambar stego
    savePNG("stego_image.png", image, width, height);

    // Bebaskan memori gambar
    free(image);
}

// Tujuan : Mengekstrak pesan rahasia yang sudah disisipkan pada gambar stego
// param : stegoImage (nama file gambar stego yang akan diesktrak pesannya)
void extractMessage(const char* stegoImage) {
    int width, height, channels;
    unsigned char* image = readPNG(stegoImage, &width, &height, &channels);

    if (image == NULL) {
        printf("Error: Gagal membaca gambar stego %s.\n", stegoImage);
        return;
    }

    // Ekstrak panjang pesan dari empat byte pertama gambar
    int messageLength = *((int*)image);

    // Hitung panjang pesan dalam bit
    int maxMessageLength = (width * height * channels - 4) * 8;

    // Pastikan panjang pesan yang diekstrak tidak melebihi kapasitas gambar
    if (messageLength * 8 > maxMessageLength) {
        printf("Error: Panjang pesan yang diekstrak melebihi kapasitas gambar.\n");
        free(image);
        return;
    }

    // Alokasikan memori untuk pesan yang diekstrak
    char* extractedMessage = (char*)malloc((messageLength + 1) * sizeof(char));
    if (extractedMessage == NULL) {
        printf("Error: Alokasi memori gagal.\n");
        free(image);
        return;
    }

    int messageIndex = 0;
    int currentByte = 0;
    int index = 0;

    // Mulai ekstraksi pesan
    for (int i = 4; i < width * height * channels; i++) {
        if (messageIndex < messageLength * 8) {
            int lsb = image[i] & 1;
            currentByte |= lsb << (7 - (messageIndex % 8));
            messageIndex++;

            if (messageIndex % 8 == 0) {
                extractedMessage[index++] = currentByte;
                currentByte = 0;
            }
        } else {
            break; // Keluar dari loop jika pesan telah diekstrak semua
        }
    }

    extractedMessage[index] = '\0';

    // Print pesan yang diekstrak
    printf("Pesan yang diekstrak: %s\n", extractedMessage);

    // Bebaskan memori
    free(extractedMessage);
    free(image);
}

int mains(int argc, char *argv[])
{
    const char* coverImage = "lena.png";
    const char* stegoImage = "stego_image.png";
    const char* secretMessage = "hallo";

    embedMessage(coverImage, secretMessage);
    extractMessage(stegoImage);
    
    return 0;
}