#ifndef ADMIN_H
#define ADMIN_H

#include "../struct.h"

void menuAdmin();

/* ---------------------- FUNGSI UNTUK KELOLA MAHASISWA --------------------- */
void tambahMhs();
void tampilMhs();
void cariMhs();
void editMhs();
void hapusMhs();
int  findMhs(string npm);

/* ---------------------- FUNGSI UNTUK KELOLA DOSEN --------------------- */
void tambahDosen();
void tampilDosen();
void cariDosen();
void editDosen();
void hapusDosen();
int  findDosen(string nip);

/* ---------------------- FUNGSI UNTUK KELOLA MATA KULIAH --------------------- */
Dosen *getDosenByNIP(string nip);

void tambahMatkul();
void tampilMatkul();
void cariMatkul();
void editMatkul();
void hapusMatkul();
int  findMatkul(string kode);

#endif