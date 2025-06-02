#include "dosen.h"

#include "../siska.h"
#include "../struct/struct.h"

#include <iostream>

using namespace std;

// fungsi untuk mendapatkan dosen berdasarkan email
Dosen *getDosenByEmail(string email) {
    for (int i = 0; i < jumlahDosen; i++) {
        // jika email dosen yang login sama dengan yang ada di daftar dosen
        string expectedEmail = daftarDosen[i].nip + "@staff.unsika.ac.id";
        if (email == expectedEmail) { // jika cocok
            return &daftarDosen[i];   // mengembalikan alamat dosen
        }
    }
    return nullptr;
}

/* ------------------------------- MENU DOSEN ------------------------------- */
void menuDosen(Akun *user) {
    tampilkanBanner();
    Dosen *dsn = getDosenByEmail(user->email); // mendapatkan dosen berdasarkan email

    if (!dsn) {
        cout << "Dosen tidak ditemukan!\n";
        return;
    }
    do {
        cout << "\n---------- MENU UTAMA DOSEN ----------\n";
        cout << "1. Lihat Mata Kuliah Yang Diaampu\n";
        cout << "2. Lihat Profil\n";
        cout << "3. Logout\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        // jika input tidak valid
        if (cin.fail()) {
            cin.clear();            // membersihkan buffer
            cin.ignore(1000, '\n'); // mengabaikan input sebelumnya
            cout << "Input tidak valid. Harap masukkan angka.\n";
        }

        switch (pilihan) {
            case 1 : tampilMatkulDosen(dsn); break;
            case 2 : tampilProfilDosen(dsn); break;

            default: cout << "Pilihan tidak valid.\n"; break;
        }

    } while (pilihan != 3);
}

// fungsi untuk menampilkan mata kuliah yang diaampu
void tampilMatkulDosen(Dosen *dsn) {
    string nip;
    for (int i = 0; i < jumlahDosen; i++) {
        if (dsn == &daftarDosen[i]) { // jika dosen yang login sama dengan yang ada di daftar dosen
            nip = daftarDosen[i].nip; // mendapatkan NIP dosen
            break;
        }
    }

    cout << "\n===== MATA KULIAH YANG DIAAMPU =====\n";

    if (jumlahMatkul == 0) { // jika tidak ada mata kuliah
        cout << "\nBelum ada mata kuliah.\n";
        return;
    }

    for (int i = 0; i < jumlahMatkul; i++) {    // mencari mata kuliah yang diaampu
        if (daftarMatkul[i].nip_dosen == nip) { // jika nip di mata kuliah sama dengan NIP dosen
            cout << daftarMatkul[i].kode << " - " << daftarMatkul[i].nama << endl; //
        } else { // jika tidak ada mata kuliah yang diaampu
            cout << "Belum ada mata kuliah yang diaampu.\n";
        }
    }
}

// fungsi untuk menampilkan profil
void tampilProfilDosen(Dosen *dsn) {
    cout << "\n===== PROFIL DOSEN =====\n";
    cout << "Nama\t: " << dsn->nama << endl;
    cout << "NIP\t: " << dsn->nip << endl;
    cout << "Email\t: " << dsn->nip << "@staff.unsika.ac.id" << endl;
}