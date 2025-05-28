#include "mahasiswa.h"

#include "../siska.h"
#include "../struct.h"

#include <iostream>

using namespace std;

void menuMhs(Akun *user) {
    tampilkanBanner();
    do {
        cout << "\n---------- MENU UTAMA MAHASISWA ----------\n";
        cout << "1. Lihat KRS\n";
        cout << "2. Ambil Mata Kuliah\n";
        cout << "0. Keluar\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

    } while (pilihan != 0);
}