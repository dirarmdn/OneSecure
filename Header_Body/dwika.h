#ifndef DWIKA_H
#define DWIKA_H

char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);

#endif 
