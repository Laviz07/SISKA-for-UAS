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
        cout << "Email: " << user->email << endl;

        cout << "1. Lihat Mata Kuliah Yang Diaampu\n";
        cout << "0. Keluar\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1 : tampilMatkulDosen(getDosenByEmail(user->email)->email); break;

            default: break;
        }

    } while (pilihan != 0);
}

Akun *getDosenByEmail(string email) {
    for (int i = 0; i < jumlahAkun; i++) {
        if (daftarAkun[i].email == email && daftarAkun[i].role == "dosen") { return &daftarAkun[i]; }
    }
    return NULL;
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