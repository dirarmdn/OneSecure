#ifndef RAIHAN_H
#define RAIHAN_H

#include "aes.h"

// Function to add round key to AES state
void aes_add_round_key(AES_State *state, const AES_Key *key);

// Function to perform AES mix columns operation
void aes_mix_columns(AES_State *state);

#endif
