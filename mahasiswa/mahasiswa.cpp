#include "mahasiswa.h"

#include "../admin/admin.h"
#include "../siska.h"
#include "../struct/struct.h"

#include <iostream>

using namespace std;

// fungsi untuk mendapatkan mahasiswa berdasarkan email
Mhs *getMhsByEmail(string email) {
    for (int i = 0; i < jumlahMhs; i++) {
        // jika email mahasiswa yang login sama dengan yang ada di daftar mahasiswa
        string expectedEmail = daftarMhs[i].npm + "@student.unsika.ac.id";
        if (email == expectedEmail) { // jika cocok
            return &daftarMhs[i];     // mengembalikan alamat mahasiswa
        }
    }
    return nullptr;
}

/* ----------------------------- MENU MAHASISWA ----------------------------- */
void menuMhs(Akun *user) {
    tampilkanBanner();

    Mhs *mhs = getMhsByEmail(user->email); // mendapatkan mahasiswa berdasarkan email
    if (!mhs) {                            // jika mahasiswa tidak ditemukan
        cout << "Mahasiswa tidak ditemukan!\n";
        return;
    }

    do {
        cout << "\n---------- MENU UTAMA MAHASISWA ----------\n";
        cout << "1. Lihat KRS\n";
        cout << "2. Ambil Mata Kuliah\n";
        cout << "3. Hapus Mata Kuliah dari KRS\n";
        cout << "4. Lihat Profil\n";
        cout << "5. Logout\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        // jika input tidak valid
        if (cin.fail()) {
            cin.clear();            // membersihkan buffer
            cin.ignore(1000, '\n'); // mengabaikan input sebelumnya
            cout << "Input tidak valid. Harap masukkan angka.\n";
        }

        switch (pilihan) {
            case 1 : tampilKrs(mhs); break;
            case 2 : tambahKrs(mhs); break;
            case 3 : hapusKrs(mhs); break;
            case 4 : tampilProfilMhs(mhs); break;

            default: cout << "Pilihan tidak valid.\n"; break;
        }

    } while (pilihan != 5);
}

// fungsi untuk mendapatkan matkul berdasarkan kode
Matkul *getMatkulByKode(string kode) {
    for (int i = 0; i < jumlahMatkul; i++) {
        if (daftarMatkul[i].kode == kode) { // jika kode matkul cocok dengan input
            return &daftarMatkul[i];        // mengembalikan alamat matkul
        }
    }
    return NULL;
}

// fungsi untuk menghitung total SKS
int hitungTotalSks(Mhs *mhs) {
    int      total = 0;
    NodeKrs *curr  = mhs->krs;  // mendapatkan node pertama dari KRS
    while (curr != nullptr) {   // perulangan untuk menghitung total SKS
        total += curr->mk->sks; // menambahkan SKS
        curr = curr->next;      // melanjutkan ke node selanjutnya
    }
    return total;
}

void tampilKrs(Mhs *mhs) {
    cout << "\n===== KARTU RENCANA STUDI =====\n";
    if (mhs->krs == nullptr) { // jika KRS masih kosong
        cout << "\nBelum ada matkul di KRS.\n";
    } else {
        int      no   = 1;
        NodeKrs *curr = mhs->krs;                  // mendapatkan node pertama dari KRS
        while (curr != nullptr) {                  // perulangan untuk menampilkan KRS
            cout << no++ << ". " << curr->mk->kode // menampilkan kode matkul
                 << " - " << curr->mk->nama        // menampilkan nama matkul
                 << " (SKS: " << curr->mk->sks     // menampilkan SKS
                 << ", Dosen: " << getDosenByNIP(curr->mk->nip_dosen)->nama // menampilkan nama dosen
                 << ")\n";
            curr = curr->next;
        }

        cout << "\nTotal SKS: " << hitungTotalSks(mhs) << endl; // menampilkan total SKS
    }
}

// fungsi untuk mengecek apakah matkul sudah ada di KRS
bool sudahAdaDiKrs(Mhs *mhs, string kode) {
    NodeKrs *curr = mhs->krs;         // mendapatkan node pertama dari KRS
    while (curr != nullptr) {
        if (curr->mk->kode == kode) { // jika kode matkul cocok
            return true;              // mengembalikan true
        }
        curr = curr->next;            // melanjutkan ke node selanjutnya
    }
    return false;                     // jika tidak ada matkul dengan kode tersebut, mengembalikan false
}

// fungsi untuk menambahkan matkul ke KRS
void tambahKrs(Mhs *mhs) {
    cout << "\n===== TAMBAH MATA KULIAH KE KRS =====\n";
    string kode;
    cout << "Masukkan kode matkul yang ingin diambil: ";
    cin >> kode;

    Matkul *mk = getMatkulByKode(kode); // mendapatkan matkul berdasarkan kode
    if (mk == nullptr) {                // jika matkul tidak ditemukan
        cout << "Matkul tidak ditemukan.\n";
        return;
    }

    if (sudahAdaDiKrs(mhs, kode)) { // jika matkul sudah ada di KRS
        cout << "Matkul sudah ada dalam KRS.\n";
        return;
    }

    NodeKrs *newNode = new NodeKrs;     // membuat node baru
    newNode->mk      = mk;              // mengisi node dengan matkul
    newNode->next    = nullptr;         // node selanjutnya kosong

    if (mhs->krs == nullptr) {          // jika KRS masih kosong
        mhs->krs = newNode;             // node baru menjadi node pertama
    } else {
        NodeKrs *curr = mhs->krs;       // mendapatkan node pertama
        while (curr->next != nullptr) { // selama node selanjutnya tidak kosong
            curr = curr->next;          // melanjutkan ke node selanjutnya
        }
        curr->next = newNode;           // node baru menjadi node terakhir
    }

    cout << "Matkul berhasil ditambahkan ke KRS.\n";
}

// fungsi untuk menghapus matkul dari KRS
void hapusKrs(Mhs *mhs) {
    cout << "\n===== HAPUS MATA KULIAH DARI KRS =====\n";
    if (mhs->krs == nullptr) { // jika KRS masih kosong
        cout << "KRS masih kosong.\n";
        return;
    }

    string kode;
    cout << "\nMasukkan kode matkul yang ingin dihapus dari KRS: ";
    cin >> kode;

    if (!sudahAdaDiKrs(mhs, kode)) { // jika matkul tidak ada di KRS
        cout << "Matkul tidak ada dalam KRS.\n";
        return;
    }

    NodeKrs *prev = nullptr;             // node sebelum node yang ingin dihapus
    NodeKrs *curr = mhs->krs;            // mendapatkan node pertama

    while (curr != nullptr) {            // selama node tidak kosong
        if (curr->mk->kode == kode) {    // jika kode matkul cocok
            if (prev == nullptr) {       // jika node sebelumnya kosong
                mhs->krs = curr->next;   // node selanjutnya menjadi node pertama
            } else {
                prev->next = curr->next; // node selanjutnya menjadi node sebelumnya
            }
            delete curr;                 // menghapus node
            cout << "Matkul berhasil dihapus dari KRS.\n";
            return;
        }
        prev = curr;       // node sebelumnya menjadi node saat ini
        curr = curr->next; // melanjutkan ke node selanjutnya
    }
}

// lihat profil
void tampilProfilMhs(Mhs *mhs) {
    cout << "\n===== PROFIL MAHASISWA =====\n";
    cout << "Nama\t: " << mhs->nama << endl;
    cout << "NPM\t: " << mhs->npm << endl;
    cout << "Email\t: " << mhs->npm << "@student.unsika.ac.id" << endl;
}