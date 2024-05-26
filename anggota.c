#include "anggota.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Anggota *daftarAnggota = NULL; // Linked list anggota

void tambahAnggota(int id, char *nama) {
    if (id <= 0 || strlen(nama) == 0) {
        printf("Input tidak valid. Pastikan semua data terisi dengan benar.\n");
        return;
    }

    Anggota *anggotaBaru = (Anggota *)malloc(sizeof(Anggota));
    anggotaBaru->id = id;
    strcpy(anggotaBaru->nama, nama);
    anggotaBaru->next = daftarAnggota;
    anggotaBaru->prev = NULL;
    if (daftarAnggota != NULL) {
        daftarAnggota->prev = anggotaBaru;
    }
    daftarAnggota = anggotaBaru;
    printf("Anggota berhasil ditambahkan.\n");
}

Anggota* cariAnggotaById(int id) {
    Anggota *current = daftarAnggota;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void tampilkanAnggota() {
    Anggota *current = daftarAnggota;
    while (current != NULL) {
        printf("ID: %d, Nama: %s\n", current->id, current->nama);
        current = current->next;
    }
}

void hapusAnggota(int id) {
    Anggota *current = daftarAnggota;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Anggota tidak ditemukan.\n");
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        daftarAnggota = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
    printf("Anggota berhasil dihapus.\n");
}

void simpanAnggotaKeFile() {
    FILE *file = fopen("anggota.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data anggota.\n");
        return;
    }

    Anggota *current = daftarAnggota;
    while (current != NULL) {
        fprintf(file, "%d,%s\n", current->id, current->nama);
        current = current->next;
    }

    fclose(file);
    printf("Data anggota berhasil disimpan ke file.\n");
}

void muatAnggotaDariFile() {
    FILE *file = fopen("anggota.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk memuat data anggota.\n");
        return;
    }

    while (!feof(file)) {
        Anggota *anggotaBaru = (Anggota *)malloc(sizeof(Anggota));
        if (fscanf(file, "%d,%49[^\n]\n", &anggotaBaru->id, anggotaBaru->nama) == 2) {
            anggotaBaru->next = daftarAnggota;
            anggotaBaru->prev = NULL;
            if (daftarAnggota != NULL) {
                daftarAnggota->prev = anggotaBaru;
            }
            daftarAnggota = anggotaBaru;
        } else {
            free(anggotaBaru);
        }
    }

    fclose(file);
    printf("Data anggota berhasil dimuat dari file.\n");
}
