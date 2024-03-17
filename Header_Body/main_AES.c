#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "raihan.h"
#include "dwika.h"
#include "alya.h"

#define MAX_TEXT_LENGTH 16

int main() {
    int option;
    int i;
    char inputText[MAX_TEXT_LENGTH];
    unsigned char plaintext[MAX_TEXT_LENGTH];
    unsigned char ciphertext[MAX_TEXT_LENGTH];
    unsigned char decryptedtext[MAX_TEXT_LENGTH];
    unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};
    enum keySize size = SIZE_16;
    
    do {
        printf("||=================================================||\n");
        printf("||                WELCOME TO ONESECURE             ||\n");
        printf("||=================================================||\n");
    
        printf("\nSelect an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("0. Exit\n");
        printf("Option (Only Real Number): ");
        scanf("%d", &option);
        
        if (option == 1) {
            do {
                system("cls");
                printf("=========================     OneSecure Encrypt     =========================\n");
                printf("\nInput your message (up to 16 characters): ");
                scanf("%s", inputText);
                memset(plaintext, 0, MAX_TEXT_LENGTH);
                memcpy(plaintext, inputText, strlen(inputText));
                
                if (strlen(inputText) > MAX_TEXT_LENGTH) {
                    printf("\nError: Plaintext is too long. Please enter up to 16 characters.\n");
                }
            } while (strlen(inputText) > MAX_TEXT_LENGTH);
            
            aes_encrypt(plaintext, ciphertext, key, size);
            
            printf("Hiding Your Message\nProcessing ...");
            sleep(2);
            printf("\nYour Message Hide Successfully\n");
            
            printf("\n(VERY IMPORTANT!!!) keep it in your head\nCiphertext (HEXADECIMAL):\n");
            printHex(ciphertext, MAX_TEXT_LENGTH);
            printf("\n\n\n");
        } else if (option == 2) {
            do{
            system("cls");
	            printf("=========================     OneSecure Decrypt     =========================\n");
	            printf("\nInput Your Ciphertext In HEXADECIMAL (separated by space): ");
	            for (i = 0; i < MAX_TEXT_LENGTH; i++) {
	                if (scanf("%2x", &ciphertext[i]) != 1) {
	                    printf("\nError: Invalid input. Please enter a valid Ciphertext.\n");
	                    while (getchar() != '\n'); // Membersihkan sisa input
	                    break; // Keluar dari loop
	                }
	            }
			}while (i < MAX_TEXT_LENGTH);
            
            aes_decrypt(ciphertext, decryptedtext, key, size);
            
            printf("Decrypt your message\n Processing...\n");
            sleep(2);
            printf("\nDecrypted text (HEXADECIMAL):\n");
            printHex(decryptedtext, MAX_TEXT_LENGTH);
            
            printf("\nDecrypted text (ASCII):\n");
            printASCII(decryptedtext, MAX_TEXT_LENGTH);
            printf("\n\n\n");
        } else if (option == 0) {
            printf("\nExiting...\n");
            sleep(2);
        } else {
            printf("\nInvalid option. Please try again.\n");
        }
    } while (option != 0);
    
    return 0;
}

