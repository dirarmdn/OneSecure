#ifndef RAIHAN_H
#define RAIHAN_H

enum keySize {
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

typedef struct Node {
    unsigned char data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
} DoublyCircularLinkedList;

unsigned char getSBoxValue(unsigned char num);
void rotate(unsigned char *word);
unsigned char getSBoxInvert(unsigned char num);
unsigned char getRconValue(unsigned char num);
void core(unsigned char *word, int iteration);
void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize);
// void addRoundKey(unsigned char *state, unsigned char *roundKey);
void addRoundKey(DoublyCircularLinkedList *state, DoublyCircularLinkedList *roundKey);
void mixColumns(unsigned char *state);
void mixColumn(unsigned char *column);
void aes_round(DoublyCircularLinkedList *state, DoublyCircularLinkedList *roundKey);
void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey);

DoublyCircularLinkedList* createDoublyCircularLinkedList();
void insertEnd(DoublyCircularLinkedList *list, unsigned char data);
DoublyCircularLinkedList* arrayToDoublyCircularLinkedList(unsigned char *array, int length);
void doublyCircularLinkedListToArray(DoublyCircularLinkedList *list, unsigned char *array);

#endif // RAIHAN_H