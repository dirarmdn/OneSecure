#include <stdio.h> // Library standar input-output
#include <stdlib.h> // Library standar untuk fungsi-fungsi umum
#include <string.h> // Library standar untuk operasi string
#include <unistd.h> // Library standar untuk fungsi sleep()
#include "raihan.h" // Header file untuk fungsi-fungsi Rahian
#include "dwika.h" // Header file untuk fungsi-fungsi Dwika
#include "alya.h" // Header file untuk fungsi-fungsi Alya

#define MAX_TEXT_LENGTH 16 // Mendefinisikan panjang maksimum teks

int main() { // Fungsi utama program
    int option; // Variabel untuk menyimpan pilihan menu
    int i; // Variabel iterasi
    char inputText[MAX_TEXT_LENGTH]; // Array untuk menyimpan teks input
    unsigned char plaintext[MAX_TEXT_LENGTH]; // Array untuk menyimpan teks plainteks
    unsigned char ciphertext[MAX_TEXT_LENGTH]; // Array untuk menyimpan teks sandi
    unsigned char decryptedtext[MAX_TEXT_LENGTH]; // Array untuk menyimpan teks terdekripsi
    unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'}; // Kunci enkripsi
    enum keySize size = SIZE_16; // Ukuran kunci
    
    do { // Mulai loop utama
        printf("||=================================================||\n"); // Cetak header program
        printf("||                WELCOME TO ONESECURE             ||\n");
        printf("||=================================================||\n");
    
        printf("\nSelect an option:\n"); // Cetak menu pilihan
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("0. Exit\n");
        printf("Option (Only Real Number): "); // Meminta input pilihan dari pengguna
        scanf("%d", &option); // Menyimpan input pilihan
        
        if (option == 1) { // Jika pilihan adalah 1 (enkripsi)
            do { // Loop untuk memastikan teks input tidak melebihi panjang maksimum
                system("cls"); // Menghapus layar konsol (hanya berfungsi di sistem Windows)
                printf("=========================     OneSecure Encrypt     =========================\n"); // Header untuk proses enkripsi
                printf("\nInput your message (up to 16 characters): "); // Meminta input teks plainteks dari pengguna
                scanf("%s", inputText); // Menyimpan input teks
                
                memset(plaintext, 0, MAX_TEXT_LENGTH); // Mengosongkan array plaintext
                memcpy(plaintext, inputText, strlen(inputText)); // Menyalin teks input ke array plaintext
                
                if (strlen(inputText) > MAX_TEXT_LENGTH) { // Jika teks input melebihi panjang maksimum
                    printf("\nError: Plaintext is too long. Please enter up to 16 characters.\n"); // Cetak pesan kesalahan
                }
            } while (strlen(inputText) > MAX_TEXT_LENGTH); // Loop akan berlanjut sampai teks input valid
            
            aes_encrypt(plaintext, ciphertext, key, size); // Melakukan enkripsi teks
                
            printf("Hiding Your Message\nProcessing ..."); // Proses enkripsi
            sleep(2); // Jeda selama 2 detik
            printf("\nYour Message Hide Successfully\n"); // Pesan berhasil
            
            printf("\n(VERY IMPORTANT!!!) keep it in your head\nCiphertext (HEXADECIMAL):\n"); // Pesan enkripsi berhasil
            printHex(ciphertext, MAX_TEXT_LENGTH); // Cetak teks sandi dalam format heksadesimal
            printf("\n\n\n"); // Baris kosong
        } else if (option == 2) { // Jika pilihan adalah 2 (dekripsi)
            do { // Loop untuk memastikan input ciphertext valid
                system("cls"); // Menghapus layar konsol (hanya berfungsi di sistem Windows)
	            printf("=========================     OneSecure Decrypt     =========================\n"); // Header untuk proses dekripsi
	            printf("\nInput Your Ciphertext In HEXADECIMAL (separated by space): "); // Meminta input ciphertext dari pengguna
	            for (i = 0; i < MAX_TEXT_LENGTH; i++) { // Loop untuk membaca teks sandi dalam format heksadesimal
	                if (scanf("%2x", &ciphertext[i]) != 1) { // Membaca satu byte dari input dalam format heksadesimal
	                    printf("\nError: Invalid input. Please enter a valid Ciphertext.\n"); // Cetak pesan kesalahan jika input tidak valid
	                    while (getchar() != '\n'); // Membersihkan sisa input
	                    break; // Keluar dari loop
	                }
	            }
			} while (i < MAX_TEXT_LENGTH); // Loop akan berlanjut sampai teks sandi valid
            
            aes_decrypt(ciphertext, decryptedtext, key, size); // Melakukan dekripsi teks
                
            printf("Decrypt your message\n Processing...\n"); // Proses dekripsi
            sleep(2); // Jeda selama 2 detik
            printf("\nDecrypted text (HEXADECIMAL):\n"); // Cetak hasil dekripsi dalam format heksadesimal
            printHex(decryptedtext, MAX_TEXT_LENGTH); // Cetak teks terdekripsi dalam format heksadesimal
            
            printf("\nDecrypted text (ASCII):\n"); // Cetak hasil dekripsi dalam format ASCII
            printASCII(decryptedtext, MAX_TEXT_LENGTH); // Cetak teks terdekripsi dalam format ASCII
            printf("\n\n\n"); // Baris kosong
        } else if (option == 0) { // Jika pilihan adalah 0 (keluar)
            printf("\nExiting...\n"); // Cetak pesan keluar
            sleep(2); // Jeda selama 2 detik
        } else { // Jika pilihan tidak valid
            printf("\nInvalid option. Please try again.\n"); // Cetak pesan kesalahan
        }
    } while (option != 0); // Loop akan berlanjut sampai pilihan adalah 0 (keluar)
    
    return 0; // Keluar dari program dengan status berhasil
}

