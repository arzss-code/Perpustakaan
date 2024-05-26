#include "transaksi.h"
#include "strukturdata.h"
#include "buku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Transaksi *daftarTransaksi = NULL; // Linked list transaksi
StackNode *riwayatTransaksi = NULL; // Stack untuk undo

void catatTransaksi(int idTransaksi, int idAnggota, int isbnBuku, char *tanggal) {
    if (idTransaksi <= 0 || idAnggota <= 0 || isbnBuku <= 0 || strlen(tanggal) != 10) {
        printf("Input tidak valid. Pastikan semua data terisi dengan benar.\n");
        return;
    }

    Transaksi *transaksiBaru = (Transaksi *)malloc(sizeof(Transaksi));
    transaksiBaru->idTransaksi = idTransaksi;
    transaksiBaru->idAnggota = idAnggota;
    transaksiBaru->isbnBuku = isbnBuku;
    strcpy(transaksiBaru->tanggal, tanggal);
    transaksiBaru->next = daftarTransaksi;
    daftarTransaksi = transaksiBaru;

    // Ubah status buku menjadi DIPINJAM
    ubahStatusBuku(isbnBuku, DIPINJAM);

    // Push ke stack riwayat transaksi
    push(*transaksiBaru);
    printf("Transaksi berhasil dicatat.\n");
}

void pengembalianBuku(int idTransaksi) {
    Transaksi *current = daftarTransaksi;
    Transaksi *previous = NULL;

    while (current != NULL && current->idTransaksi != idTransaksi) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Transaksi tidak ditemukan.\n");
        return;
    }

    // Ubah status buku menjadi TERSEDIA
    ubahStatusBuku(current->isbnBuku, TERSEDIA);

    // Hapus transaksi dari daftar transaksi
    if (previous == NULL) {
        daftarTransaksi = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Buku telah dikembalikan.\n");
}

void batalkanTransaksi() {
    if (isStackEmpty()) {
        printf("Tidak ada transaksi yang bisa dibatalkan.\n");
        return;
    }

    Transaksi transaksiTerakhir = pop();
    // Ubah status buku menjadi TERSEDIA
    ubahStatusBuku(transaksiTerakhir.isbnBuku, TERSEDIA);

    // Hapus dari daftar transaksi
    Transaksi *current = daftarTransaksi;
    Transaksi *previous = NULL;
    while (current != NULL && current->idTransaksi != transaksiTerakhir.idTransaksi) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Transaksi tidak ditemukan.\n");
        return;
    } else if (previous == NULL) {
        daftarTransaksi = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Transaksi berhasil dibatalkan.\n");
}

void tampilkanTransaksi() {
    Transaksi *current = daftarTransaksi;
    while (current != NULL) {
        printf("ID Transaksi: %d, ID Anggota: %d, ISBN Buku: %d, Tanggal: %s\n",
               current->idTransaksi, current->idAnggota, current->isbnBuku, current->tanggal);
        current = current->next;
    }
}

void simpanTransaksiKeFile() {
    FILE *file = fopen("transaksi.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data transaksi.\n");
        return;
    }

    Transaksi *current = daftarTransaksi;
    while (current != NULL) {
        fprintf(file, "%d,%d,%d,%s\n", current->idTransaksi, current->idAnggota, current->isbnBuku, current->tanggal);
        current = current->next;
    }

    fclose(file);
    printf("Data transaksi berhasil disimpan ke file.\n");
}

void muatTransaksiDariFile() {
    FILE *file = fopen("transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk memuat data transaksi.\n");
        return;
    }

    while (!feof(file)) {
        Transaksi *transaksiBaru = (Transaksi *)malloc(sizeof(Transaksi));
        if (fscanf(file, "%d,%d,%d,%9[^\n]\n", &transaksiBaru->idTransaksi, &transaksiBaru->idAnggota, &transaksiBaru->isbnBuku, transaksiBaru->tanggal) == 4) {
            transaksiBaru->next = daftarTransaksi;
            daftarTransaksi = transaksiBaru;
        } else {
            free(transaksiBaru);
        }
    }

    fclose(file);
    printf("Data transaksi berhasil dimuat dari file.\n");
}

void tampilkanRiwayatPeminjaman(int idAnggota) {
    Transaksi *current = daftarTransaksi;
    printf("Riwayat Peminjaman Anggota dengan ID %d:\n", idAnggota);
    while (current != NULL) {
        if (current->idAnggota == idAnggota) {
            printf("ID Transaksi: %d, ISBN Buku: %d, Tanggal: %s\n",
                   current->idTransaksi, current->isbnBuku, current->tanggal);
        }
        current = current->next;
    }
}