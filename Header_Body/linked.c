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

void shiftNode (address *head) {
    address pCur;
    infotype temp;

    pCur = *head;

    while (next(pCur) != *head) {
        temp = data(pCur);
        data(pCur) = data(next(pCur));
        data(next(pCur)) = temp;
        // printf("\n%c", data(pCur));
        // printf("%c\n", data(next(pCur)));
        pCur = next(pCur);
    };

    // pCur = *head;
    // printf("\nshift node:\n");
    // do {
    //     printf("%c", data(pCur));
    //     pCur = next(pCur);
    // } while (pCur != *head);
}

void shuffleNode(address *head) {
    address pCur, temp;

    pCur = *head; 
    while (next(pCur) != *head) {
        temp = next(pCur); // Simpan pointer next sementara
        next(pCur) = prev(pCur); // Ubah pointer next menjadi prev
        prev(pCur) = temp; // Ubah pointer prev menjadi next yang disimpan sebelumnya
        pCur = temp; // Pindah ke node berikutnya
    }
    temp = next(pCur); // Simpan pointer next dari node terakhir
    next(pCur) = prev(pCur); // Ubah pointer next dari node terakhir menjadi prev
    prev(pCur) = temp; // Ubah pointer prev dari node terakhir menjadi next yang disimpan sebelumnya
    *head = pCur; // Atur head baru

    // printf("\nshuffle node:\n");
    // pCur = *head;
    // do {
    //     printf("%c", data(pCur));
    //     pCur = next(pCur);
    // } while (pCur != *head);
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

        // Menyisipkan node baru setelah dua node yang ada
        next(pNew) = next(pCur);
        prev(next(pNew)) = pNew;
        next(pCur) = pNew;
        prev(pNew) = pCur;

        // Memindahkan pointer ke node baru
        pCur = next(pCur);
        if (pCur != *head) {
            pCur = next(pCur); // Pindahkan lagi jika tidak mencapai kepala
        }
    } while (pCur != *head);

    // Mencetak isi linked list yang baru disisipi karakter acak
    // pCur = *head;
    // printf("\ninsert rand:\n");
    // do {
    //     printf("%c", data(pCur));
    //     pCur = next(pCur);
    // } while (pCur != *head);
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

void linkedListToArray(address head, char* array) {
    address pCur = head;
    int i = 0;
    do {
        array[i] = data(pCur);
        pCur = next(pCur);
        i++;
    } while (pCur != head);
    array[i] = '\0';
}

void ArraytoLinkedList(const char *extractedMessage, address *head) {
    int i = 0;
    while (extractedMessage[i] != '\0') {
        insertNode(head, extractedMessage[i]);
        i++;
    }
}

void deleteRandChar(address *head) {
    if (*head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }

    address current = *head;
    int position = 1; // Start position from 0

    do {
        address nextNode = next(current);

        // Check if the current position is even
        if (position % 2 == 0) {
            // If the node to be deleted is the head, update the head
            if (current == *head) {
                *head = next(current);
                if (*head == current) { // Only one node was in the list
                    *head = NULL;
                }
            }

            // Unlink the node
            prev(nextNode) = prev(current);
            next(prev(current)) = nextNode;
            free(current);

            if (*head == NULL) {
                break; // List became empty
            }
        }

        current = nextNode;
        position++;

    } while (current != *head);

    // Ensure the list is properly circular
    if (*head != NULL) {
        address last = *head;
        while (next(last) != *head) {
            last = next(last);
        }
        prev(*head) = last;
        next(last) = *head;
    }
}

void unshiftnode(address *head) {
    if (*head == NULL || next(*head) == *head) {
        // Jika linked list kosong atau hanya ada satu node
        return;
    }

    address pLast = prev(*head); // Simpan node terakhir
    address pFirstAfterHead = next(*head); // Simpan node pertama setelah head
    infotype temp;

    while (next(pLast) != pFirstAfterHead) { // Iterasi sampai sebelum node pertama setelah head
        temp = data(pLast);
        data(pLast) = data(prev(pLast));
        data(prev(pLast)) = temp;
        pLast = prev(pLast);
    }

    // Set next dari node terakhir menjadi node pertama setelah head
    next(pLast) = pFirstAfterHead;
    // Set prev dari node pertama setelah head menjadi node terakhir
    prev(pFirstAfterHead) = pLast;
    // Set head baru menjadi node terakhir
    *head = pLast;
}

/*void deletefirst5node(address *head) {
    if (*head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }

    address current = *head;
    int count = 0;

    // Iterasi melalui 5 node pertama
    while (current != NULL && count <= 5) {
        address nextNode = next(current);
        free(current);
        current = nextNode;
        count++;
    }

    // Atur head baru setelah penghapusan
    *head = current;

}*/

/*void deletelast5node(address *head) {
    if (*head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }

    // Traverse to the last node
    address current = *head;
    while (next(current) != *head) {
        current = next(current);
    }

    // Traverse back and delete the last 5 nodes
    int count = 0;
    while (count < 5 && current != *head) {
        address prevNode = prev(current); // Get the previous node
        free(current); // Delete the current node
        current = prevNode; // Move to the previous node
        count++;
    }

    // Update the next pointer of the last remaining node
    next(current) = *head;
}*/


void printLinkedList(address *head) {
    if (head == NULL) {
        printf("Linked list kosong.\n");
        return;
    }

    address current = *head;
    printf("Pesan yang disisipkan: ");
    do {
        printf("%c ", data(current));
        current = next(current);
    } while (current != *head);
    printf("\n");
}


// int main() {
//     int i, size;
//     address head = NULL;
//     const char* secretMessage = "elvis";

//     for (i = 0; i < strlen(secretMessage); i++) {
//         insertNode(&head, secretMessage[i]);
//     }

//     shiftNode(&head);
// 	insertRandChar(&head);
//     size = countList(head);
//     shuffleNode(&head);
//     unsigned char input[size];
//     linkedListToArray(head, input);
//     printf("\nhasil akhir bgt ceritanya:\n");
//     for (int i = 0; i <= size; i++) {
//         printf("%c ", input[i]); // Mencetak isi array
//     }

// }
