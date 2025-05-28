#include <iostream>
#include <string>
using namespace std;

#include "admin/admin.h"
#include "dosen/dosen.h"
#include "mahasiswa/mahasiswa.h"
#include "siska.h"
#include "struct.h"

int pilihan;

void tampilMatkulDosen(string email);

/* ---------------------- FUNGSI UNTUK KELOLA KRS --------------------- */
// void tambahKrs(Mhs *m);
// void tampilKrs(Mhs *m);

// Mhs    *getMahasiswaByEmail(string email);
// Dosen  *getDosenByNIP(string nip);
// Matkul *getMatkulByKode(string kode);
// void    sortMhs();
// void    sortMatkul();

/* ---------------------------- BANNER BIAR KEREN --------------------------- */
void tampilkanBanner() {
    cout << R"(
 ______  __  ______  __  __   ______
/\  ___\/\ \/\  ___\/\ \/ /  /\  __ \
\ \___  \ \ \ \___  \ \  _"-.\ \  __ \
 \/\_____\ \_\/\_____\ \_\ \_\\ \_\ \_\
  \/_____/\/_/\/_____/\/_/\/_/ \/_/\/_/
    )";
}

/* ---------------------------------- LOGIN --------------------------------- */
Akun *login() {
    string email, password;
    Akun  *result  = nullptr;
    int    attempt = 3;

    tampilkanBanner();

    while (!result && attempt > 0) {
        cout << "\n---------------------------------\n";
        cout << "\tLOGIN KE AKUN SISKA\n";
        cout << "---------------------------------\n";

        cout << "Masukkan email: ";
        cin >> email;

        cout << "Masukkan password: ";
        cin >> password;

        for (int i = 0; i < jumlahAkun; i++) {
            if (email == daftarAkun[i].email && password == daftarAkun[i].password) {
                result = &daftarAkun[i];
                cout << "Login berhasil!\n";
                if (daftarAkun[i].role == "admin") {
                    cout << "Selamat datang, " << daftarAkun[i].role << "!\n";
                } else if (daftarAkun[i].role == "dosen") {
                    string nip = daftarAkun[i].email.substr(0, daftarAkun[i].email.find("@"));
                    for (int j = 0; j < jumlahDosen; j++) {
                        if (daftarDosen[j].nip == nip) {
                            cout << "Selamat datang, " << daftarDosen[j].nama << "!\n";
                            break;
                        }
                    }
                } else if (daftarAkun[i].role == "mahasiswa") {
                    string npm = daftarAkun[i].email.substr(0, daftarAkun[i].email.find("@"));
                    for (int j = 0; j < jumlahMhs; j++) {
                        if (daftarMhs[j].npm == npm) {
                            cout << "Selamat datang, " << daftarMhs[j].nama << "!\n";
                            break;
                        }
                    }
                }

                break;
            }
        }

        if (!result) {
            cout << "Login gagal. Silakan coba lagi.\n";
            attempt--;
            cout << "Sisa percobaan: " << attempt << endl;
        }
    }

    if (!result) {
        cout << "\nTerlalu banyak percobaan. Program keluar.\n"; //
    }
    return result;
}

/* ------------------------------- TAMBAH AKUN ------------------------------ */
void tambahAkun(string email, string password, string role) {
    daftarAkun[jumlahAkun] = {email, password, role};
    jumlahAkun++;
}

int main() {
    tambahAkun("adminsiska@unsika.ac.id", "admin1234", "admin");

    while (true) {
        Akun *user = login();
        if (!user) { break; }

        if (user->role == "admin") {
            menuAdmin();
        } else if (user->role == "dosen") {
            menuDosen(user);
        } else if (user->role == "mahasiswa") {
            menuMhs(user);
        }

        cout << "\nLogout... Kembali ke halaman login.\n";
    }

    cout << "\nTerima kasih, selamat tinggal!.\n";

    return 0;
}