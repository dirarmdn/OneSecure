/* File        : dhira.h */
/* Deskripsi   : ADT PVD untuk implementasi PVD embedding message */
/* Dibuat oleh : Dhira Ramadini @dirarmdn 2024 */
#ifndef DHIRA_H
#define DHIRA_H
#include "../src/package/boolean.h"


#define data(P) (P)->data
#define next(P) (P)->next
#define prev(P) (P)->prev

typedef char infotype;
typedef struct TLinked *address;
typedef struct TLinked {
    infotype data;
    address next;
    address prev;
} linkedList;

// Tujuan : memesan memory dengan alokasi dinamis
// Jika berhasil mengirimkan address, dan jika gagal mengirimkan NULL
address createNode ();

// Tujuan : Mengisi node yang sudah dipesan dengan Nilai yang dikirimkan
// Periksa keberadaan P, Nilai diisi jika p tidak NULL
// next(*p) diisi NULL
// Param(s) : p (parameter Input-Output); data (parameter Input)
void fillNode (address p, infotype data);

// Tujuan : Mengisi linked list dengan random character
// Param : p (parameter Input-Output)
void insertRandChar (address *p);

// Tujuan : Menghubungkan node menjadi sebuah linked list
// Param(s) : head (parameter Input-Output), data (parameter input)
void insertNode(address *head, infotype data);

// Tujuan : Menghitung jumlah banyak node dalam linked list
// Param : head (parameter Input-Output)
int countList(address head);

// Tujuan : Konversi linked list kembali ke array
// Param(s) : head (parameter Input-Output), array (parameter Input-Output)
void linkedListToArray(address head, unsigned char* array);

// Tujuan: membaca gambar PNG dan mengembalikan data pikselnya
// Param : filename (nama file gambar yang akan dibaca), 
//         width (lebar gambar dalam pixel), height (tinggi gambar dalam pixel), 
//         channels (jumlah saluran warna RGB)
unsigned char* readIMG(const char* filename, int* width, int* height, int* channels);

// Tujuan: menyimpan gambar stego format JPG
// Param(s) : filename (nama file gambar yang akan disimpan),
//            data (hasil pemrosesan gambar), width (lebar gambar dalam pixel), height (tinggi gambar dalam pixel)
void savePNG(const char* filename, unsigned char* data, int width, int height);

// Tujuan: menyimpan gambar stego format JPG
// Param(s) : filename (nama file gambar yang akan disimpan),
//            data (hasil pemrosesan gambar), width (lebar gambar dalam pixel), height (tinggi gambar dalam pixel)
void saveJPG(const char* filename, unsigned char* data, int width, int height);

// Tujuan: untuk menyisipkan pesan rahasia menggunakan PVD
// Param : coverImage (nama file gambar yang akan digunakan sebagai penutup),
//         secretMessage (pesan rahasia yang akan disembunyikan)
void embedMessage(const char* coverImage, const char* secretMessage, const char* stegoImage, int format);

// Tujuan : untuk menyatukan proses penyisipan pesan mulai dari pemrosesan
// pesan rahasia sampai embedding to image
void embed_process (const char* coverImage, const char* secretMessage, const char* stegoImage, int format);

#endif
