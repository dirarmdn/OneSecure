#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <stdlib.h>

// Data Type
typedef uint8_t byte;
typedef uint32_t word;

// Implementation: subBytes
void subBytes(unsigned char *state);
// Implementation: shiftRows
void shiftRows(unsigned char *state);
void shiftRow(unsigned char *state, unsigned char nbr);

// Constant
#define AES_BLOCK_SIZE 16

// 

#endif
