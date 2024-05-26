// #include "buku.h"
// #include "anggota.h"
// #include "transaksi.h"
// #include "strukturdata.h"
#include "buku.c"
#include "anggota.c"
#include "transaksi.c"
#include "strukturdata.c"
#include <stdio.h>
#include <stdlib.h>

void tampilkanMenu();
void submenuBuku();
void submenuAnggota();
void submenuTransaksi();

int main() {
    muatBukuDariFile();
    muatAnggotaDariFile();
    muatTransaksiDariFile();

    int pilihan, submenu, isbn, id, idTransaksi, idAnggota;
    char judul[100], penulis[50], kategori[50], tanggal[10];

    while (1) {
        tampilkanMenu();
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                do {
                    submenuBuku();
                    printf("Masukkan pilihan Anda: ");
                    scanf("%d", &submenu);
                    switch (submenu) {
                        case 1:
                            printf("Masukkan ISBN: ");
                            scanf("%d", &isbn);
                            printf("Masukkan judul: ");
                            scanf(" %[^\n]s", judul);
                            printf("Masukkan penulis: ");
                            scanf(" %[^\n]s", penulis);
                            printf("Masukkan kategori: ");
                            scanf(" %[^\n]s", kategori);
                            tambahBuku(isbn, judul, penulis, kategori);
                            break;
                        case 2:
                            printf("Masukkan ISBN: ");
                            scanf("%d", &isbn);
                            Buku *buku = cariBukuByISBN(isbn);
                            if (buku != NULL) {
                                printf("Buku ditemukan:\n");
                                printf("Judul: %s\n", buku->judul);
                                printf("Penulis: %s\n", buku->penulis);
                                printf("Kategori: %s\n", buku->kategori);
                                printf("Status: %s\n", buku->status == TERSEDIA ? "Tersedia" : "Dipinjam");
                            } else {
                                printf("Buku tidak ditemukan.\n");
                            }
                            break;
                        case 3:
                            printf("Daftar Buku:\n");
                            tampilkanBuku();
                            break;
                        case 4:
                            printf("Masukkan kategori: ");
                            scanf(" %[^\n]s", kategori);
                            printf("Buku dalam kategori '%s':\n", kategori);
                            tampilkanBukuByKategori(kategori);
                            break;
                        case 5:
                            printf("Buku yang sedang dipinjam:\n");
                            tampilkanBukuDipinjam();
                            break;
                        case 6:
                            printf("Masukkan ISBN buku yang akan dihapus: ");
                            scanf("%d", &isbn);
                            hapusBuku(isbn);
                            break;
                        case 7:
                            printf("Kembali ke menu utama...\n");
                            break;
                        default:
                            printf("Pilihan tidak valid.\n");
                    }
                } while (submenu != 7);
            break;
            case 2:
                do {
                    submenuAnggota();
                    printf("Masukkan pilihan Anda: ");
                    scanf("%d", &submenu);
                    switch (submenu) {
                        case 1:
                            printf("Masukkan ID anggota: ");
                            scanf("%d", &id);
                            printf("Masukkan nama anggota: ");
                            scanf(" %[^\n]s", judul);
                            tambahAnggota(id, judul);
                            break;
                        case 2:
                            printf("Masukkan ID anggota: ");
                            scanf("%d", &id);
                            Anggota *anggota = cariAnggotaById(id);
                            if (anggota != NULL) {
                                printf("Anggota ditemukan:\n");
                                printf("Nama: %s\n", anggota->nama);
                            } else {
                                printf("Anggota tidak ditemukan.\n");
                            }
                            break;
                        case 3:
                            printf("Daftar Anggota:\n");
                            tampilkanAnggota();
                            break;
                        case 4:
                            printf("Masukkan ID anggota yang akan dihapus: ");
                            scanf("%d", &id);
                            hapusAnggota(id);
                            break;
                        case 5:
                            printf("Kembali ke menu utama...\n");
                            break;
                        default:
                            printf("Pilihan tidak valid.\n");
                    }
                } while (submenu != 5);
                break;
            case 3:
                do {
                    submenuTransaksi();
                    printf("Masukkan pilihan Anda: ");
                    scanf("%d", &submenu);
                    switch (submenu) {
                        case 1:
                            printf("Masukkan ID transaksi: ");
                            scanf("%d", &idTransaksi);
                            printf("Masukkan ID anggota: ");
                            scanf("%d", &idAnggota);
                            printf("Masukkan ISBN buku: ");
                            scanf("%d", &isbn);
                            printf("Masukkan tanggal (DD-MM-YYYY): ");
                            scanf(" %[^\n]s", tanggal);
                            catatTransaksi(idTransaksi, idAnggota, isbn, tanggal);
                            break;
                        case 2:
                            batalkanTransaksi();
                            break;
                        case 3:
                            printf("Masukkan ID transaksi untuk melakukan pengembalian buku: ");
                            scanf("%d", &idTransaksi);
                            pengembalianBuku(idTransaksi);
                            break;
                        case 4:
                            printf("Daftar Transaksi:\n");
                            tampilkanTransaksi();
                            break;
                        case 5:
                            printf("Masukkan ID anggota untuk melihat riwayat peminjaman: ");
                            scanf("%d", &idAnggota);
                            tampilkanRiwayatPeminjaman(idAnggota);
                            break;
                        case 6:
                            printf("Kembali ke menu utama...\n");
                            break;
                        default:
                            printf("Pilihan tidak valid.\n");
                    }
                } while (submenu != 6); // Keluar dari submenu jika pilihan adalah 6
                break;
            case 4:
                simpanBukuKeFile();
                simpanAnggotaKeFile();
                simpanTransaksiKeFile();
                printf("Terima kasih telah menggunakan Sistem Manajemen Perpustakaan.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }

    return 0;
}

void tampilkanMenu() {
    printf("\nSistem Manajemen Perpustakaan\n");
    printf("1. Menu Buku\n");
    printf("2. Menu Anggota\n");
    printf("3. Menu Transaksi\n");
    printf("4. Keluar\n");
}

void submenuBuku() {
    printf("\nMenu Buku\n");
    printf("1. Tambah Buku\n");
    printf("2. Cari Buku berdasarkan ISBN\n");
    printf("3. Tampilkan Semua Buku\n");
    printf("4. Tampilkan Buku berdasarkan Kategori\n");
    printf("5. Tampilkan Buku yang Dipinjam\n");
    printf("6. Hapus Buku\n");
    printf("7. Kembali ke Menu Utama\n");
}

void submenuAnggota() {
    printf("\nMenu Anggota\n");
    printf("1. Tambah Anggota\n");
    printf("2. Cari Anggota berdasarkan ID\n");
    printf("3. Tampilkan Semua Anggota\n");
    printf("4. Hapus Anggota\n");
    printf("5. Kembali ke Menu Utama\n");
}

void submenuTransaksi() {
    printf("\nMenu Transaksi\n");
    printf("1. Catat Transaksi Peminjaman\n");
    printf("2. Batalkan Transaksi Peminjaman\n");
    printf("3. Catat Transaksi Pengembalian\n");
    printf("4. Tampilkan Semua Transaksi\n");
    printf("5. Cari Riwayat Transaksi\n");
    printf("6. Kembali ke Menu Utama\n");
}

