#ifndef DHIRA_H
#define DHIRA_H

unsigned char* readPNG(const char* filename, int* width, int* height, int* channels);
void savePNG(const char* filename, unsigned char* data, int width, int height);
void embedMessage(unsigned char* coverImage, const char* secretMessage);
void extractMessage(const char* stegoImage);

#endif