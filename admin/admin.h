#ifndef ADMIN_H
#define ADMIN_H

#include "../struct.h"

void menuAdmin();

/* ---------------------- FUNGSI UNTUK KELOLA MAHASISWA --------------------- */
void tambahMhs();
void tampilMhs();
void cariMhs(string npm);
void editMhs(string npm);
void hapusMhs(string npm);
int  findMhs(string npm);

/* ---------------------- FUNGSI UNTUK KELOLA DOSEN --------------------- */
void tambahDosen();
void tampilDosen();
void cariDosen(string nip);
void editDosen(string nip);
void hapusDosen(string nip);
int  findMhs(string nip);

/* ---------------------- FUNGSI UNTUK KELOLA MATA KULIAH --------------------- */
void tambahMatkul();
void tampilMatkul();
void cariMatkul(string kode);
void editMatkul(string kode);
void hapusMatkul(string kode);
int  findMatkul(string kode);

#endif