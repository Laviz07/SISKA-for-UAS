#include "mahasiswa.h"

#include "../admin/admin.h"
#include "../siska.h"
#include "../struct.h"

#include <iostream>

using namespace std;

void menuMhs(Akun *user) {
    tampilkanBanner();

    Mhs *mhs = getMhsByEmail(user->email);
    if (!mhs) {
        cout << "Mahasiswa tidak ditemukan!\n";
        return;
    }

    do {
        cout << "\n---------- MENU UTAMA MAHASISWA ----------\n";
        cout << "1. Lihat KRS\n";
        cout << "2. Ambil Mata Kuliah\n";
        cout << "3. Hapus Mata Kuliah dari KRS\n";
        cout << "0. Logout\n";
        cout << "Masukkan pilihan anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1 : tampilKrs(mhs); break;
            case 2 : tambahKrs(mhs); break;
            case 3 : hapusKrs(mhs); break;

            default: cout << "Pilihan tidak valid.\n"; break;
        }

    } while (pilihan != 0);
}

Mhs *getMhsByEmail(string email) {
    for (int i = 0; i < jumlahMhs; i++) {
        string expectedEmail = daftarMhs[i].npm + "@student.unsika.ac.id";
        if (email == expectedEmail) { return &daftarMhs[i]; }
    }
    return nullptr;
}

Matkul *getMatkulByKode(string kode) {
    for (int i = 0; i < jumlahMatkul; i++) {
        if (daftarMatkul[i].kode == kode) { return &daftarMatkul[i]; }
    }
    return NULL;
}

int hitungTotalSks(Mhs *mhs) {
    int      total = 0;
    NodeKrs *curr  = mhs->krs;
    while (curr != nullptr) {
        total += curr->mk->sks;
        curr = curr->next;
    }
    return total;
}

void tampilKrs(Mhs *mhs) {
    cout << "\n===== KARTU RENCANA STUDI =====\n";
    if (mhs->krs == nullptr) {
        cout << "\nBelum ada matkul di KRS.\n";
    } else {
        int      no   = 1;
        NodeKrs *curr = mhs->krs;
        while (curr != nullptr) {
            cout << no++ << ". " << curr->mk->kode << " - " << curr->mk->nama << " (SKS: " << curr->mk->sks
                 << ", Dosen: " << getDosenByNIP(curr->mk->nip_dosen)->nama << ")\n";
            curr = curr->next;
        }

        cout << "\nTotal SKS: " << hitungTotalSks(mhs) << endl;
    }
}

bool sudahAdaDiKrs(Mhs *mhs, string kode) {
    NodeKrs *curr = mhs->krs;
    while (curr != nullptr) {
        if (curr->mk->kode == kode) { return true; }
        curr = curr->next;
    }
    return false;
}

void tambahKrs(Mhs *mhs) {
    cout << "\n===== TAMBAH MATA KULIAH KE KRS =====\n";
    string kode;
    cout << "Masukkan kode matkul yang ingin diambil: ";
    cin >> kode;

    Matkul *mk = getMatkulByKode(kode);
    if (mk == nullptr) {
        cout << "Matkul tidak ditemukan.\n";
        return;
    }

    if (sudahAdaDiKrs(mhs, kode)) {
        cout << "Matkul sudah ada dalam KRS.\n";
        return;
    }

    NodeKrs *newNode = new NodeKrs;
    newNode->mk      = mk;
    newNode->next    = nullptr;

    if (mhs->krs == nullptr) {
        mhs->krs = newNode;
    } else {
        NodeKrs *curr = mhs->krs;
        while (curr->next != nullptr) { curr = curr->next; }
        curr->next = newNode;
    }

    cout << "Matkul berhasil ditambahkan ke KRS.\n";
}

void hapusKrs(Mhs *mhs) {
    if (mhs->krs == nullptr) {
        cout << "KRS masih kosong.\n";
        return;
    }
    
    string kode;
    cout << "\nMasukkan kode matkul yang ingin dihapus dari KRS: ";
    cin >> kode;

    if (!sudahAdaDiKrs(mhs, kode)) {
        cout << "Matkul tidak ada dalam KRS.\n";
        return;
    }

    NodeKrs *prev = nullptr;
    NodeKrs *curr = mhs->krs;

    while (curr != nullptr) {
        if (curr->mk->kode == kode) {
            if (prev == nullptr) {
                mhs->krs = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            cout << "Matkul berhasil dihapus dari KRS.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}