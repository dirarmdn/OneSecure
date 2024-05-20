#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "raihan.h"
#include "dwika.h"
#include "alya.h"
#include "dhira.h"
#include "syahid.h"

#define MAX_TEXT_LENGTH 16

int main() {

    int option = 1;
    int i, choice, format;
    char inputText[MAX_TEXT_LENGTH];
    unsigned char plaintext[MAX_TEXT_LENGTH];
    unsigned char ciphertext[MAX_TEXT_LENGTH];
    unsigned char decryptedtext[MAX_TEXT_LENGTH];
    unsigned char key[16];
    enum keySize size = SIZE_16;
    char cover_image[100], stego_image[100], secret_message[100];
    const char* secretMessage;
	const char* coverImage;
    char menu;
    int rotationSteps = 3; // Misalnya jumlah langkah rotasi yang digunakan
    int rotationDirection = 1; // 1 untuk rotasi ke kanan, 0 untuk rotasi ke kiri
    Node* head = NULL; // Deklarasi head di sini untuk menghindari redefinisi
    
    do {
        switch (option) {
            case 1:
                system("cls");
                printf("||=================================================||\n");
                printf("||\tWELCOME TO OneSecure\t||\n");
                printf("||=================================================||\n");
                printf("\nSelect an option:\n");
                printf("1. Encrypt with AES\n");
                printf("2. Decrypt with AES\n");
                printf("3. Encrypt with PVD\n");
                printf("4. Decrypt with PVD\n");
                printf("0. Exit\n");
                printf("Silahkan pilih: ");
                scanf("%d", &choice);
                if (choice = 1){
                    option = 2;
                } else if (choice = 2) {
                    option = 3;
                } else if (choice= 3){
                    option = 4;
                } else if (choice = 4){
                    option = 5;
                } else if (choice = 0){
                    option = 0;
                }
                option  = 1;

            case 2:
            do {
                system("cls");
                printf("=========================     OneSecure Encrypt AES     =========================\n");
                printf("\nInput your message (up to 16 characters): ");
                scanf(" %[^\n]s", &inputText);
                memset(plaintext, 0, MAX_TEXT_LENGTH);
                memcpy(plaintext, inputText, strlen(inputText));
                
                if (strlen(inputText) > MAX_TEXT_LENGTH) {
                    printf("\nError: Plaintext is too long. Please enter up to 16 characters.\n");
                }
            } while (strlen(inputText) > MAX_TEXT_LENGTH);
            
            printf("Enter AES Key (16 characters): ");
            scanf(" %[^\n]s", key);

            aes_encrypt(plaintext, ciphertext, key, size);
            
            printf("Hiding Your Message\nProcessing ...");
            sleep(2);
            printf("\nYour Message Hide Successfully\n");
            
            printf("\n(VERY IMPORTANT!!!) keep it in your head\nCiphertext (HEXADECIMAL):\n");
            printHex(ciphertext, MAX_TEXT_LENGTH);
            system("pause");
            option = 1;

        case 3:
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
            
            printf("Enter AES Key (16 characters): ");
            scanf(" %[^\n]s", key);

            aes_decrypt(ciphertext, decryptedtext, key, size);
            
            printf("Decrypt your message\n Processing...\n");
            sleep(2);
            printf("\nDecrypted text (HEXADECIMAL):\n");
            printHex(decryptedtext, MAX_TEXT_LENGTH);
            
            printf("\nDecrypted text (ASCII):\n");
            printASCII(decryptedtext, MAX_TEXT_LENGTH);
            system("pause");
            option = 1;

        case 4:
            system("cls");
            printf("=========================     OneSecure Encrypt PVD     =========================\n");
            printf("1. Encrypt JPG file\n");
            printf("2. Encrypt PNG file\n");
            printf("Enter choice: ");
            scanf("%d", &option);
            printf("Enter your secret message: ");
            scanf(" %[^\n]", secret_message);
            printf("Enter your image name: ");
            scanf(" %s", cover_image);
            printf("Enter your output image name: ");
            scanf(" %s", stego_image);
            embed_process(cover_image, secret_message, stego_image, option);
        case 5:
            system("cls");
            printf("=========================     OneSecure Decrypt PVD     =========================\n");
            printf("Enter your image name: ");
            scanf(" %s", stego_image);
            extractMessage(stego_image);
            option = 1;
        case 0:
            printf("\nExiting...\n");
            sleep(2);
            exit(0);
            break;
        default:
            printf("\n invalid option. Please try again.\n");
            break;
        }
    } while (option != 0);
    return 0;
}

