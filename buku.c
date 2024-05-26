#include "buku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Buku *daftarBuku = NULL; // Linked list buku

void tambahBuku(int isbn, char *judul, char *penulis, char *kategori) {
    if (isbn <= 0 || strlen(judul) == 0 || strlen(penulis) == 0 || strlen(kategori) == 0) {
        printf("Input tidak valid. Pastikan semua data terisi dengan benar.\n");
        return;
    }

    Buku *bukuBaru = (Buku *)malloc(sizeof(Buku));
    bukuBaru->isbn = isbn;
    strcpy(bukuBaru->judul, judul);
    strcpy(bukuBaru->penulis, penulis);
    strcpy(bukuBaru->kategori, kategori);
    bukuBaru->status = TERSEDIA;
    bukuBaru->next = daftarBuku;
    daftarBuku = bukuBaru;
    printf("Buku berhasil ditambahkan.\n");
}

Buku* cariBukuByISBN(int isbn) {
    Buku *current = daftarBuku;
    while (current != NULL) {
        if (current->isbn == isbn) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void tampilkanBuku() {
    Buku *current = daftarBuku;
    while (current != NULL) {
        printf("ISBN: %d, Judul: %s, Penulis: %s, Kategori: %s, Status: %s\n",
               current->isbn, current->judul, current->penulis, current->kategori,
               current->status == TERSEDIA ? "Tersedia" : "Dipinjam");
        current = current->next;
    }
}

void tampilkanBukuByKategori(char *kategori) {
    Buku *current = daftarBuku;
    while (current != NULL) {
        if (strcmp(current->kategori, kategori) == 0) {
            printf("ISBN: %d, Judul: %s, Penulis: %s, Kategori: %s, Status: %s\n",
                   current->isbn, current->judul, current->penulis, current->kategori,
                   current->status == TERSEDIA ? "Tersedia" : "Dipinjam");
        }
        current = current->next;
    }
}

void hapusBuku(int isbn) {
    Buku *current = daftarBuku;
    Buku *previous = NULL;

    while (current != NULL && current->isbn != isbn) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Buku tidak ditemukan.\n");
        return;
    }

    if (previous == NULL) {
        daftarBuku = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Buku berhasil dihapus.\n");
}

void ubahStatusBuku(int isbn, StatusBuku status) {
    Buku *buku = cariBukuByISBN(isbn);
    if (buku != NULL) {
        buku->status = status;
        printf("Status buku berhasil diubah.\n");
    } else {
        printf("Buku tidak ditemukan.\n");
    }
}

void tampilkanBukuDipinjam() {
    Buku *current = daftarBuku;
    while (current != NULL) {
        if (current->status == DIPINJAM) {
            printf("ISBN: %d, Judul: %s, Penulis: %s, Kategori: %s, Status: %s\n",
                   current->isbn, current->judul, current->penulis, current->kategori,
                   "Dipinjam");
        }
        current = current->next;
    }
}

void simpanBukuKeFile() {
    FILE *file = fopen("buku.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data buku.\n");
        return;
    }

    Buku *current = daftarBuku;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s,%d\n", current->isbn, current->judul, current->penulis, current->kategori, current->status);
        current = current->next;
    }

    fclose(file);
    printf("Data buku berhasil disimpan ke file.\n");
}

void muatBukuDariFile() {
    FILE *file = fopen("buku.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk memuat data buku.\n");
        return;
    }

    while (!feof(file)) {
        Buku *bukuBaru = (Buku *)malloc(sizeof(Buku));
        if (fscanf(file, "%d,%99[^,],%49[^,],%49[^,],%d\n", &bukuBaru->isbn, bukuBaru->judul, bukuBaru->penulis, bukuBaru->kategori, (int *)&bukuBaru->status) == 5) {
            bukuBaru->next = daftarBuku;
            daftarBuku = bukuBaru;
        } else {
            free(bukuBaru);
        }
    }

    fclose(file);
    printf("Data buku berhasil dimuat dari file.\n");
}
