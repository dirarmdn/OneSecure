#include <stdio.h>
#include <stdlib.h>

int getImageWidth(FILE *inputFile);  // Function declaration

void encodePVD(char *inputImage, char *outputImage, char *message) {
    FILE *inputFile = fopen(inputImage, "rb");
    if (inputFile == NULL) {
        perror("Error opening input image file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputImage, "wb");
    if (outputFile == NULL) {
        perror("Error opening output image file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    int headerSize = 54;  // Default header size
    if (fileSize >= 54) {
        char buffer[54];
        fread(buffer, sizeof(char), 54, inputFile);
        headerSize = *(int *)&buffer[10];
        fseek(inputFile, 0, SEEK_SET);
    }

    char *header = malloc(headerSize);
    fread(header, sizeof(char), headerSize, inputFile);
    fwrite(header, sizeof(char), headerSize, outputFile);

    char pixel[3];
    char bit;
    int messageIndex = 0;

    while (fread(pixel, sizeof(char), 3, inputFile) == 3) {
        for (int i = 7; i >= 0; i--) {
            if (message[messageIndex] != '\0') {
                bit = (message[messageIndex] >> i) & 1;
                pixel[2] = (pixel[2] & 0xFE) | (bit & 1);  // Replace LSB with message bit
                messageIndex++;
            }
            fwrite(pixel, sizeof(char), 3, outputFile);
        }

        // Calculate and skip padding bytes
        int padding = (4 - (getImageWidth(inputFile) * 3) % 4) % 4;
        fseek(inputFile, padding, SEEK_CUR);
    }

    free(header);
    fclose(inputFile);
    fclose(outputFile);
}

int getImageWidth(FILE *inputFile) {
    char buffer[54];
    fread(buffer, sizeof(char), 54, inputFile);
    return *(int *)&buffer[18];
}

int main() {
    char inputImage[] = "sample2.bmp";
    char outputImage[] = "output.bmp";
    char message[] = "Hello";

    encodePVD(inputImage, outputImage, message);

    printf("Message encoded successfully.\n");

    return 0;
}
