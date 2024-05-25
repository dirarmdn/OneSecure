#ifndef SYAHID_H
#define SYAHID_H
#include "dhira.h"

// Tujuan : Mengekstrak pesan rahasia yang sudah disisipkan dalam gambar stego
void extractMessage(const char* stegoImage);

void ArraytoLinkedList(const char *extractedMessage, address *head);

void printLinkedList(address *head);

void deleteRandChar(address *head);

void unshiftnode(address *head);

//void deletefirst5node(address *head);

//void deletelast5node(address *head);

void extractProcess(const char* extractedMessage);

#endif
