#ifndef MAHASISWA_H
#define MAHASISWA_H

#include "../struct/struct.h"

void menuMhs(Akun *user);
void tambahKrs(Mhs *m);
void tampilKrs(Mhs *m);
void hapusKrs(Mhs *m);
bool sudahAdaDiKrs(Mhs *mhs, string kode);
Mhs *getMhsByEmail(string email);
void tampilProfilMhs(Mhs *mhs);

#endif