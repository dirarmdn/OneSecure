#ifndef ALYA_H
#define ALYA_H

enum keySize {
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

unsigned char getSBoxValue(unsigned char num);
void rotate(unsigned char *word);
unsigned char getSBoxInvert(unsigned char num);
unsigned char getRconValue(unsigned char num);
void core(unsigned char *word, int iteration);
void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize);
void subBytes(unsigned char *state);
void shiftRows(unsigned char *state);
void shiftRow(unsigned char *state, unsigned char nbr);
void addRoundKey(unsigned char *state, unsigned char *roundKey);
void mixColumns(unsigned char *state);
void mixColumn(unsigned char *column);
void aes_round(unsigned char *state, unsigned char *roundKey);
void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey);
void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
void invSubBytes(unsigned char *state);
void invShiftRows(unsigned char *state);
void invShiftRow(unsigned char *state, unsigned char nbr);
void invMixColumns(unsigned char *state);
void invMixColumn(unsigned char *column);
void aes_invMain(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);

#endif // ALYA_H
