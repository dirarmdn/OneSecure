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

    // Read image data
    unsigned char* image = readPNG(stegoImage, &width, &height, &channels);
    if (image == NULL) {
        printf("Error: Failed to read stego image.\n");
        return;
    }

    // Extract message length from the first 4 bytes
    int messageLength = *((int*)image);

    // Allocate memory for extracted message (including null terminator)
    char* extractedMessage = (char*)malloc((messageLength + 1) * sizeof(char));
    if (extractedMessage == NULL) {
        printf("Error: Memory allocation failed.\n");
        free(image);
        return;
    }

    // Extract message bit-by-bit with proper handling of message length
    int messageIndex = 0;
    int currentByte = 0;
    int index = 0; // Index for extracted message array

    while (messageIndex < messageLength * 8 && index < messageLength) {
        // Extract LSB of pixel
        int lsb = image[4 + i] & 1; // Skip the first 4 bytes containing message length

        // Accumulate bit into current byte
        currentByte |= lsb << (7 - (messageIndex % 8));
        messageIndex++;

        // If enough bits collected for a byte, store it in the message string
        if (messageIndex % 8 == 0) {
            extractedMessage[index++] = currentByte;
            currentByte = 0;  // Reset for the next character
        }

        i++; // Increment image data index (avoiding first 4 bytes)
    }

    // Add null terminator to the extracted message
    extractedMessage[index] = '\0';

    // Print the extracted message
    printf("Extracted Message: %s\n", extractedMessage);

    // Free memory
    free(extractedMessage);
    free(image);
}

int main(int argc, char *argv[])
{
	
    unsigned char* coverImage = "lena.png";
    const char* stegoImage = "stego_image.png";
    const char* secretMessage = "Hi";

    embedMessage(coverImage, secretMessage);
    extractMessage(stegoImage);
    
    return 0;
}
