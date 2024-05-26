#ifndef ANGGOTA_H
#define ANGGOTA_H

typedef struct Anggota {
    int id;
    char nama[50];
    struct Anggota *next;
    struct Anggota *prev;
} Anggota;

void tambahAnggota(int id, char *nama);
Anggota* cariAnggotaById(int id);
void tampilkanAnggota();
void hapusAnggota(int id);
void simpanAnggotaKeFile();
void muatAnggotaDariFile();

#endif
