#ifndef DOSEN_H
#define DOSEN_H

#include "../struct.h"

void menuDosen(Akun *user);

Dosen *getDosenByEmail(string email);
void   tampilMatkulDosen(Dosen *dsn);
void   tampilProfil(Dosen *dsn);

#endif