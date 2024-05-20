#include <string.h>
#include <unistd.h>
#include <stdio.h>  // for printf
#include <stdlib.h> // for malloc, free
#include "raihan.h"
#include "dwika.h"
#include "alya.h"
#include <time.h>

// Fungsi untuk menambahkan node baru ke dalam linked list
void appendNode(struct Node **head, unsigned char data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = (*head)->prev;
    (*head)->prev->next = newNode;
    (*head)->prev = newNode;
}

// Fungsi untuk mengubah output enkripsi menjadi doubly circular linked list
void outputToLinkedList(unsigned char *output, struct Node **head) {
    *head = (struct Node *)malloc(sizeof(struct Node));
    (*head)->prev = *head;
    (*head)->next = *head;
    for (int i = 0; i < 16; i++) {
        appendNode(head, output[i]);
    }
}

// Fungsi untuk mengacak linked list
void shuffleLinkedList(struct Node *head) {
    // Mendapatkan panjang linked list
    int length = 0;
    struct Node *temp = head;
    do {
        length++;
        temp = temp->next;
    } while (temp != head);

    // Melakukan pengacakan
    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % length;
        // Menukar data antara node ke-i dan node ke-randomIndex
        struct Node *node1 = head;
        struct Node *node2 = head;
        for (int j = 0; j < i; j++) {
            node1 = node1->next;
        }
        for (int j = 0; j < randomIndex; j++) {
            node2 = node2->next;
        }
        unsigned char temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }
}

// Fungsi untuk mengembalikan linked list ke bentuk array
void linkedListToArray(struct Node *head, unsigned char *output) {
    struct Node *temp = head;
    int i = 0;
    do {
        output[i++] = temp->data;
        temp = temp->next;
    } while (temp != head);
}

char aes_decryptFromLinkedList(struct Node *head, unsigned char *output, unsigned char *key, enum keySize size) {
    unsigned char block[16];
    linkedListToArray(head, block);
    return aes_decrypt(block, output, key, size);
}