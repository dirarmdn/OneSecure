/* File        : dhira.h */
/* Deskripsi   : ADT PVD untuk implementasi PVD embedding message */
/* Dibuat oleh : Dhira Ramadini @dirarmdn */
#ifndef DHIRA_H
#define DHIRA_H

// Tujuan: membaca file PNG yang akan dimasukkan/diambil pesan 
unsigned char* readPNG(const char* filename, int* width, int* height, int* channels);

// Tujuan: menyimpan file PNG yang sudah dimasukkan pesan
void savePNG(const char* filename, unsigned char* data, int width, int height);

// Tujuan: memasukkan pesan dengan teknik Pixel Value Differencing
void embedMessage(const char* coverImage, const char* secretMessage, const char* stegoImage);

#endif
