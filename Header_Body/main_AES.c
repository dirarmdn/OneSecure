#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "raihan.h"
#include "dwika.h"
#include "alya.h"
#include "dhira.h"
#include "syahid.h"

#define MAX_TEXT_LENGTH 16 // Mendefinisikan panjang maksimum teks

int main() {

    int option, i, choice;
    char inputText[MAX_TEXT_LENGTH];
    unsigned char plaintext[MAX_TEXT_LENGTH];
    unsigned char ciphertext[MAX_TEXT_LENGTH];
    unsigned char decryptedtext[MAX_TEXT_LENGTH];
    unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};
    enum keySize size = SIZE_16;
    char cover_image[100], stego_image[100], secret_message[100];
    const char* secretMessage;
	const char* coverImage;
    char menu;
    
    for (;;) {
        // system("cls");
        printf("||=================================================||\n");
        printf("||                WELCOME TO OneSecure             ||\n");
        printf("||=================================================||\n");
    
        printf("\nSelect an option:\n");
        printf("1. Encrypt with AES\n");
        printf("2. Decrypt with AES\n");
        printf("3. Encrypt with PVD\n");
        printf("4. Decrypt with PVD\n");
        printf("0. Exit\n");
        printf("Option (Only Real Number): "); // Meminta input pilihan dari pengguna
        scanf("%d", &option); // Menyimpan input pilihan
        
        switch (option)
        {
            case 1:
            do {
                system("cls");
                printf("=========================     OneSecure Encrypt AES     =========================\n");
                printf("\nInput your message (up to 16 characters): ");
                scanf("%s", inputText);
                memset(plaintext, 0, MAX_TEXT_LENGTH);
                memcpy(plaintext, inputText, strlen(inputText));
                
                memset(plaintext, 0, MAX_TEXT_LENGTH); // Mengosongkan array plaintext
                memcpy(plaintext, inputText, strlen(inputText)); // Menyalin teks input ke array plaintext
                
                if (strlen(inputText) > MAX_TEXT_LENGTH) { // Jika teks input melebihi panjang maksimum
                    printf("\nError: Plaintext is too long. Please enter up to 16 characters.\n"); // Cetak pesan kesalahan
                }
            } while (strlen(inputText) > MAX_TEXT_LENGTH); // Loop akan berlanjut sampai teks input valid
            
            aes_encrypt(plaintext, ciphertext, key, size); // Melakukan enkripsi teks
                
            printf("Hiding Your Message\nProcessing ..."); // Proses enkripsi
            sleep(2); // Jeda selama 2 detik
            printf("\nYour Message Hide Successfully\n"); // Pesan berhasil
            
            printf("Hiding Your Message\nProcessing ...");
            sleep(2);
            printf("\nYour Message Hide Successfully\n");
            
            printf("\n(VERY IMPORTANT!!!) keep it in your head\nCiphertext (HEXADECIMAL):\n");
            printHex(ciphertext, MAX_TEXT_LENGTH);
            printf("\n\n\n");

            break;
        case 2:
            do {
            system("cls");
	            printf("=========================     OneSecure Decrypt AES     =========================\n");
	            printf("\nInput Your Ciphertext In HEXADECIMAL (separated by space): ");
	            for (i = 0; i < MAX_TEXT_LENGTH; i++) {
	                if (scanf("%2x", &ciphertext[i]) != 1) {
	                    printf("\nError: Invalid input. Please enter a valid Ciphertext.\n");
	                    while (getchar() != '\n'); // Membersihkan sisa input
	                    break; // Keluar dari loop
	                }
	            }
			} while (i < MAX_TEXT_LENGTH);
            
            aes_decrypt(ciphertext, decryptedtext, key, size); // Melakukan dekripsi teks
                
            printf("Decrypt your message\n Processing...\n"); // Proses dekripsi
            sleep(2); // Jeda selama 2 detik
            printf("\nDecrypted text (HEXADECIMAL):\n"); // Cetak hasil dekripsi dalam format heksadesimal
            printHex(decryptedtext, MAX_TEXT_LENGTH); // Cetak teks terdekripsi dalam format heksadesimal
            
            printf("Decrypt your message\n Processing...\n");
            sleep(2);
            printf("\nDecrypted text (HEXADECIMAL):\n");
            printHex(decryptedtext, MAX_TEXT_LENGTH);
            
            printf("\nDecrypted text (ASCII):\n");
            printASCII(decryptedtext, MAX_TEXT_LENGTH);
            printf("\n\n\n");
            break;
        case 3:
            system("cls");
            printf("=========================     OneSecure Encrypt PVD     =========================\n");
            // printf("1. Encrypt JPG file\n");
            // printf("2. Encrypt PNG file\n");
            // printf("Enter choice: ");
            // scanf("%d", &extention);
            printf("Enter your secret message: ");
            scanf(" %[^\n]", secret_message);
            printf("Enter your image name: ");
            scanf(" %s", cover_image);
            printf("Enter your output image name: ");
            scanf(" %s", stego_image);
            embed_process(cover_image, secret_message, stego_image);
            break;
        case 4:
            system("cls");
            printf("=========================     OneSecure Decrypt PVD     =========================\n");
            printf("Enter your image name: ");
            scanf(" %s", stego_image);
            extractMessage(stego_image);
            break;
        case 0:
            printf("\nExiting...\n");
            sleep(2);
            exit(0);
            break;
        default:
            printf("\n invalid option. Please try again.\n");
        }

        printf("Back to menu? (Y/N) \n");
        scanf(" %c", &menu);

        if (menu != 'Y' && menu != 'y') {
            break;
        }
    
    }
    return 0;

}

