#ifndef DHIRA_H
#define DHIRA_H

// to read PNG file using stb image lib
unsigned char* readPNG(const char* filename, int* width, int* height, int* channels);
// to save Stego Image 
void savePNG(const char* filename, unsigned char* data, int width, int height);
// to embed message using PVD technique
void embedMessage(unsigned char* coverImage, const char* secretMessage);
// to extract message form stego image
void extractMessage(const char* stegoImage);

#endif