#include "dosen.h"

#include "../siska.h"
#include "../struct.h"

#include <iostream>

using namespace std;

void menuDosen(Akun *user) {
    tampilkanBanner();
    do {
        cout << "\n---------- MENU UTAMA DOSEN ----------\n";
        cout << "NIP: " << user->email.substr(0, user->email.find('@')) << endl;
        // cout << "Nama: " << user->nama << endl;
        cout << "Email: " << user->email << endl;

        cout << "1. Lihat Mata Kuliah Yang Diaampu\n";
        cout << "2. Tambah Mata Kuliah Yang Diaampu\n";
        cout << "0. Keluar\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1 : tampilMatkulDosen(user->email); break;

            default: break;
        }

    } while (pilihan != 0);
}

void tampilMatkulDosen(string email) {
    string nip;
    for (int i = 0; i < jumlahDosen; i++) {
        if (daftarAkun[i].email == email) {
            nip = daftarDosen[i].nip;
            break;
        }
    }

    cout << "Matkul yang diampu oleh anda:\n";
    for (int i = 0; i < jumlahMatkul; i++) {
        if (daftarMatkul[i].nip_dosen == nip) {
            cout << daftarMatkul[i].kode << " - " << daftarMatkul[i].nama << endl; //
        }
    }
}