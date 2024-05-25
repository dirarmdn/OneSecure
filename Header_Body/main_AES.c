#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "raihan.h"
#include "dwika.h"
#include "alya.h"
#include "dhira.h"
#include "syahid.h"

#define MAX_TEXT_LENGTH 16

int main() {
    int option = 1;
    int i, choice;
    int rotationSteps = 8; // Misalnya jumlah langkah rotasi yang digunakan
    int rotationDirection = 1; // 1 untuk rotasi ke kanan, 0 untuk rotasi ke kiri
    bool cek;
    char inputText[MAX_TEXT_LENGTH];
    char *cekext;
    unsigned char plaintext[MAX_TEXT_LENGTH];
    unsigned char ciphertext[MAX_TEXT_LENGTH];
    unsigned char decryptedtext[MAX_TEXT_LENGTH];
    unsigned char key[16];
    enum keySize size = SIZE_16;
    char cover_image[100], stego_image[100], secret_message[100];
    const char* secretMessage;
    const char* coverImage;
    char menu;
    Node* head = NULL;

    do {
        while (option != 0) {
            switch (option) {
                case 1:
                    system("cls");
                    printf("||==============================================||\n");
                    printf("||\t\tWELCOME TO OneSecure\t\t||\n");
                    printf("||==============================================||\n");
                    printf("||Select an option:\t\t\t\t||\n");
                    printf("||1. Encrypt with AES\t\t\t\t||\n");
                    printf("||2. Decrypt with AES\t\t\t\t||\n");
                    printf("||3. Encrypt with PVD\t\t\t\t||\n");
                    printf("||4. Decrypt with PVD\t\t\t\t||\n");
                    printf("||0. Exit\t\t\t\t\t||\n");
                    printf("||Please select: ");
                    cek = false;
                    do {
                        if (scanf("%d", &choice) == true) {
                            cek = true;
                        } else {
                            printf("||Invalid input. Please enter the correct input!\n");
                            printf("||Please select: ");
                            fflush(stdin);
                        }
                    } while (!cek);

                    if (choice == 1) {
                        option = 2;
                        break;
                    } else if (choice == 2) {
                        option = 3;
                        break;
                    } else if (choice == 3) {
                        option = 4;
                        break;
                    } else if (choice == 4) {
                        option = 5;
                        break;
                    } else if (choice == 0) {
                        option = 0;
                    } 
                    break;

                case 2:
                    do {
                        system("cls");
                        printf(">>>>>>>>>>>>>>>>>>\tOneSecure Encrypt AES\t<<<<<<<<<<<<<<<<<<\n");
                        printf("\n>> Input your message (up to 16 characters): ");
                        scanf(" %[^\n]s", inputText);
                        memset(plaintext, 0, MAX_TEXT_LENGTH);
                        memcpy(plaintext, inputText, strlen(inputText));

                        if (strlen(inputText) > MAX_TEXT_LENGTH) {
                            printf(">> Error: Plaintext is too long. Please enter up to 16 characters.\n");
                            sleep(2);
                        }
                    } while (strlen(inputText) > MAX_TEXT_LENGTH);

                    printf(">> Enter AES Key (16 characters): ");
                    scanf(" %[^\n]s", key);

                    aes_encrypt(plaintext, ciphertext, key, size);

                    printf(">> Hiding Your Message\n");
                    printf(">> Processing");
                    printf(" .");
                    sleep(1);
                    printf(" .");
                    sleep(1);
                    printf(" .\n");
                    sleep(1);
                    printf(">> Your Message Hide Successfully!!!\n");
                    
                    printf(">> hidden word in HEXADECIMAL:\n>> ");
                    printHex(ciphertext, MAX_TEXT_LENGTH);

                    head = arrayToDCLL(ciphertext, MAX_TEXT_LENGTH);
                    head = rotateDCLL(head, rotationSteps, rotationDirection);

                    //printf(">> Rotated Ciphertext (DCLL):\n>> ");
                    printf("\n>> Hidden message: \n>> ");
                    printDCLL(head);
                    printf(">> Copy or Remember this message to use in decrypt!!! \n");

                    DCLLToArray(head, ciphertext, MAX_TEXT_LENGTH);

                    system("pause");
                    option = 1;
                    break;

                case 3:
                    do {
                        system("cls");
                        printf(">>>>>>>>>>>>>>>>>>\tOneSecure Decrypt AES\t<<<<<<<<<<<<<<<<<<\n");
                        printf("\n>> Input Your Hidden message : ");
                        for (i = 0; i < MAX_TEXT_LENGTH; i++) {
                            if (scanf("%2x", &ciphertext[i]) != 1) {
                                printf("\n>> Error: Invalid input. Please enter a valid Ciphertext.\n");
                                while (getchar() != '\n');
                                break;
                            }
                        }
                    } while (i < MAX_TEXT_LENGTH);

                    printf(">> Enter AES Key (16 characters): ");
                    scanf(" %[^\n]s", key);

                    printf(">> Decrypt Your Message\n");
                    printf(">> Processing");
                    printf(" .");
                    sleep(1);
                    printf(" .");
                    sleep(1);
                    printf(" .\n");
                    sleep(1);

                    head = arrayToDCLL(ciphertext, MAX_TEXT_LENGTH);
                    //printf("\n>> Ciphertext Before Reverse Rotate (DCLL):\n>> ");
                    //printDCLL(head);

                    head = reverseRotateDCLL(head, rotationSteps, rotationDirection);
                    //printf(">> Ciphertext After Reverse Rotate (DCLL):\n>> ");
                    //printDCLL(head);

                    DCLLToArray(head, ciphertext, MAX_TEXT_LENGTH);
                    //printf("\n>> Decrypted text (HEXADECIMAL):\n>> ");
                    //printHex(decryptedtext, MAX_TEXT_LENGTH);

                    aes_decrypt(ciphertext, decryptedtext, key, size);

                    printf("\n>> This is your message:\n>> ");
                    printASCII(decryptedtext, MAX_TEXT_LENGTH);
                    system("pause");
                    option = 1;
                    break;

                case 4:
                    system("cls");
                    printf(">>>>>>>>>>>>>>>>>>\tOneSecure Encrypt PVD\t<<<<<<<<<<<<<<<<<<\n\n");

                    printf(">> Enter your secret message: ");
                    scanf(" %[^\n]", secret_message);

                    // Loop untuk input nama cover image
                    do {
                        printf(">> Enter your image name (BMP/PNG): ");
                        scanf(" %s", cover_image);

                        // Cek ekstensi file cover image
                        cekext = strrchr(cover_image, '.');
                        cek = (cekext != NULL) && 
                            (strcmp(cekext, ".bmp") == 0 || strcmp(cekext, ".BMP") == 0 || 
                            strcmp(cekext, ".png") == 0 || strcmp(cekext, ".PNG") == 0);

                        if (!cek) {
                            printf(">> Invalid file extension. Please enter a BMP or PNG file.\n");
                        }
                    } while (!cek);

                    // Loop untuk input nama stego image
                    do {
                        printf(">> Enter your output image name (BMP/PNG): ");
                        scanf(" %s", stego_image);

                        // Cek ekstensi file stego image
                        cekext = strrchr(stego_image, '.');
                        cek = (cekext != NULL) && 
                            (strcmp(cekext, ".bmp") == 0 || strcmp(cekext, ".BMP") == 0 || 
                            strcmp(cekext, ".png") == 0 || strcmp(cekext, ".PNG") == 0);

                        if (!cek) {
                            printf(">> Invalid file extension. Please enter a BMP or PNG file.\n");
                        }
                    } while (!cek);

                    // Menentukan pilihan berdasarkan ekstensi file cover image
                    if (strcmp(cekext, ".bmp") == 0 || strcmp(cekext, ".BMP") == 0) {
                        choice = 1;
                    } else if (strcmp(cekext, ".png") == 0 || strcmp(cekext, ".PNG") == 0)
                    {
                        choice = 2;
                    }

                    printf("\n>> Hiding Your Message\n");
                    printf(">> Processing");
                    printf(" .");
                    sleep(1);
                    printf(" .");
                    sleep(1);
                    printf(" .\n");
                    sleep(1);
                    embed_process(cover_image, secret_message, stego_image, choice);
                    system("pause");
                    option = 1;
                    break;

                case 5:
                    system("cls");
                        printf(">>>>>>>>>>>>>>>>>>\tOneSecure Decrypt PVD\t<<<<<<<<<<<<<<<<<<\n\n");
                    do {
                        printf(">> Enter your image name: ");
                        scanf(" %s", stego_image);

                        // Cek ekstensi file stego image
                        cekext = strrchr(stego_image, '.');
                        cek = (cekext != NULL) && 
                            (strcmp(cekext, ".bmp") == 0 || strcmp(cekext, ".BMP") == 0 || 
                            strcmp(cekext, ".png") == 0 || strcmp(cekext, ".PNG") == 0);

                        if (!cek) {
                            printf(">> Invalid file extension. Please enter a BMP or PNG file.\n");
                        }
                    } while (!cek);

                    printf("\n>> Decrypt Your Image to Message\n");
                    printf(">> Processing");
                    printf(" .");
                    sleep(1);
                    printf(" .");
                    sleep(1);
                    printf(" .\n\n");
                    sleep(1);
                    extractMessage(stego_image);
                    system("pause");
                    option = 1;
                    break;
                    break;

                case 0:
                    printf("\n>> Exit ...\n");
                    exit(0);
                    break;
            }
        }
    } while (option != 0);
    return 0;
}
