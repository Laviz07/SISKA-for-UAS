#include "admin.h"

#include "../siska.h"

#include <iostream>
#include <string>
using namespace std;

void menuAdmin() {
    tampilkanBanner();
    do {
        cout << "\n---------- MENU UTAMA ADMIN ----------\n";
        cout << "1. Kelola Mahasiswa\n";
        cout << "2. Kelola Dosen\n";
        cout << "3. Kelola Mata Kuliah\n";
        cout << "0. Logout\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                do {
                    cout << "\n===== KELOLA MAHASISWA =====\n";
                    cout << "1. Tambah Mahasiswa\n";
                    cout << "2. Lihat Daftar Mahasiswa\n";
                    cout << "3. Cari Mahasiswa\n";
                    cout << "4. Edit Mahasiswa\n";
                    cout << "5. Hapus Mahasiswa\n";
                    cout << "6. Kembali\n";
                    cout << "Pilihan: ";
                    cin >> pilihan;
                    string npm;
                    switch (pilihan) {
                        case 1: tambahMhs(); break;
                        case 2: tampilMhs(); break;
                        case 3:
                            cout << "\nNPM: ";
                            cin >> npm;
                            cariMhs(npm);
                            break;
                        case 4:
                            cout << "\nNPM: ";
                            cin >> npm;
                            editMhs(npm);
                            break;
                        case 5:
                            cout << "\nNPM: ";
                            cin >> npm;
                            hapusMhs(npm);
                            break;
                        default: cout << "Pilihan tidak tersedia" << endl;
                    }

                } while (pilihan != 6);
                break;

            case 2:
                do {
                    cout << "\n===== KELOLA DOSEN =====\n";
                    cout << "1. Tambah Dosen\n";
                    cout << "2. Lihat Daftar Dosen\n";
                    cout << "3. Cari Dosen\n";
                    cout << "4. Edit Dosen\n";
                    cout << "5. Hapus Dosen\n";
                    cout << "6. Kembali\n";
                    cout << "Pilihan: ";
                    cin >> pilihan;
                    string nip;
                    switch (pilihan) {
                        case 1: tambahDosen(); break;
                        case 2: tampilDosen(); break;
                        case 3:
                            cout << "NIP: ";
                            cin >> nip;
                            cariDosen(nip);
                            break;
                        case 4:
                            cout << "NIP: ";
                            cin >> nip;
                            editDosen(nip);
                            break;
                        case 5:
                            cout << "NIP: ";
                            cin >> nip;
                            hapusDosen(nip);
                            break;
                        default: cout << "Pilihan tidak tersedia" << endl;
                    }

                } while (pilihan != 6);
                break;

            case 3:
                do {
                    cout << "\n===== KELOLA MATA KULIAH =====\n";
                    cout << "1. Tambah Mata Kuliah\n";
                    cout << "2. Lihat Daftar Mata Kuliah\n";
                    cout << "3. Cari Mata Kuliah\n";
                    cout << "4. Edit Mata Kuliah\n";
                    cout << "5. Hapus Mata Kuliah\n";
                    cout << "6. Kembali\n";
                    cout << "Pilihan: ";
                    cin >> pilihan;
                    string kode;
                    switch (pilihan) {
                        case 1: tambahMatkul(); break;
                        case 2: tampilMatkul(); break;
                        case 3:
                            cout << "Kode: ";
                            cin >> kode;
                            cariMatkul(kode);
                            break;
                        case 4:
                            cout << "Kode: ";
                            cin >> kode;
                            editMatkul(kode);
                            break;
                        case 5:
                            cout << "Kode: ";
                            cin >> kode;
                            hapusMatkul(kode);
                            break;
                        default: cout << "Pilihan tidak tersedia" << endl;
                    }
                } while (pilihan != 6);
                break;

            default: cout << "Pilihan tidak tersedia" << endl;
        }
        cin.fail();
        cin.clear();
        cin.ignore(1000, '\n');
    } while (pilihan != 0);
}

/* -------------------------------- MAHASISWA ------------------------------- */
void tambahMhs() {
    cout << "\n===== TAMBAH MAHASISWA =====\n";
    cout << "Masukkan NPM: ";
    cin >> daftarMhs[jumlahMhs].npm;

    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, daftarMhs[jumlahMhs].nama);

    string email = daftarMhs[jumlahMhs].npm + "@student.unsika.ac.id";
    tambahAkun(email, "123", "mahasiswa");
    jumlahMhs++;
    cout << "\nMahasiswa berhasil ditambahkan!.\n";
}

string keHurufKecil(string str) {
    string hasil = "";
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch + 32; // ubah huruf besar ke huruf kecil
        }
        hasil += ch;
    }
    return hasil;
}

void sortMhsByNama() { // menggunakan bubble sort
    for (int i = 0; i < jumlahMhs - 1; i++) {
        for (int j = i + 1; j < jumlahMhs; j++) {
            if (keHurufKecil(daftarMhs[i].nama) > keHurufKecil(daftarMhs[j].nama)) {
                swap(daftarMhs[i], daftarMhs[j]); //
            }
        }
    }
}

void sortMhsByNPM() { // menggunakan bubble sort
    for (int i = 0; i < jumlahMhs - 1; i++) {
        for (int j = i + 1; j < jumlahMhs; j++) {
            if (daftarMhs[i].npm > daftarMhs[j].npm) { swap(daftarMhs[i], daftarMhs[j]); }
        }
    }
}

void tampilMhs() {
    cout << "\n===== DAFTAR MAHASISWA =====\n";

    if (jumlahMhs == 0) {
        cout << "jumlah mahasiswa masih kosong.\n";
        return;
    }

    for (int i = 0; i < jumlahMhs; i++) {
        cout << i + 1 << ". " << daftarMhs[i].nama << " - " << daftarMhs[i].npm << endl;
    }

    cout << "\nJumlah Mahasiswa: " << jumlahMhs << endl;

    cout << "\nUrutkan berdasarkan:" << endl;
    cout << "1. Nama\n";
    cout << "2. NPM\n";
    cout << "3. Kembali\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            sortMhsByNama();
            tampilMhs();
            break;
        case 2:
            sortMhsByNPM();
            tampilMhs();
            break;
        case 3 : return;

        default: break;
    }

    cin.fail();
    cin.clear();
    cin.ignore(1000, '\n');
}

int findMhs(string npm) {
    for (int i = 0; i < jumlahMhs; i++) {
        if (daftarMhs[i].npm == npm) { return i; }
    }
    return -1;
}

void cariMhs(string npm) {
    int idx = findMhs(npm);
    if (idx != -1) {
        cout << "\nNama\t: " << daftarMhs[idx].nama << endl;
        cout << "NPM\t: " << daftarMhs[idx].npm << endl;
    } else {
        cout << "\nMahasiswa tidak ditemukan.\n";
    }
}

void editMhs(string npm) {
    int idx = findMhs(npm);
    if (idx == -1) {
        return; //
    }
    cout << "\nMasukkan Nama Baru: ";
    cin.ignore();
    getline(cin, daftarMhs[idx].nama);
    cout << "\nMahasiswa berhasil diubah.\n";
}

void hapusMhs(string npm) {
    int idx = findMhs(npm);
    if (idx == -1) { return; }
    for (int i = idx; i < jumlahMhs - 1; i++) { daftarMhs[i] = daftarMhs[i + 1]; }
    jumlahMhs--;
    cout << "\nMahasiswa berhasil dihapus.\n";
}

/* ------------------------ DOSEN ------------------------ */
void tambahDosen() {
    cout << "\n===== TAMBAH DOSEN =====\n";
    cout << "Masukkan NIP: ";
    cin >> daftarDosen[jumlahDosen].nip;
    cout << "Masukkan Nama: ";
    cin.ignore();
    getline(cin, daftarDosen[jumlahDosen].nama);
    string email = daftarDosen[jumlahDosen].nip + "@staff.unsika.ac.id";
    tambahAkun(email, "123", "dosen");
    jumlahDosen++;
    cout << "\nDosen berhasil ditambahkan!\n";
}

void sortDosenByNama() { // menggunakan bubble sort
    for (int i = 0; i < jumlahDosen - 1; i++) {
        for (int j = i + 1; j < jumlahDosen; j++) {
            if (keHurufKecil(daftarDosen[i].nama) > keHurufKecil(daftarDosen[j].nama)) {
                swap(daftarDosen[i], daftarDosen[j]); //
            }
        }
    }
}

void sortDosenByNIP() { // menggunakan bubble sort
    for (int i = 0; i < jumlahDosen - 1; i++) {
        for (int j = i + 1; j < jumlahDosen; j++) {
            if (daftarDosen[i].nip > daftarDosen[j].nip) {
                swap(daftarDosen[i], daftarDosen[j]); //
            }
        }
    }
}

void tampilDosen() {
    cout << "\n===== DAFTAR DOSEN =====\n";

    if (jumlahDosen == 0) {
        cout << "Dosen masih kosong.\n";
        return;
    }

    for (int i = 0; i < jumlahDosen; i++) {
        cout << i + 1 << ". " << daftarDosen[i].nama << " - " << daftarDosen[i].nip << endl;
    }

    cout << "\nJumlah Dosen: " << jumlahDosen << endl;

    cout << "\nUrutkan berdasarkan:" << endl;
    cout << "1. Nama\n";
    cout << "2. NIP\n";
    cout << "3. Kembali\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            sortDosenByNama();
            tampilDosen();
            break;
        case 2:
            sortDosenByNIP();
            tampilDosen();
            break;
        case 3 : return;

        default: break;
    }

    cin.fail();
    cin.clear();
    cin.ignore(1000, '\n');
}

int findDosen(string nip) {
    for (int i = 0; i < jumlahDosen; i++) {
        if (daftarDosen[i].nip == nip) { return i; }
    }
    return -1;
}

void cariDosen(string nip) {
    int idx = findDosen(nip);
    if (idx != -1) {
        cout << "\nNama\t: " << daftarDosen[idx].nama << endl;
        cout << "NIP\t: " << daftarDosen[idx].nip << endl;
    } else {
        cout << "Dosen tidak ditemukan.\n";
    }
}

void editDosen(string nip) {
    int idx = findDosen(nip);
    if (idx == -1) { return; }
    cout << "\nMasukkan Nama Baru: ";
    cin.ignore();
    getline(cin, daftarDosen[idx].nama);
    cout << "\nDosen berhasil diubah!\n";
}

void hapusDosen(string nip) {
    int idx = findDosen(nip);
    if (idx == -1) { return; }
    for (int i = idx; i < jumlahDosen - 1; i++) { daftarDosen[i] = daftarDosen[i + 1]; }
    jumlahDosen--;
    cout << "\nDosen berhasil dihapus!\n";
}

/* ------------------------ MATKUL ------------------------ */
void tambahMatkul() {
    cout << "\nMasukkan Kode: ";
    cin >> daftarMatkul[jumlahMatkul].kode;

    // jika kode sudah ada
    for (int i = 0; i < jumlahMatkul; i++) {
        if (daftarMatkul[i].kode == daftarMatkul[jumlahMatkul].kode) {
            cout << "Kode mata kuliah sudah ada.\n";
            return;
        }
    }

    cout << "Masukkan Nama Mata Kuliah: ";
    cin.ignore();
    getline(cin, daftarMatkul[jumlahMatkul].nama);
    cout << "Masukkan SKS: ";
    cin >> daftarMatkul[jumlahMatkul].sks;
    cout << "Masukkan NIP Dosen Pengampu: ";
    cin >> daftarMatkul[jumlahMatkul].nip_dosen;

    // jika dosen tidak ditemukan
    if (findDosen(daftarMatkul[jumlahMatkul].nip_dosen) == -1) {
        cout << "Dosen tidak ditemukan.\n";
        return;
    }

    jumlahMatkul++;
    cout << "\nMata Kuliah berhasil ditambahkan!\n";
}

Dosen *getDosenByNIP(string nip) {
    for (int i = 0; i < jumlahDosen; i++) {
        if (daftarDosen[i].nip == nip) { return &daftarDosen[i]; }
    }
    return NULL;
}

void sortMatkulByNama() { // menggunakan bubble sort
    for (int i = 0; i < jumlahMatkul - 1; i++) {
        for (int j = i + 1; j < jumlahMatkul; j++) {
            if (keHurufKecil(daftarMatkul[i].nama) > keHurufKecil(daftarMatkul[j].nama)) {
                swap(daftarMatkul[i], daftarMatkul[j]); //
            }
        }
    }
}

void sortMatkulByKode() { // menggunakan bubble sort
    for (int i = 0; i < jumlahMatkul - 1; i++) {
        for (int j = i + 1; j < jumlahMatkul; j++) {
            if (daftarMatkul[i].kode > daftarMatkul[j].kode) { swap(daftarMatkul[i], daftarMatkul[j]); }
        }
    }
}

void tampilMatkul() {
    cout << "\n===== DAFTAR MATA KULIAH =====\n";
    if (jumlahMatkul == 0) {
        cout << "Belum ada mata kuliah.\n";
        return;
    }
    for (int i = 0; i < jumlahMatkul; i++) {
        cout << i + 1 << ". " << daftarMatkul[i].kode << " - " << daftarMatkul[i].nama
             << " (SKS: " << daftarMatkul[i].sks
             << ", Dosen: " << getDosenByNIP(daftarMatkul[i].nip_dosen)->nama << ")\n";
    }

    cout << "\nUrutkan berdasarkan:" << endl;
    cout << "1. Nama\n";
    cout << "2. Kode Mata Kuliah\n";
    cout << "3. Kembali\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            sortMatkulByNama();
            tampilMatkul();
            break;
        case 2:
            sortMatkulByKode();
            tampilMatkul();
            break;
        case 3 : return;

        default: break;
    }

    cin.fail();
    cin.clear();
    cin.ignore(1000, '\n');
}

int findMatkul(string kode) {
    for (int i = 0; i < jumlahMatkul; i++) {
        if (daftarMatkul[i].kode == kode) { return i; }
    }
    return -1;
}

void cariMatkul(string kode) {
    int idx = findMatkul(kode);
    if (idx != -1) {
        cout << "\nNama Mata Kuliah\t: " << daftarMatkul[idx].nama << endl;
        cout << "Kode\t: " << daftarMatkul[idx].kode << endl;
        cout << "SKS\t: " << daftarMatkul[idx].sks << endl;
        cout << "Dosen Pengampu\t: " << getDosenByNIP(daftarMatkul[idx].nip_dosen)->nama << endl;
    } else {
        cout << "\nMata Kuliah tidak ditemukan.\n";
    }
}

void editMatkul(string kode) {
    int idx = findMatkul(kode);
    if (idx == -1) { return; }
    cout << "Masukkan Nama Mata Kuliah Baru: ";
    cin.ignore();
    getline(cin, daftarMatkul[idx].nama);

    cout << "Masukkan SKS Baru: ";
    cin >> daftarMatkul[idx].sks;

    cout << "Masukkan NIP Dosen Pengampu Baru: ";
    cin >> daftarMatkul[idx].nip_dosen;

    cout << "\nMatkul berhasil diubah.\n";
}

void hapusMatkul(string kode) {
    int idx = findMatkul(kode);
    if (idx == -1) { return; }
    for (int i = idx; i < jumlahMatkul - 1; i++) { daftarMatkul[i] = daftarMatkul[i + 1]; }
    jumlahMatkul--;
    cout << "Matkul berhasil dihapus.\n";
}
