#ifndef ALYA_H
#define ALYA_H

void subBytes(unsigned char *state);
void shiftRows(unsigned char *state);
void shiftRow(unsigned char *state, unsigned char nbr);
void invSubBytes(unsigned char *state);
void invShiftRows(unsigned char *state);
void invShiftRow(unsigned char *state, unsigned char nbr);
Node* insertRandomNode(Node* head, unsigned char data);

#endif
