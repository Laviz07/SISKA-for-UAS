#include <iostream>
#include <string>
using namespace std;

// includes
#include "admin/admin.h"
#include "dosen/dosen.h"
#include "mahasiswa/mahasiswa.h"
#include "siska.h"
#include "struct/struct.h"

int pilihan;

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

    // jika percobaan login belum habis dan user belum berhasil login
    while (!result && attempt > 0) {
        cout << "\n---------------------------------\n";
        cout << "\tLOGIN KE AKUN SISKA\n";
        cout << "---------------------------------\n";

        cout << "Masukkan email: ";
        cin >> email;

        cout << "Masukkan password: ";
        cin >> password;

        // linear search untuk mencari akun
        for (int i = 0; i < jumlahAkun; i++) {
            // jika email dan password cocok
            if (email == daftarAkun[i].email && password == daftarAkun[i].password) {
                result = &daftarAkun[i];                    // akun ditemukan
                cout << "Login berhasil!\n";

                if (daftarAkun[i].role == "admin") {        // jika rolenya adalah admin
                    cout << "Selamat datang, " << daftarAkun[i].role << "!\n";

                } else if (daftarAkun[i].role == "dosen") { // jika rolenya adalah dosen
                    // mengambil nip sebelum @
                    string nip = daftarAkun[i].email.substr(0, daftarAkun[i].email.find("@"));
                    for (int j = 0; j < jumlahDosen; j++) {
                        if (daftarDosen[j].nip == nip) { // jika nip cocok
                            cout << "Selamat datang, " << daftarDosen[j].nama << "!\n";
                            break;
                        }
                    }

                } else if (daftarAkun[i].role == "mahasiswa") { // jika rolenya adalah mahasiswa
                    // mengambil npm sebelum @
                    string npm = daftarAkun[i].email.substr(0, daftarAkun[i].email.find("@"));
                    for (int j = 0; j < jumlahMhs; j++) {
                        if (daftarMhs[j].npm == npm) { // jika npm cocok
                            cout << "Selamat datang, " << daftarMhs[j].nama << "!\n";
                            break;
                        }
                    }
                }
                break;
            }
        }

        // jika akun tidak ditemukan
        if (!result) {
            cout << "Login gagal. Silakan coba lagi.\n";
            attempt--; // mengurangi percobaan
            cout << "Sisa percobaan: " << attempt << endl;
        }
    }

    // jika percobaan login habis
    if (!result) {
        cout << "\nTerlalu banyak percobaan. Keluar dari aplikasi.\n"; //
    }
    return result;
}

/* ------------------------------- TAMBAH AKUN ------------------------------ */
void tambahAkun(string email, string password, string role) {
    daftarAkun[jumlahAkun] = {email, password, role}; // memasukkan data akun
    jumlahAkun++;                                     // jumlah akun bertambah
}

/* --------------------- KONVERSI STRING KE HURUF KECIL --------------------- */
string keHurufKecil(string str) {
    string hasil = "";

    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];             // mengambil karakter
        if (ch >= 'A' && ch <= 'Z') { // jika ch merupakan huruf besar
            ch = ch + 32;             // ubah huruf besar ke huruf kecil
        }
        hasil += ch;                  // tambahkan karakter ch ke hasil
    }
    return hasil;
}

int main() {
    // menambahkan akun admin
    tambahAkun("adminsiska@unsika.ac.id", "admin123", "admin");


    while (true) {
        Akun *user = login(); // usernya hasil dari login
        if (!user) { break; } // jika tidak ada user, maka berheni

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