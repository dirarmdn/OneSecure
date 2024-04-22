#ifndef DWIKA_H
#define DWIKA_H

char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
void invMixColumns(unsigned char *state);
void invMixColumn(unsigned char *column);
void aes_invMain(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
void printHex(unsigned char *text, int length);
void printASCII(unsigned char *text, int length);

#endif 
