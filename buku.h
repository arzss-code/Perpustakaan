#ifndef BUKU_H
#define BUKU_H

typedef enum {
    TERSEDIA,
    DIPINJAM
} StatusBuku;

typedef struct Buku {
    int isbn;
    char judul[100];
    char penulis[50];
    char kategori[50];
    StatusBuku status;
    struct Buku *next; // untuk single linked list
    struct Buku *prev; // untuk double linked list
} Buku;

void tambahBuku(int isbn, char *judul, char *penulis, char *kategori);
Buku* cariBukuByISBN(int isbn);
void tampilkanBuku();
void tampilkanBukuByKategori(char *kategori);
void hapusBuku(int isbn);
void ubahStatusBuku(int isbn, StatusBuku status);
void tampilkanBukuDipinjam();
void simpanBukuKeFile();
void muatBukuDariFile();

#endif
