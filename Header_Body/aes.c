#include <stdio.h>  // for printf
#include <stdlib.h> // for malloc, free
#include "raihan.h"
#include "dwika.h"
#include "alya.h"

enum errorCode
{
    SUCCESS = 0,
    ERROR_AES_UNKNOWN_KEYSIZE,
    ERROR_MEMORY_ALLOCATION_FAILED,
};

// Implementation: S-Box

unsigned char sbox[256] = {
    // 0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,  // 0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,  // 1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,  // 2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,  // 3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,  // 4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,  // 5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,  // 6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,  // 7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,  // 8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,  // 9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,  // A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,  // B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,  // C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,  // D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,  // E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}; // F

unsigned char rsbox[256] =
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

unsigned char getSBoxValue(unsigned char num);
unsigned char getSBoxInvert(unsigned char num);

// Implementation: Rotate
void rotate(unsigned char *word);

// Implementation: Rcon
unsigned char Rcon[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d,
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab,
    0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d,
    0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25,
    0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d,
    0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
    0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a,
    0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02,
    0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
    0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5,
    0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33,
    0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb};

unsigned char getRconValue(unsigned char num);

// Implementation: Key Schedule Core
void core(unsigned char *word, int iteration);

// Implementation: Key Expansion

unsigned char getSBoxValue(unsigned char num)
{
    return sbox[num];
}

unsigned char getSBoxInvert(unsigned char num)
{
    return rsbox[num];
}

/* Rijndael's key schedule rotate operation
 * rotate the word eight bits to the left
 *
 * rotate(1d2c3a4f) = 2c3a4f1d
 *
 * word is an char array of size 4 (32 bit)
 */
void rotate(unsigned char *word)
{
    unsigned char c;
    int i;

    c = word[0];
    for (i = 0; i < 3; i++)
        word[i] = word[i + 1];
    word[3] = c;
}

unsigned char getRconValue(unsigned char num)
{
    return Rcon[num];
}

void core(unsigned char *word, int iteration)
{
    int i;

    // rotate the 32-bit word 8 bits to the left
    rotate(word);

    // apply S-Box substitution on all 4 parts of the 32-bit word
    for (i = 0; i < 4; ++i)
    {
        word[i] = getSBoxValue(word[i]);
    }

    // XOR the output of the rcon operation with i to the first part (leftmost) only
    word[0] = word[0] ^ getRconValue(iteration);
}

/* Rijndael's key expansion
 * expands an 128,192,256 key into an 176,208,240 bytes key
 *
 * expandedKey is a pointer to an char array of large enough size
 * key is a pointer to a non-expanded key
 */

void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size,size_t expandedKeySize)
{
    // current expanded keySize, in bytes
    int currentSize = 0;
    int rconIteration = 1;
    int i;
    unsigned char t[4] = {0}; // temporary 4-byte variable

    // set the 16,24,32 bytes of the expanded key to the input key
    for (i = 0; i < size; i++)
        expandedKey[i] = key[i];
    currentSize += size;

    while (currentSize < expandedKeySize)
    {
        // assign the previous 4 bytes to the temporary value t
        for (i = 0; i < 4; i++)
        {
            t[i] = expandedKey[(currentSize - 4) + i];
        }

        /* every 16,24,32 bytes we apply the core schedule to t
         * and increment rconIteration afterwards
         */
        if (currentSize % size == 0)
        {
            core(t, rconIteration++);
        }

        // For 256-bit keys, we add an extra sbox to the calculation
        if (size == SIZE_32 && ((currentSize % size) == 16))
        {
            for (i = 0; i < 4; i++)
                t[i] = getSBoxValue(t[i]);
        }

        /* We XOR t with the four-byte block 16,24,32 bytes before the new expanded key.
         * This becomes the next four bytes in the expanded key.
         */
        for (i = 0; i < 4; i++)
        {
            expandedKey[currentSize] = expandedKey[currentSize - size] ^ t[i];
            currentSize++;
        }
    }
}

void subBytes(unsigned char *state)
{
    int i;
    // Looping untuk mengganti setiap byte dalam state dengan nilai dari SBox
    // menggunakan nilai byte dalam state sebagai indeks untuk SBox
    for (i = 0; i < 16; i++)
        state[i] = getSBoxValue(state[i]); // Mengganti byte dengan nilai dari SBox
}

void shiftRows(unsigned char *state)
{
    int i;
    // Iterasi melalui 4 baris dan memanggil fungsi shiftRow() untuk setiap baris
    for (i = 0; i < 4; i++)
        shiftRow(state + i * 4, i); // Memanggil shiftRow() dengan baris state yang sesuai
}

void shiftRow(unsigned char *state, unsigned char nbr)
{
    int i, j;
    unsigned char tmp;
    // Setiap iterasi menggeser baris ke kiri sebanyak nbr kali
    for (i = 0; i < nbr; i++)
    {
        tmp = state[0]; // Menyimpan nilai byte pertama dalam baris
        // Menggeser setiap byte dalam baris ke kiri sebanyak 1 byte
        for (j = 0; j < 3; j++)
            state[j] = state[j + 1];
        state[3] = tmp; // Memasukkan nilai yang disimpan ke byte terakhir
    }
}


void addRoundKey(unsigned char *state, unsigned char *roundKey)
{
    int i;
    for (i = 0; i < 16; i++)
        state[i] = state[i] ^ roundKey[i];
}

unsigned char galois_multiplication(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for (counter = 0; counter < 8; counter++)
    {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void mixColumns(unsigned char *state)
{
    int i, j;
    unsigned char column[4];

    // iterate over the 4 columns
    for (i = 0; i < 4; i++)
    {
        // construct one column by iterating over the 4 rows
        for (j = 0; j < 4; j++)
        {
            column[j] = state[(j * 4) + i];
        }

        // apply the mixColumn on one column
        mixColumn(column);

        // put the values back into the state
        for (j = 0; j < 4; j++)
        {
            state[(j * 4) + i] = column[j];
        }
    }
}

void mixColumn(unsigned char *column)
{
    unsigned char cpy[4];
    int i;
    for (i = 0; i < 4; i++)
    {
        cpy[i] = column[i];
    }
    column[0] = galois_multiplication(cpy[0], 2) ^
                galois_multiplication(cpy[3], 1) ^
                galois_multiplication(cpy[2], 1) ^
                galois_multiplication(cpy[1], 3);

    column[1] = galois_multiplication(cpy[1], 2) ^
                galois_multiplication(cpy[0], 1) ^
                galois_multiplication(cpy[3], 1) ^
                galois_multiplication(cpy[2], 3);

    column[2] = galois_multiplication(cpy[2], 2) ^
                galois_multiplication(cpy[1], 1) ^
                galois_multiplication(cpy[0], 1) ^
                galois_multiplication(cpy[3], 3);

    column[3] = galois_multiplication(cpy[3], 2) ^
                galois_multiplication(cpy[2], 1) ^
                galois_multiplication(cpy[1], 1) ^
                galois_multiplication(cpy[0], 3);
}

void aes_round(unsigned char *state, unsigned char *roundKey)
{
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, roundKey);
}

void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey)
{
    int i, j;
    // iterate over the columns
    for (i = 0; i < 4; i++)
    {
        // iterate over the rows
        for (j = 0; j < 4; j++)
            roundKey[(i + (j * 4))] = expandedKey[(i * 4) + j];
    }
}

void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds)
{
    int i = 0;

    unsigned char roundKey[16];

    createRoundKey(expandedKey, roundKey);
    addRoundKey(state, roundKey);

    for (i = 1; i < nbrRounds; i++)
    {
        createRoundKey(expandedKey + 16 * i, roundKey);
        aes_round(state, roundKey);
    }

    createRoundKey(expandedKey + 16 * nbrRounds, roundKey);
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, roundKey);
}

char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size) {
    int expandedKeySize;
    int nbrRounds;
    int i;
    unsigned char *expandedKey;
    unsigned char block[16];

    // Menentukan jumlah putaran dan ukuran kunci yang diperluas berdasarkan ukuran kunci yang diberikan
    switch (size) {
        case SIZE_16:
            nbrRounds = 10; // Jumlah putaran untuk kunci 16 byte
            expandedKeySize = 176; // Ukuran kunci yang diperluas untuk kunci 16 byte
            break;
        case SIZE_24:
            nbrRounds = 12; // Jumlah putaran untuk kunci 24 byte
            expandedKeySize = 208; // Ukuran kunci yang diperluas untuk kunci 24 byte
            break;
        case SIZE_32:
            nbrRounds = 14; // Jumlah putaran untuk kunci 32 byte
            expandedKeySize = 240; // Ukuran kunci yang diperluas untuk kunci 32 byte
            break;
        default:
            return ERROR_AES_UNKNOWN_KEYSIZE; // Mengembalikan kesalahan jika ukuran kunci tidak diketahui
    }

    // Mengalokasikan memori untuk kunci yang diperluas
    expandedKey = (unsigned char *)malloc(expandedKeySize * sizeof(unsigned char));
    if (expandedKey == NULL) {
        return ERROR_MEMORY_ALLOCATION_FAILED; // Mengembalikan kesalahan jika alokasi memori gagal
    }

    // Menetapkan nilai-nilai blok menggunakan nilai-nilai dari input plaintext
    for (i = 0; i < 16; i++) {
        block[i] = input[i];
    }

    expandKey(expandedKey, key, size, expandedKeySize); // Memperluas kunci
    aes_main(block, expandedKey, nbrRounds); // Melakukan enkripsi blok menggunakan kunci yang diperluas

    // Memasukkan blok yang telah dienkripsi ke dalam output
    for (i = 0; i < 16; i++) {
        output[i] = block[i];
    }

    free(expandedKey); // Membebaskan memori yang dialokasikan untuk kunci yang diperluas
    expandedKey = NULL;

    return SUCCESS; // Mengembalikan nilai sukses
}

void invSubBytes(unsigned char *state)
{
    int i;
    // Looping untuk mengganti setiap byte dalam state dengan nilai dari SBoxInvert
    // menggunakan nilai byte dalam state sebagai indeks untuk SBoxInvert
    for (i = 0; i < 16; i++)
        state[i] = getSBoxInvert(state[i]); // Mengganti byte dengan nilai dari SBoxInvert
}

void invShiftRows(unsigned char *state)
{
    int i;
    // Iterasi melalui 4 baris dan memanggil fungsi invShiftRow() untuk setiap baris
    for (i = 0; i < 4; i++)
        invShiftRow(state + i * 4, i); // Memanggil invShiftRow() dengan baris state yang sesuai
}

void invShiftRow(unsigned char *state, unsigned char nbr)
{
    int i, j;
    unsigned char tmp;
    // Setiap iterasi menggeser baris ke kanan sebanyak nbr kali
    for (i = 0; i < nbr; i++)
    {
        tmp = state[3]; // Menyimpan nilai byte terakhir dalam baris
        // Menggeser setiap byte dalam baris ke kanan sebanyak 1 byte
        for (j = 3; j > 0; j--)
            state[j] = state[j - 1];
        state[0] = tmp; // Memasukkan nilai yang disimpan ke byte pertama
    }
}

void invMixColumns(unsigned char *state)
{
    int i, j;
    unsigned char column[4];

    // iterate over the 4 columns
    for (i = 0; i < 4; i++)
    {
        // construct one column by iterating over the 4 rows
        for (j = 0; j < 4; j++)
        {
            column[j] = state[(j * 4) + i];
        }

        // apply the invMixColumn on one column
        invMixColumn(column);

        // put the values back into the state
        for (j = 0; j < 4; j++)
        {
            state[(j * 4) + i] = column[j];
        }
    }
}

void invMixColumn(unsigned char *column)
{
    unsigned char cpy[4];
    int i;
    for (i = 0; i < 4; i++)
    {
        cpy[i] = column[i];
    }
    column[0] = galois_multiplication(cpy[0], 14) ^
                galois_multiplication(cpy[3], 9) ^
                galois_multiplication(cpy[2], 13) ^
                galois_multiplication(cpy[1], 11);
    column[1] = galois_multiplication(cpy[1], 14) ^
                galois_multiplication(cpy[0], 9) ^
                galois_multiplication(cpy[3], 13) ^
                galois_multiplication(cpy[2], 11);
    column[2] = galois_multiplication(cpy[2], 14) ^
                galois_multiplication(cpy[1], 9) ^
                galois_multiplication(cpy[0], 13) ^
                galois_multiplication(cpy[3], 11);
    column[3] = galois_multiplication(cpy[3], 14) ^
                galois_multiplication(cpy[2], 9) ^
                galois_multiplication(cpy[1], 13) ^
                galois_multiplication(cpy[0], 11);
}

void aes_invRound(unsigned char *state, unsigned char *roundKey)
{

    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKey);
    invMixColumns(state);
}

void aes_invMain(unsigned char *state, unsigned char *expandedKey, int nbrRounds)
{
    int i = 0;

    unsigned char roundKey[16];

    createRoundKey(expandedKey + 16 * nbrRounds, roundKey);
    addRoundKey(state, roundKey);

    for (i = nbrRounds - 1; i > 0; i--)
    {
        createRoundKey(expandedKey + 16 * i, roundKey);
        aes_invRound(state, roundKey);
    }

    createRoundKey(expandedKey, roundKey);
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKey);
}

char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size) {
    int expandedKeySize;
    int nbrRounds;
    unsigned char *expandedKey;
    unsigned char block[16];

    // Menentukan jumlah putaran dan ukuran kunci yang diperluas berdasarkan ukuran kunci yang diberikan
    switch (size) {
        case SIZE_16:
            nbrRounds = 10; // Jumlah putaran untuk kunci 16 byte
            expandedKeySize = 176; // Ukuran kunci yang diperluas untuk kunci 16 byte
            break;
        case SIZE_24:
            nbrRounds = 12; // Jumlah putaran untuk kunci 24 byte
            expandedKeySize = 208; // Ukuran kunci yang diperluas untuk kunci 24 byte
            break;
        case SIZE_32:
            nbrRounds = 14; // Jumlah putaran untuk kunci 32 byte
            expandedKeySize = 240; // Ukuran kunci yang diperluas untuk kunci 32 byte
            break;
        default:
            return ERROR_AES_UNKNOWN_KEYSIZE; // Mengembalikan kesalahan jika ukuran kunci tidak diketahui
    }

    // Mengalokasikan memori untuk kunci yang diperluas
    expandedKey = (unsigned char *)malloc(expandedKeySize * sizeof(unsigned char));
    if (expandedKey == NULL) {
        return ERROR_MEMORY_ALLOCATION_FAILED; // Mengembalikan kesalahan jika alokasi memori gagal
    }

    // Menetapkan nilai-nilai blok menggunakan nilai-nilai dari input ciphertext
    for (int i = 0; i < 16; i++) {
        block[i] = input[i];
    }

    expandKey(expandedKey, key, size, expandedKeySize); // Memperluas kunci

    aes_invMain(block, expandedKey, nbrRounds); // Melakukan dekripsi blok menggunakan kunci yang diperluas

    // Memasukkan blok yang telah didekripsi ke dalam output
    for (int i = 0; i < 16; i++) {
        output[i] = block[i];
    }

    free(expandedKey); // Membebaskan memori yang dialokasikan untuk kunci yang diperluas
    expandedKey = NULL;

    return SUCCESS; // Mengembalikan nilai sukses
}


void printHex(unsigned char *text, int length) {
    // Melakukan iterasi melalui setiap byte dalam array text
    for (int i = 0; i < length; i++) {
        printf("%2.2x ", text[i]); // Mencetak setiap byte dalam format heksadesimal dua digit  di antara setiap byte
    }
    printf("\n");
}

void printASCII(unsigned char *text, int length) {
    // Melakukan iterasi melalui setiap byte dalam array text
    for (int i = 0; i < length; i++) {
        // Memeriksa apakah byte saat ini adalah karakter cetak standar dalam ASCII (dari 0x20 hingga 0x7e)
        if (text[i] >= 0x20 && text[i] <= 0x7e) {
            printf("%c", text[i]); // mencetak karakter ASCII setelah di cek
        } else {
            printf(" "); // mencetak spasi untuk karakter tidak tercetak
        }
    }
    printf("\n");
}

Node* createDCLLNode(unsigned char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}
Node* append(Node* head, unsigned char data) {
    Node* newNode = createDCLLNode(data);
    if (!head) {
        return newNode;
    }
    Node* tail = head->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
    return head;
}

Node* arrayToDCLL(unsigned char* array, int size) {
    Node* head = NULL;
    for (int i = 0; i < size; i++) {
        head = append(head, array[i]);
    }
    return head;
}

Node* insertRandomNode(Node* head, unsigned char data) {
    if (head == NULL) return NULL;
    
    Node* newNode = createDCLLNode(data);
    Node* current = head;

    // Traverse to the second node (third position)
    for (int i = 0; i < 2; i++) {
        current = current->next;
        // If list has less than 3 nodes, insert at the end
        if (current == head) break;
    }

    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;

    return newNode; // Return the newly added node
}

Node* rotateDCLL(Node* head, int k, int direction,  Node** insertedNode) {
    if (!head) return NULL;
    if (k <= 0) return head;

    Node* current = head;

    // Calculate the effective rotations needed, in case k is larger than the length of the list
    int length = 1;
    Node* temp = head;
    while (temp->next != head) {
        length++;
        temp = temp->next;
    }
    k = k % length;

    // Rotate the list by adjusting the head pointer
    if (direction == 1) { // Rotasi ke kanan
        for (int i = 0; i < k; i++) {
            current = current->prev;
        }
    } else if (direction == 0) { // Rotasi ke kiri
        for (int i = 0; i < k; i++) {
            current = current->next;
        }
    }

    // Update the head to the new position
    head = current;

    // Adjust prev and next pointers for all nodes in the list
    Node* new_tail = head->prev;
    Node* new_head = head;

    // Rebuild the list connections
    temp = new_head;
    do {
        temp->prev = new_tail;
        new_tail->next = temp;
        new_tail = temp;
        temp = temp->next;
    } while (temp != new_head);

    *insertedNode = insertRandomNode(current, (unsigned char)(rand() % 256));
    return current;
}


Node* removeNode(Node* head) {
    if (head == NULL) return NULL;

    Node* current = head;

    // Traverse to the fourth position
    for (int i = 0; i < 3; i++) { // Adjusted loop to stop at the fourth node
        current = current->next;
        if (current == head) {
            return head; // If there are less than four nodes, return head unchanged
        }
    }

    // Update links to remove the node
    current->prev->next = current->next;
    current->next->prev = current->prev;

    // Update head if needed
    if (current == head) {
        head = current->prev->prev->prev;
    }

    free(current);
    return head;
}

Node* reverseRotateDCLL(Node* head, int k, int direction, Node* insertedNode) {
    if (!head || k <= 0) return head;

    // Calculate the effective rotations needed, in case k is larger than the length of the list
    int length = 0;
    Node* temp = head;
    while (temp->next != head) {
        length++;
        temp = temp->next;
    }
    k = k % length;

    // Reverse the direction: if it was right (1), make it left (0), and vice versa
    int reverseDirection = (direction == 1) ? 0 : 1;
    Node* current = head;

    if (reverseDirection == 1) { // Rotate right
        for (int i = 0; i < k; i++) {
            current = current->prev;
        }
    } else if (reverseDirection == 0) { // Rotate left
        for (int i = 0; i < k; i++) {
            current = current->next;
        }
    }

    return current;
}

void DCLLToArray(Node* head, unsigned char* array, int size) {
    if (!head) return;
    Node* temp = head;
    for (int i = 0; i < size; i++) {
        array[i] = temp->data;
        temp = temp->next;
    }
}

void printDCLL(Node* head) {
    if (!head) return;
    Node* temp = head;
    do {
        printf("%02x ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}