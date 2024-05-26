#ifndef TRANSAKSI_H
#define TRANSAKSI_H

typedef struct Transaksi {
    int idTransaksi;
    int idAnggota;
    int isbnBuku;
    char tanggal[10];
    struct Transaksi *next;
} Transaksi;

void catatTransaksi(int idTransaksi, int idAnggota, int isbnBuku, char *tanggal);
void pengembalianBuku(int idTransaksi);
void batalkanTransaksi();
void tampilkanTransaksi();
void simpanTransaksiKeFile();
void muatTransaksiDariFile();
void tampilkanRiwayatPeminjaman(int idAnggota);

#endif
