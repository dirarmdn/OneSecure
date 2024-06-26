#ifndef RAIHAN_H
#define RAIHAN_H

enum keySize {
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

typedef struct Node {
    unsigned char data;
    struct Node* next;
    struct Node* prev;
} Node;

unsigned char getSBoxValue(unsigned char num);
void rotate(unsigned char *word);
unsigned char getSBoxInvert(unsigned char num);
unsigned char getRconValue(unsigned char num);
void core(unsigned char *word, int iteration);
void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize);
void addRoundKey(unsigned char *state, unsigned char *roundKey);
void mixColumns(unsigned char *state);
void mixColumn(unsigned char *column);
void aes_round(unsigned char *state, unsigned char *roundKey);
void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey);
Node* createDCLLNode(unsigned char data);
Node* append(Node* head, unsigned char data);
Node* arrayToDCLL(unsigned char* array, int size);
Node* rotateDCLL(Node* head, int k, int direction,  Node** insertedNode);
void DCLLToArray(Node* head, unsigned char* array, int size);
void printDCLL(Node* head);

#endif // RAIHAN_H
