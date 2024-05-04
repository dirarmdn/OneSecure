#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dhira.h"

address createNode () {
	address pNew;

	pNew = (address)malloc(sizeof(linkedList)); // alokasi dinamis
	if (pNew == NULL) {
		printf("Gagal Alokasi\n");
		return NULL;
	} 
	return pNew;
}

void fillNode(address *p, infotype data) {
    if (p == NULL) {
        printf("Node Belum dialokasi\n");
    } else {
        data(*p) = data;
        next(*p) = NULL;
    }   
}

void insertNode(address *head, infotype data) {
    address pNew, pCur;
    
    pNew = createNode();
    if (pNew != NULL) {
        fillNode(&pNew, data);

        if (*head == NULL) {
            *head = pNew;
        } else {
            pCur = *head;
            while (next(pCur) != NULL) {
                pCur = next(pCur);
            }
            next(pCur) = pNew;
        }   
    }
}


void insertRandNumber(address *head) {
    address pCur, pCode;
    int code;
    char strCode[100];

	srand(time(0));
    pCur = *head;
    while (next(pCur) != NULL) {
        code = rand() % 1000;
        sprintf(strCode, "%d", code); // Mengonversi bilangan integer menjadi string
        
		pCode = createNode();
        fillNode(&pCode, strCode[0]); // Memasukkan karakter pertama dari string sebagai data node
        
		next(pCode) = next(pCur);
        next(pCur) = pCode;
        pCur = next(pCode);
    }
}

int countList(address head) {
    address pCur = head;
	int count;

	count = 0;
    while (pCur != NULL) {
        pCur = next(pCur);
		count++;
    }
    return count;
}

void linkedListToArray(address head, infotype *array) {
    address pCur = head;
    int i = 0;
    while (pCur != NULL) {
        array[i] = data(pCur);
		printf("%c", data(pCur));
        pCur = next(pCur);
        i++;
    }
	printf("\n");
}