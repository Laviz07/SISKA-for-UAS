#include "dosen.h"

#include "../siska.h"
#include "../struct/struct.h"

#include <iostream>

using namespace std;

void menuDosen(Akun *user) {
    tampilkanBanner();
    Dosen *dsn = getDosenByEmail(user->email);

    if (!dsn) {
        cout << "Mahasiswa tidak ditemukan!\n";
        return;
    }
    do {
        cout << "\n---------- MENU UTAMA DOSEN ----------\n";
        cout << "1. Lihat Mata Kuliah Yang Diaampu\n";
        cout << "2. Lihat Profil\n";
        cout << "3. Keluar\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1 : tampilMatkulDosen(dsn); break;
            case 2 : tampilProfil(dsn); break;

            default: cout << "Pilihan tidak valid.\n"; break;
        }

    } while (pilihan != 3);
}

Dosen *getDosenByEmail(string email) {
    for (int i = 0; i < jumlahDosen; i++) {
        string expectedEmail = daftarDosen[i].nip + "@staff.unsika.ac.id";
        if (email == expectedEmail) { return &daftarDosen[i]; }
    }
    return nullptr;
}

void tampilMatkulDosen(Dosen *dsn) {
    string nip;
    for (int i = 0; i < jumlahDosen; i++) {
        if (dsn == &daftarDosen[i]) {
            nip = daftarDosen[i].nip;
            break;
        }
    }

    cout << "\n===== MATA KULIAH YANG DIAAMPU =====\n";
    for (int i = 0; i < jumlahMatkul; i++) {
        if (daftarMatkul[i].nip_dosen == nip) {
            cout << daftarMatkul[i].kode << " - " << daftarMatkul[i].nama << endl; //
        }
    }
}

void tampilProfil(Dosen *dsn) {
    cout << "\n===== PROFIL DOSEN =====\n";
    cout << "Nama\t: " << dsn->nama << endl;
    cout << "NIP\t: " << dsn->nip << endl;
    cout << "Email\t: " << dsn->nip << "@staff.unsika.ac.id" << endl;
}