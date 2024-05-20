#ifndef SYAHID_H
#define SYAHID_H

#define data(P) (P)->data
#define next(P) (P)->next
#define prev(P) (P)->prev

typedef char infotype;
typedef struct TLinked *address;
typedef struct TLinked {
    infotype data;
    address next;
    address prev;
} linkedList;

// Tujuan : Mengekstrak pesan rahasia yang sudah disisipkan dalam gambar stego
void extractMessage(const char* stegoImage);

void ArraytoLinkedList(infotype arr[], int size);

#endif
