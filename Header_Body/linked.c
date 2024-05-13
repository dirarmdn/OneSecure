#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dhira.h"

address createNode () {
	address pNew;

	pNew = (address) malloc(sizeof(linkedList)); // alokasi dinamis
	if (pNew == NULL) {
		printf("Gagal Alokasi\n");
		return NULL;
	} 
	return pNew;
}

void fillNode(address p, infotype data) {
    data(p) = data;
}

void insertNode(address *head, infotype data) {
    address pNew, pCur;
    
    pNew = createNode();
    if (pNew != NULL) {
        fillNode(pNew, data);

        if (*head == NULL) {  //jika linked list kosong
            *head = pNew;
            prev(pNew) = pNew;
            next(pNew) = pNew;
        } else {
            pCur = *head;
            while (next(pCur) != *head) {
                pCur = next(pCur);
            }

            next(pCur) = pNew;
            prev(pNew) = pCur;
            next(pNew) = *head;
            prev(*head) = pNew;
        }
    }
}

void insertRandChar(address *head) {
    address pCur, pNew;
    char randChar;

    srand(time(0));
    pCur = *head;
    do {
        // Menghasilkan karakter acak antara 'a' dan 'z'
        randChar = 'a' + rand() % 26;

        // Membuat node baru dan mengisinya dengan karakter acak
        pNew = createNode();
        fillNode(pNew, randChar);

        // Menyisipkan node baru ke dalam linked list
        next(pNew) = next(pCur);
        prev(next(pNew)) = pNew;
        next(pCur) = pNew;
        prev(pNew) = pCur;

        pCur = next(pNew);
    } while (pCur != *head);
}


int countList(address head) {
    address pCur = head;
    int count = 0;

    do {
        pCur = next(pCur);
        count++;
    } while (pCur != head);
    
    return count;
}

void linkedListToArray(address head, unsigned char* array) {
    address pCur = head;
    int i = 0;
    do {
        array[i] = data(pCur); // Menyalin data ke dalam array
        pCur = next(pCur); // Memindahkan pCur ke node berikutnya
        i++; // Menambahkan indeks array
    } while (pCur != head);
}


// int main() {
//     int i, size;
//     address head = NULL;
//     const char* secretMessage = "halo say";

//     for (i = 0; i < strlen(secretMessage); i++) {
//         insertNode(&head, secretMessage[i]);
//     }

// 	insertRandNumber(&head);
//     size = countList(head);
//     unsigned char input[size];
//     linkedListToArray(head, input);
//     printf("\nhasil akhir bgt ceritanya:\n");
//     for (int i = 0; i < size; i++) {
//         printf("%c", input[i]); // Mencetak isi array
//     }

// }
