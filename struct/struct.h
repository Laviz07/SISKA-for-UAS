#ifndef STRUCT_H
#define STRUCT_H

#include <string>
using namespace std;

struct Akun {
        string email, password, role;
};

struct Dosen {
        string nip, nama;
};

struct Mhs {
        string          npm, nama;
        struct NodeKrs *krs = nullptr;
};

struct Matkul {
        string kode, nama, nip_dosen;
        int    sks;
};

struct NodeKrs {
        Matkul  *mk;
        NodeKrs *next;
};

const int     MAX = 50;
extern Matkul daftarMatkul[MAX];
extern Mhs    daftarMhs[MAX];
extern Dosen  daftarDosen[MAX];
extern Akun   daftarAkun[MAX];

extern int jumlahAkun, jumlahMhs, jumlahDosen, jumlahMatkul;
extern int pilihan;

#endif