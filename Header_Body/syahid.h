#ifndef SYAHID_H
#define SYAHID_H


// Tujuan : Mengekstrak pesan rahasia yang sudah disisipkan dalam gambar stego
void extractMessage(const char* stegoImage);

void ArraytoLinkedList(const char *extractedMessage, address *head);

void printLinkedList(address *head);

void extractProcess(const char* extractedMessage);

#endif
