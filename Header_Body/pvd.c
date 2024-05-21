#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dhira.h"
#include "syahid.h"
#include <dirent.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../src/package/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../src/package/stb_image_write.h"

unsigned char* readIMG(const char* filename, int* width, int* height, int* channels) {
    return stbi_load(filename, width, height, channels, STBI_rgb);
}

void savePNG(const char* filename, unsigned char* data, int width, int height) {
    stbi_write_png(filename, width, height, 3, data, width * 3);        
}

void embed_process(const char* coverImage, const char* secretMessage, const char* stegoImage, int option) {
    int i, size;
    address head = NULL;

    for (i = 0; i < strlen(secretMessage); i++) {
        insertNode(&head, secretMessage[i]);
    }

    shiftNode(&head);
	insertRandChar(&head);
    size = countList(head);
    shuffleNode(&head);
    unsigned char input[size];
    linkedListToArray(head, input);
    printf("\nhasil akhir bgt ceritanya:\n");
    for (int i = 0; i <= size; i++) {
        printf("%c ", input[i]); // Mencetak isi array
    }

    embedMessage(coverImage, input, stegoImage, option);
}

void embedMessage(const char* coverImage, const char* secretMessage, const char* stegoImage, int option) {
    int width, height, channels;
    unsigned char* image = readIMG(coverImage, &width, &height, &channels);

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
            int bit_img = image[i] & 1;
            int secretBit = (secretMessage[secretMessageIndex / 8] >> (7 - (secretMessageIndex % 8))) & 1;

            // Sesuaikan nilai piksel sesuai dengan bit pesan
            if (bit_img != secretBit) {
                if (bit_img == 0) {
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
        savePNG(stegoImage, image, width, height);    

        
    // Bebaskan memori gambar
    free(image);
    option = 1;
}

// Tujuan : Mengekstrak pesan rahasia yang sudah disisipkan pada gambar stego
// param : stegoImage (nama file gambar stego yang akan diesktrak pesannya)
void extractMessage(const char* stegoImage) {
    int width, height, channels;
    unsigned char* image = readIMG(stegoImage, &width, &height, &channels);

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
    extractProcess(extractedMessage);

    // Bebaskan memori
    free(extractedMessage);
    free(image);
}

void extractProcess(const char* extractedMessage) {
    address head = NULL;
    ArraytoLinkedList(extractedMessage, &head);
    shuffleNode(&head);
    deletefirst5node(&head);
    //deletelast5node(&head);
    printLinkedList(&head);
}