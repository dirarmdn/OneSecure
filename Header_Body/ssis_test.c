#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char red, green, blue;
} Pixel;

void spread_spectrum_encode_pixel(Pixel *pixel, unsigned char data) {
    pixel->red = (pixel->red & 0xFC) | ((data >> 6) & 0x03);
    pixel->green = (pixel->green & 0xFC) | ((data >> 4) & 0x03);
    pixel->blue = (pixel->blue & 0xFC) | ((data >> 2) & 0x03);
}

void spread_spectrum_decode_pixel(Pixel *pixel) {
    unsigned char data = ((pixel->red & 0x03) << 6) | ((pixel->green & 0x03) << 4) | ((pixel->blue & 0x03) << 2);
    printf("%c", data);
}

void spread_spectrum_encode_image(const char *filename, const char *output_filename, const char *data) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Error: Could not open input file.\n");
        return;
    }

    FILE *output_fp = fopen(output_filename, "wb");
    if (!output_fp) {
        printf("Error: Could not create output file.\n");
        fclose(fp);
        return;
    }

    // Read and write BMP header
    unsigned char header[54];
    fread(header, sizeof(header), 1, fp);
    fwrite(header, sizeof(header), 1, output_fp);

    Pixel pixel;
    int data_index = 0;

    // Start reading pixel data after the BMP header
    fseek(fp, 54, SEEK_SET);

    while (fread(&pixel, sizeof(Pixel), 1, fp) == 1) {
        spread_spectrum_encode_pixel(&pixel, data[data_index]);
        fwrite(&pixel, sizeof(Pixel), 1, output_fp);
        data_index++;

        if (data[data_index] == '\0') {
            // Write the null terminator pixel and break
            Pixel null_pixel = {0, 0, 0};
            fwrite(&null_pixel, sizeof(Pixel), 1, output_fp);
            break;
        }
    }

    fclose(fp);
    fclose(output_fp);
}


void spread_spectrum_decode_image(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Error: Could not open output file.\n");
        return;
    }

    fseek(fp, 54, SEEK_SET);

    Pixel pixel;
    while (fread(&pixel, sizeof(Pixel), 1, fp) == 1) {
        spread_spectrum_decode_pixel(&pixel);
        if (pixel.red == 0 && pixel.green == 0 && pixel.blue == 0) {
            break;  // Break when encountering null terminator
        }
    }

    fclose(fp);
}


int main() {
    const char *input_filename = "sample2.bmp";
    const char *output_filename = "output11.bmp";
    const char *data = "Dhira";

    spread_spectrum_encode_image(input_filename, output_filename, data);

    spread_spectrum_decode_image(output_filename);

    return 0;
}

