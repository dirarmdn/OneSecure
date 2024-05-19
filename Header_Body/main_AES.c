#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "raihan.h"
#include "dwika.h"
#include "alya.h"
#include "dhira.h"
#include "syahid.h"

#define MAX_TEXT_LENGTH 24

typedef struct Node {
    unsigned char data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createDCLLNode(unsigned char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

Node* append(Node* head, unsigned char data) {
    Node* newNode = createDCLLNode(data);
    if (!head) {
        return newNode;
    }
    Node* tail = head->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
    return head;
}

Node* arrayToDCLL(unsigned char* array, int size) {
    Node* head = NULL;
    for (int i = 0; i < size; i++) {
        head = append(head, array[i]);
    }
    return head;
}

Node* rotateDCLL(Node* head, int k, int direction) {
    if (!head) return NULL;
    Node* current = head;
    if (direction == 1) { // Rotasi ke kanan
        for (int i = 0; i < k; i++) {
            current = current->prev;
        }
    } else if (direction == 0) { // Rotasi ke kiri
        for (int i = 0; i < k; i++) {
            current = current->next;
        }
    }
    return current;
}

void DCLLToArray(Node* head, unsigned char* array, int size) {
    if (!head) return;
    Node* temp = head;
    for (int i = 0; i < size; i++) {
        array[i] = temp->data;
        temp = temp->next;
    }
}

Node* reverseRotateDCLL(Node* head, int k, int direction) {
    // Reverse the direction: if it was right (1), make it left (0), and vice versa
    int reverseDirection = direction == 1 ? 0 : 1;
    return rotateDCLL(head, k, reverseDirection);
}

void printDCLL(Node* head) {
    if (!head) return;
    Node* temp = head;
    do {
        printf("%02x ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    int option, i, choice;
    char inputText[MAX_TEXT_LENGTH];
    unsigned char plaintext[MAX_TEXT_LENGTH];
    unsigned char ciphertext[MAX_TEXT_LENGTH];
    unsigned char decryptedtext[MAX_TEXT_LENGTH];
    unsigned char key[24] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4'};
    enum keySize size = SIZE_24;
    char cover_image[100], stego_image[100], secret_message[100];
    const char* secretMessage;
    const char* coverImage;
    char menu;
    int rotationSteps = 3; // Misalnya jumlah langkah rotasi yang digunakan
    int rotationDirection = 1; // 1 untuk rotasi ke kanan, 0 untuk rotasi ke kiri
    Node* head = NULL; // Deklarasi head di sini untuk menghindari redefinisi
    
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
        printf("Option (Only Real Number): ");
        scanf("%d", &option);
        
        switch (option)
        {
            case 1:
                do {
                    system("cls");
                    printf("=========================     OneSecure Encrypt AES     =========================\n");
                    printf("\nInput your message (up to 16 characters): ");
                    scanf(" %[^\n]s", inputText);
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
                printf("\n\n");

                // Konversi ciphertext ke DCLL dan lakukan rotasi
                head = arrayToDCLL(ciphertext, MAX_TEXT_LENGTH);
                head = rotateDCLL(head, rotationSteps, rotationDirection);

                printf("Rotated Ciphertext (DCLL):\n");
                printDCLL(head);

                DCLLToArray(head, ciphertext, MAX_TEXT_LENGTH);

                break;
            case 2:
                do {
                    system("cls");
                    printf("=========================     OneSecure Decrypt AES     =========================\n");
                    printf("\nInput Your Rotated Ciphertext In HEXADECIMAL (separated by space): ");
                    for (i = 0; i < MAX_TEXT_LENGTH; i++) {
                        if (scanf("%2x", &ciphertext[i]) != 1) {
                            printf("\nError: Invalid input. Please enter a valid Ciphertext.\n");
                            while (getchar() != '\n'); // Membersihkan sisa input
                            break; // Keluar dari loop
                        }
                    }
                } while (i < MAX_TEXT_LENGTH);
                
                // Konversi ciphertext ke DCLL dan kembalikan rotasi
                head = arrayToDCLL(ciphertext, MAX_TEXT_LENGTH);
                printf("Ciphertext Before Reverse Rotate (DCLL):\n");
                printDCLL(head);

                head = reverseRotateDCLL(head, rotationSteps, rotationDirection);

                printf("Ciphertext After Reverse Rotate (DCLL):\n");
                printDCLL(head);

                DCLLToArray(head, ciphertext, MAX_TEXT_LENGTH);
                
                aes_decrypt(ciphertext, decryptedtext, key, size);
                
                printf("Decrypt your message\n Processing...\n");
                sleep(2);
                printf("\nDecrypted text (HEXADECIMAL):\n");
                printHex(decryptedtext, MAX_TEXT_LENGTH);
                
                printf("\nDecrypted text (ASCII):\n");
                printASCII(decryptedtext, strlen(inputText));
                printf("\n\n\n");
                break;
            case 3:
                system("cls");
                printf("=========================     OneSecure Encrypt PVD     =========================\n");
                printf("Enter your secret message: ");
                scanf(" %[^\n]", secret_message);
                printf("Enter your image name: ");
                scanf(" %s", cover_image);
                printf("Enter your output image name: ");
                scanf(" %s", stego_image);
                // embed_process(cover_image, secret_message, stego_image);
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