#include "admin.h"

#include "../siska.h"

#include <iostream>
#include <string>
using namespace std;

/* ------------------------------- MENU ADMIN ------------------------------- */
void menuAdmin() {
    int pilihanUtama, pilihanMahasiswa, pilihanDosen, pilihanMatkul;
    tampilkanBanner();
    do {
        cout << "\n---------- MENU UTAMA ADMIN ----------\n";
        cout << "1. Kelola Mahasiswa\n";
        cout << "2. Kelola Dosen\n";
        cout << "3. Kelola Mata Kuliah\n";
        cout << "4. Logout\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihanUtama;

        // jika input tidak valid
        if (cin.fail()) {
            cin.clear();            // membersihkan buffer
            cin.ignore(1000, '\n'); // mengabaikan input sebelumnya
            cout << "Input tidak valid. Harap masukkan angka.\n";
            continue;               // kembali ke awal loop
        }

        switch (pilihanUtama) {
            case 1:
                do {
                    cout << "\n===== KELOLA MAHASISWA =====\n";
                    cout << "1. Tambah Mahasiswa\n";
                    cout << "2. Lihat Daftar Mahasiswa\n";
                    cout << "3. Cari Mahasiswa\n";
                    cout << "4. Edit Mahasiswa\n";
                    cout << "5. Hapus Mahasiswa\n";
                    cout << "6. Kembali\n";
                    cout << "Masukkan pilihan anda: ";
                    cin >> pilihanMahasiswa;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Input tidak valid. Harap masukkan angka.\n";
                        continue; // kembali ke awal loop
                    }

                    switch (pilihanMahasiswa) {
                        case 1 : tambahMhs(); break;
                        case 2 : tampilMhs(); break;
                        case 3 : cariMhs(); break;
                        case 4 : editMhs(); break;
                        case 5 : hapusMhs(); break;
                        case 6 : break;
                        default: cout << "Pilihan tidak tersedia" << endl;
                    }

                } while (pilihanMahasiswa != 6);
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
                    cout << "Masukkan pilihan anda: ";
                    cin >> pilihanDosen;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Input tidak valid. Harap masukkan angka.\n";
                        continue; // kembali ke awal loop
                    }

                    switch (pilihanDosen) {
                        case 1 : tambahDosen(); break;
                        case 2 : tampilDosen(); break;
                        case 3 : cariDosen(); break;
                        case 4 : editDosen(); break;
                        case 5 : hapusDosen(); break;
                        case 6 : break;
                        default: cout << "Pilihan tidak tersedia" << endl;
                    }

                } while (pilihanDosen != 6);
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
                    cout << "Masukkan pilihan anda: ";
                    cin >> pilihanMatkul;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Input tidak valid. Harap masukkan angka.\n";
                        continue; // kembali ke awal loop
                    }

                    switch (pilihanMatkul) {
                        case 1 : tambahMatkul(); break;
                        case 2 : tampilMatkul(); break;
                        case 3 : cariMatkul(); break;
                        case 4 : editMatkul(); break;
                        case 5 : hapusMatkul(); break;
                        case 6 : break;
                        default: cout << "Pilihan tidak tersedia" << endl;
                    }
                } while (pilihanMatkul != 6);
                break;

            default: cout << "Pilihan tidak tersedia" << endl; break;
        }
    } while (pilihanUtama != 4);
}

// fungsi untuk mencari indeks mahasiswa
int findMhs(string npm) {
    for (int i = 0; i < jumlahMhs; i++) {
        if (daftarMhs[i].npm == npm) { // jika npm mahasiswa ke-i sama dengan npm yang dicari
            return i;                  // maka kembalikan indeks mahasiswa
        }
    }
    return -1;                         // jika tidak ditemukan, kembalikan -1
}

/* -------------------------------- MAHASISWA ------------------------------- */
void tambahMhs() {
    cout << "\n===== TAMBAH MAHASISWA =====\n";
    cout << "Masukkan NPM: ";
    cin >> daftarMhs[jumlahMhs].npm;

    // jika NPM sudah terdaftar
    if (findMhs(daftarMhs[jumlahMhs].npm) != -1) {
        cout << "\nNPM sudah terdaftar.\n";
        return;
    }

    cout << "Masukkan Nama: ";
    cin.ignore();                            // membersihkan buffer
    getline(cin, daftarMhs[jumlahMhs].nama); // membaca input dengan spasi

    // membuat email mahasiswa berdasarkan NPM
    string email = daftarMhs[jumlahMhs].npm + "@student.unsika.ac.id";
    tambahAkun(email, "123", "mahasiswa"); // menambahkan akun
    jumlahMhs++;                           // jumlah mahasiswa bertambah
    cout << "\nMahasiswa berhasil ditambahkan!.\n";
}

// fungsi untuk mengurutkan daftar mahasiswa berdasarkan Nama menggunakan bubble sort
void sortMhsByNama() {
    // looping sebanyak jumlah mahasiswa - 1 karena array dimulai dari index 0
    for (int i = 0; i < jumlahMhs - 1; i++) {
        // i+1 karena looping dimulai dari index 1
        for (int j = i + 1; j < jumlahMhs; j++) {
            // jika nama mahasiswa ke-i lebih besar dari nama mahasiswa ke-j
            if (keHurufKecil(daftarMhs[i].nama) > keHurufKecil(daftarMhs[j].nama)) {
                swap(daftarMhs[i], daftarMhs[j]); // tukar posisinya
            }
        }
    }
}

// fungsi untuk mengurutkan daftar mahasiswa berdasarkan Npm menggunakan bubble sort
void sortMhsByNPM() {
    for (int i = 0; i < jumlahMhs - 1; i++) {
        for (int j = i + 1; j < jumlahMhs; j++) {
            // jika npm mahasiswa ke-i lebih besar dari npm mahasiswa ke-j
            if (daftarMhs[i].npm > daftarMhs[j].npm) {
                swap(daftarMhs[i], daftarMhs[j]); // tukar posisinya
            }
        }
    }
}

// fungsi untuk menampilkan daftar mahasiswa
void tampilMhs() {
    int pilihSort;
    cout << "\n===== DAFTAR MAHASISWA =====\n";

    if (jumlahMhs == 0) {
        cout << "\nJumlah mahasiswa masih kosong.\n";
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
    cout << "Masukkan pilihan anda: ";
    cin >> pilihSort;

    switch (pilihSort) {
        case 1:
            sortMhsByNama();
            tampilMhs();
            break;
        case 2:
            sortMhsByNPM();
            tampilMhs();
            break;
        case 3 : return;

        default: cout << "Pilihan tidak tersedia" << endl; break;
    }

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

// fungsi untuk mencari mahasiswa
void cariMhs() {
    // jika mahasiswa masih kosong
    if (jumlahMhs == 0) {
        cout << "\nJumlah mahasiswa masih kosong.\n";
        return;
    }

    cout << "\n===== CARI MAHASISWA =====\n";

    string npm;
    cout << "Masukkan NPM: ";
    cin >> npm;
    int idx = findMhs(npm); // mencari indeks mahasiswa

    if (idx != -1) {        // jika mahasiswa ditemukan
        cout << "\nNama\t: " << daftarMhs[idx].nama << endl;
        cout << "NPM\t: " << daftarMhs[idx].npm << endl;
    } else {
        cout << "\nMahasiswa tidak ditemukan.\n";
    }
}

// fungsi untuk mengedit mahasiswa
void editMhs() {
    // jika mahasiswa masih kosong
    if (jumlahMhs == 0) {
        cout << "\nJumlah mahasiswa masih kosong.\n";
        return;
    }

    cout << "\n===== EDIT MAHASISWA =====\n";

    string npm;
    cout << "Masukkan NPM: ";
    cin >> npm;
    int idx = findMhs(npm); // mencari indeks mahasiswa

    // jika mahasiswa tidak ditemukan
    if (idx == -1) {
        cout << "\nMahasiswa tidak ditemukan.\n";
        return;                        //
    }
    cout << "\nMasukkan Nama Baru: ";
    cin.ignore();                      // membersikan buffer
    getline(cin, daftarMhs[idx].nama); // mengubah nama mahasiswa
    cout << "\nMahasiswa berhasil diubah.\n";
}

// fungsi untuk menghapus mahasiswa
void hapusMhs() {
    // jika mahasiswa masih kosong
    if (jumlahMhs == 0) {
        cout << "\nJumlah mahasiswa masih kosong.\n";
        return;
    }

    cout << "\n===== HAPUS MAHASISWA =====\n";

    string npm;
    cout << "Masukkan NPM: ";
    cin >> npm;
    int idx = findMhs(npm); // mencari indeks mahasiswa

    if (idx == -1) {        // jika mahasiswa tidak ditemukan
        cout << "\nMahasiswa tidak ditemukan.\n";
        return;
    }

    // perulangan untuk menghapus mahasiswa
    for (int i = idx; i < jumlahMhs - 1; i++) {
        daftarMhs[i] = daftarMhs[i + 1]; // mengganti mahasiswa dengan mahasiswa selanjutnya
    }
    jumlahMhs--;                         // jumlah mahasiswa berkurang
    cout << "\nMahasiswa berhasil dihapus.\n";
}

/* ------------------------ DOSEN ------------------------ */
void tambahDosen() {
    cout << "\n===== TAMBAH DOSEN =====\n";
    cout << "Masukkan NIP: ";
    cin >> daftarDosen[jumlahDosen].nip;

    if (findDosen(daftarDosen[jumlahDosen].nip) != -1) {
        cout << "\nNIP tersebut sudah terdaftar.\n"; //
        return;
    }

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
    int pilihSort;
    cout << "\n===== DAFTAR DOSEN =====\n";

    if (jumlahDosen == 0) {
        cout << "\nDosen masih kosong.\n";
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
    cout << "Masukkan pilihan anda: ";
    cin >> pilihSort;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input tidak valid. Harap masukkan angka.\n";
    }

    switch (pilihSort) {
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
}

int findDosen(string nip) {
    for (int i = 0; i < jumlahDosen; i++) {
        if (daftarDosen[i].nip == nip) { return i; }
    }
    return -1;
}

void cariDosen() {
    // jika mahasiswa masih kosong
    if (jumlahDosen == 0) {
        cout << "\nJumlah dosen masih kosong.\n";
        return;
    }

    cout << "\n===== CARI DOSEN =====\n";

    string nip;
    cout << "Masukkan NIP: ";
    cin >> nip;

    int idx = findDosen(nip);

    if (idx != -1) {
        cout << "\nNama\t: " << daftarDosen[idx].nama << endl;
        cout << "NIP\t: " << daftarDosen[idx].nip << endl;
    } else {
        cout << "\nDosen tidak ditemukan.\n";
    }
}

void editDosen() {
    // jika mahasiswa masih kosong
    if (jumlahDosen == 0) {
        cout << "\nJumlah dosen masih kosong.\n";
        return;
    }

    cout << "\n===== EDIT DOSEN =====\n";

    string nip;
    cout << "Masukkan NIP: ";
    cin >> nip;

    int idx = findDosen(nip);

    // jika Dosen tidak ditemukan
    if (idx == -1) {
        cout << "\nDosen tidak ditemukan.\n";
        return;
    }

    cout << "\nMasukkan Nama Baru: ";
    cin.ignore();
    getline(cin, daftarDosen[idx].nama);
    cout << "\nDosen berhasil diubah!\n";
}

void hapusDosen() {
    // jika mahasiswa masih kosong
    if (jumlahDosen == 0) {
        cout << "\nJumlah dosen masih kosong.\n";
        return;
    }

    cout << "\n===== HAPUS DOSEN =====\n";

    string nip;
    cout << "Masukkan NIP: ";
    cin >> nip;

    int idx = findDosen(nip);

    // jika Dosen tidak ditemukan
    if (idx == -1) {
        cout << "\nDosen tidak ditemukan.\n";
        return;
    }

    for (int i = idx; i < jumlahDosen - 1; i++) { daftarDosen[i] = daftarDosen[i + 1]; }
    jumlahDosen--;
    cout << "\nDosen berhasil dihapus!\n";
}

/* ------------------------ MATKUL ------------------------ */
void tambahMatkul() {
    cout << "\n===== TAMBAH MATA KULIAH =====\n";
    cout << "Masukkan Kode: ";
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
    int pilihSort;
    cout << "\n===== DAFTAR MATA KULIAH =====\n";
    if (jumlahMatkul == 0) {
        cout << "\nBelum ada mata kuliah.\n";
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
    cout << "Masukkan pilihan anda: ";
    cin >> pilihSort;

    switch (pilihSort) {
        case 1:
            sortMatkulByNama();
            tampilMatkul();
            break;
        case 2:
            sortMatkulByKode();
            tampilMatkul();
            break;
        case 3 : return;

        default: cout << "Pilihan tidak tersedia" << endl; break;
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

void cariMatkul() {
    if (jumlahMatkul == 0) {
        cout << "\nJumlah Mata Kuliah masih kosong.\n";
        return;
    }

    cout << "\n===== CARI MATA KULIAH =====\n";

    string kode;
    cout << "Masukkan kode Mata Kuliah: ";
    cin >> kode;

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

void editMatkul() {
    if (jumlahMatkul == 0) {
        cout << "\nJumlah Mata Kuliah masih kosong.\n";
        return;
    }

    cout << "\n===== EDIT MATA KULIAH =====\n";

    string kode;
    cout << "Masukkan kode Mata Kuliah: ";
    cin >> kode;

    int idx = findMatkul(kode);
    // jika Mata Kuliah tidak ditemukan
    if (idx == -1) {
        cout << "\nMata Kuliah tidak ditemukan.\n";
        return;
    }

    cout << "Masukkan Nama Mata Kuliah Baru: ";
    cin.ignore();
    getline(cin, daftarMatkul[idx].nama);

    cout << "Masukkan SKS Baru: ";
    cin >> daftarMatkul[idx].sks;

    cout << "Masukkan NIP Dosen Pengampu Baru: ";
    cin >> daftarMatkul[idx].nip_dosen;

    cout << "\nMatkul berhasil diubah.\n";
}

void hapusMatkul() {
    if (jumlahMatkul == 0) {
        cout << "\nJumlah Mata Kuliah masih kosong.\n";
        return;
    }

    cout << "\n===== HAPUS MATA KULIAH =====\n";

    string kode;
    cout << "Masukkan kode Mata Kuliah: ";
    cin >> kode;

    int idx = findMatkul(kode);

    // jika Mata kuliah tidak ditemukan
    if (idx == -1) {
        cout << "\nMata kuliah tidak ditemukan.\n";
        return;
    }
    for (int i = idx; i < jumlahMatkul - 1; i++) { daftarMatkul[i] = daftarMatkul[i + 1]; }
    jumlahMatkul--;
    cout << "Matkul berhasil dihapus.\n";
}
