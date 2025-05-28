#ifndef SISKA_H
#define SISKA_H

#include "struct/struct.h"

void   tampilkanBanner();
void   tambahAkun(string email, string password, string role);
Akun  *login();
string keHurufKecil(string str);

#endif