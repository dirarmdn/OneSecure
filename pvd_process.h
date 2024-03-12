#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <stdlib.h>
#include <pix.h>
#include <embed.h>
#include "image_operations.h"

typedef struct {
	Image image;
	Message messege;
} steganography;

typedef struct {
	int lebar;
	int tinggi;
	unsigned char *pixels;
} image;

steganography initialize_steganography(char *image_file, char *message);

void embed_message(steganography *steg);

Message extract_message(steganography steg);

image initialize_image(char *filename);

char* read_input(FILE *fp);

int hitung_kapasitas(int panjangX, int panjangY, image image);

#endif


