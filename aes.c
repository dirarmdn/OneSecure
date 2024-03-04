#include <stdint.h>
#include <stdio.h>

#define Nb 4 // Number of columns in state matrix
#define Nk 4 // Number of 32 bit words in key
#define Nr 10 // Number of rounds

typedef uint8_t byte;
typedef uint32_t word;

word Rotword(word word) {
    return ((word << 8) | (word >> 24));
}

word Subword(word word) {
    word temp[Nb];
    for (int i = 0; i < Nb; i++) {
        temp[i] = Subbyte(word >> (i * 8));
    }
    return ((temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | temp[3]);
}

word Rcon(int round) {
    word temp = 0x01000000;
    temp = temp << (round - 1);
    return temp;
}

void KeyExpansion(byte *key, byte w[Nr+1][Nb]) {
    word temp;
    int i, j;

    for (i = 0; i < Nk; i++) {
        w[0][i] = ((word *)key)[i];
    }

    for (i = 1; i <= Nr; i++) {
        temp = w[i-1][Nk-1];
        if (i % Nk == 0) {
            temp = Subword(Rotword(temp)) ^ Rcon(i/Nk);
        }
        for (j = 0; j < Nk; j++) {
            w[i][j] = w[i-1][j] ^ temp;
            temp = w[i][j];
        }
    }
}

void AddRoundKey(byte state[Nb][Nb], byte w[Nr+1][Nb]) {
    for (int i = 0; i < Nb; i++) {
        for (int j = 0; j < Nb; j++) {
            state[i][j] ^= w[j][i];
        }
    }
}

void SubBytes(byte state[Nb][Nb]) {
    for (int i = 0; i < Nb; i++) {
        for (int j = 0; j < Nb; j++) {
            state[i][j] = Subbyte(state[i][j]);
        }
    }
}

void ShiftRows(byte state[Nb][Nb]) {
    byte temp;

    // First row remains unchanged

    // Second row
    temp = state[1][1];
    state[1][1] = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = temp;

    // Third row
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;

    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Fourth row
    temp = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}

void MixColumns(byte state[Nb][Nb]) {
    byte T[Nb];
    for (int i = 0; i < Nb; i++) {
        T[i] = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
    }
    state[0][0]```INPUT:  Continued from previous response
================================================================
smartsheet.com
state[0][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x02);
state[0][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x02);
state[0][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x02);
state[0][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x02);

state[1][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x03);
state[1][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x03);
state[1][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x03);
state[1][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x03);

state[2][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x01);
state[2][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x01);
state[2][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x01);
state[2][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x01);

state[3][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x02);
state[3][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x02);
state[3][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x02);
state[3][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x02);
```python
}

void InvShiftRows(byte state[Nb][Nb]) {
    byte temp;

    // First row remains unchanged

    // Second row
    temp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = temp;

    // Third row
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;

    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    // Fourth row
    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}

void InvSubBytes(byte state[Nb][Nb]) {
    for (int i = 0; i < Nb; i++) {
        for (int j = 0; j < Nb; j++) {
            state[i][j] = InvSubbyte(state[i][j]);
        }
    }
}

void InvMixColumns(byte state[Nb][Nb]) {
    byte T[Nb];
    for (int i = 0; i < Nb; i++) {
        T[i] = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
    }
    state[0][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x0e);
    state[0][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x0e);
    state[0][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x0e);
    state[0][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x0e);

    state[INPUT:  Continued from previous response
================================================================
smartsheet.com
1][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x0b);
state[1][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x0b);
state[1][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x0b);
state[1][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x0b);

state[2][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x0d);
state[2][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x0d);
state[2][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x0d);
state[2][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x0d);

state[3][0] = T[0] ^ GaloisFieldMultiply(T[3], 0x09);
state[3][1] = T[1] ^ GaloisFieldMultiply(T[0], 0x09);
state[3][2] = T[2] ^ GaloisFieldMultiply(T[1], 0x09);
state[3][3] = T[3] ^ GaloisFieldMultiply(T[2], 0x09);
