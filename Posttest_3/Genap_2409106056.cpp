#include <iostream>
#include <string>
#include <limits>
#include <iomanip> // PENGGANTI <cstdio> untuk memanipulasi output cout

using namespace std;

// === STRUCT DEFINITIONS (Double Linked List) ===
struct Penerbangan {
    string kodePenerbangan;
    string tujuan;
    string status;
    Penerbangan* next;
    Penerbangan* prev;
};

// === GLOBAL VARIABLES & POINTERS ===
Penerbangan* head = nullptr;
Penerbangan* tail = nullptr;

string namaMahasiswa = "";
string nimMahasiswa = "";
string basisKodePenerbangan = "JT-";
int posisiSisip = 0;
int counterJadwal = 0;
int jumlahJadwal = 0;

// === FUNCTION PROTOTYPES ===
void inisialisasiProgram();
void tampilkanMenu();
void tambahJadwal(Penerbangan*& head, Penerbangan*& tail);
void sisipkanJadwal(Penerbangan*& head, Penerbangan*& tail);
void hapusJadwalAwal(Penerbangan*& head, Penerbangan*& tail);
void updateStatusPenerbangan(Penerbangan* head);
void tampilkanDariDepan(Penerbangan* head);
void tampilkanDariBelakang(Penerbangan* tail);
void cariJadwalSpesifik(Penerbangan* head);
void clearScreen();
void pauseScreen();

// === MAIN FUNCTION ===
int main() {
    inisialisasiProgram();

    int pilihan;
    do {
        clearScreen();
        tampilkanMenu();
        cout << "   Masukkan Pilihan Anda: ";
        cin >> pilihan;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (pilihan) {
            case 1: tambahJadwal(head, tail); break;
            case 2: sisipkanJadwal(head, tail); break;
            case 3: hapusJadwalAwal(head, tail); break;
            case 4: updateStatusPenerbangan(head); break;
            case 5: tampilkanDariDepan(head); break;
            case 6: tampilkanDariBelakang(tail); break;
            case 7: cariJadwalSpesifik(head); break;
            case 0: cout << "\n   Terima kasih telah menggunakan sistem ini!\n"; break;
            default: cout << "\n   Pilihan tidak valid. Silakan coba lagi.\n"; break;
        }

        if (pilihan != 0) {
            pauseScreen();
        }

    } while (pilihan != 0);

    return 0;
}

// === IMPLEMENTATION OF FUNCTIONS ===

void inisialisasiProgram() {
    namaMahasiswa = "Muhammad Dzaki Rifa'I";
    nimMahasiswa = "2409106056";

    if (nimMahasiswa.length() >= 3) {
        basisKodePenerbangan += nimMahasiswa.substr(nimMahasiswa.length() - 3);
    } else {
        basisKodePenerbangan += "XXX";
    }

    if (!nimMahasiswa.empty()) {
        int digitTerakhir = nimMahasiswa.back() - '0';
        posisiSisip = (digitTerakhir == 0) ? 2 : digitTerakhir + 1;
    } else {
        posisiSisip = 2;
    }
}

void tampilkanMenu() {
    cout << "+------------------------------------------------------------+" << endl;
    cout << "|                 FLIGHT SCHEDULE SYSTEM                     |" << endl;
    cout << "|          [ " << namaMahasiswa << " - " << nimMahasiswa << " ]          |" << endl;
    cout << "+------------------------------------------------------------+" << endl;
    cout << "| 1. Tambah Jadwal Penerbangan                               |" << endl;
    cout << "| 2. Sisipkan Jadwal Penerbangan (di Posisi " << posisiSisip << ")                |" << endl;
    cout << "| 3. Hapus Jadwal Paling Awal                                |" << endl;
    cout << "| 4. Update Status Penerbangan                               |" << endl;
    cout << "| 5. Tampilkan Jadwal (Maju)                                 |" << endl;
    cout << "| 6. Tampilkan Jadwal (Mundur)                               |" << endl;
    cout << "| 7. Cari Jadwal Spesifik                                    |" << endl;
    cout << "| 0. Keluar                                                  |" << endl;
    cout << "+------------------------------------------------------------+" << endl;
}

void tambahJadwal(Penerbangan*& head, Penerbangan*& tail) {
    clearScreen();
    cout << "---[ 1. Tambah Jadwal Penerbangan ]---\n" << endl;
    
    Penerbangan* nodeBaru = new Penerbangan;
    cout << "Masukkan Tujuan Penerbangan: ";
    getline(cin, nodeBaru->tujuan);
    cout << "Masukkan Status Awal (Contoh: Tepat Waktu): ";
    getline(cin, nodeBaru->status);
    nodeBaru->next = nullptr;
    nodeBaru->prev = nullptr;

    if (counterJadwal == 0) {
        nodeBaru->kodePenerbangan = basisKodePenerbangan;
    } else {
        nodeBaru->kodePenerbangan = basisKodePenerbangan + "-" + to_string(counterJadwal);
    }
    counterJadwal++;
    jumlahJadwal++;

    if (head == nullptr) {
        head = nodeBaru;
        tail = nodeBaru;
    } else {
        tail->next = nodeBaru;
        nodeBaru->prev = tail;
        tail = nodeBaru;
    }

    cout << "\n   Jadwal dengan kode " << nodeBaru->kodePenerbangan << " berhasil ditambahkan!" << endl;
}

void sisipkanJadwal(Penerbangan*& head, Penerbangan*& tail) {
    clearScreen();
    cout << "---[ 2. Sisipkan Jadwal Penerbangan di Posisi " << posisiSisip << " ]---\n" << endl;

    if (posisiSisip > 1 && jumlahJadwal < posisiSisip - 1) {
        cout << "   Jumlah jadwal belum mencukupi untuk disisipkan di posisi " << posisiSisip << "." << endl;
        cout << "   (Minimal perlu ada " << posisiSisip - 1 << " jadwal)" << endl;
        return;
    }

    Penerbangan* nodeBaru = new Penerbangan;
    cout << "Masukkan Tujuan Penerbangan: ";
    getline(cin, nodeBaru->tujuan);
    cout << "Masukkan Status Awal: ";
    getline(cin, nodeBaru->status);
    nodeBaru->next = nullptr;
    nodeBaru->prev = nullptr;
    
    if (counterJadwal == 0) {
        nodeBaru->kodePenerbangan = basisKodePenerbangan;
    } else {
        nodeBaru->kodePenerbangan = basisKodePenerbangan + "-" + to_string(counterJadwal);
    }
    counterJadwal++;
    jumlahJadwal++;

    if (posisiSisip == 1) {
        nodeBaru->next = head;
        if (head != nullptr) {
            head->prev = nodeBaru;
        }
        head = nodeBaru;
        if (tail == nullptr) tail = head;
    } else {
        Penerbangan* temp = head;
        for (int i = 1; i < posisiSisip - 1 && temp != nullptr; ++i) {
            temp = temp->next;
        }
        if (temp != nullptr) {
            nodeBaru->next = temp->next;
            nodeBaru->prev = temp;
            if (temp->next != nullptr) {
                temp->next->prev = nodeBaru;
            } else {
                tail = nodeBaru;
            }
            temp->next = nodeBaru;
        } else {
            cout << "   Posisi tidak valid." << endl;
            delete nodeBaru;
            jumlahJadwal--;
            counterJadwal--;
            return;
        }
    }
    
    cout << "\n   Jadwal dengan kode " << nodeBaru->kodePenerbangan << " berhasil disisipkan!" << endl;
}

void hapusJadwalAwal(Penerbangan*& head, Penerbangan*& tail) {
    clearScreen();
    cout << "---[ 3. Hapus Jadwal Paling Awal ]---\n" << endl;

    if (head == nullptr) {
        cout << "   Jadwal penerbangan kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    Penerbangan* nodeHapus = head;
    string kodeHapus = nodeHapus->kodePenerbangan;
    head = head->next;
    
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }

    delete nodeHapus;
    jumlahJadwal--;

    cout << "   Jadwal dengan kode " << kodeHapus << " berhasil dihapus." << endl;
}

void updateStatusPenerbangan(Penerbangan* head) {
    clearScreen();
    cout << "---[ 4. Update Status Penerbangan ]---\n" << endl;

    if (head == nullptr) {
        cout << "   Jadwal penerbangan kosong." << endl;
        return;
    }

    string kodeCari;
    cout << "Masukkan Kode Penerbangan yang statusnya akan diubah: ";
    getline(cin, kodeCari);

    Penerbangan* current = head;
    bool ditemukan = false;
    while (current != nullptr) {
        if (current->kodePenerbangan == kodeCari) {
            ditemukan = true;
            cout << "   -> Data Ditemukan:" << endl;
            cout << "   -> Kode    : " << current->kodePenerbangan << endl;
            cout << "   -> Tujuan  : " << current->tujuan << endl;
            cout << "   -> Status Lama: " << current->status << endl;
            
            cout << "\n   Masukkan Status Baru (Contoh: Terlambat, Naik Pesawat): ";
            getline(cin, current->status);
            cout << "\n   Status berhasil diperbarui." << endl;
            break;
        }
        current = current->next;
    }

    if (!ditemukan) {
        cout << "\n   Jadwal dengan kode " << kodeCari << " tidak ditemukan." << endl;
    }
}

// MODIFIKASI: Mengganti printf dengan cout dan <iomanip>
void tampilkanDariDepan(Penerbangan* head) {
    clearScreen();
    cout << "+--------------------------------------------------------------------+" << endl;
    cout << "|              DAFTAR JADWAL PENERBANGAN (DARI DEPAN)                |" << endl;
    cout << "+--------------------------------------------------------------------+" << endl;
    
    if (head == nullptr) {
        cout << "|                Jadwal penerbangan saat ini kosong.               |" << endl;
    } else {
        cout << "| No. | Kode Penerbangan |      Tujuan      |        Status        |" << endl;
        cout << "+-----+------------------+------------------+----------------------+" << endl;
        
        Penerbangan* current = head;
        int nomor = 1;
        while (current != nullptr) {
            cout << "| " << left << setw(3) << nomor
                 << " | " << setw(16) << current->kodePenerbangan
                 << " | " << setw(16) << current->tujuan
                 << " | " << setw(20) << current->status << " |" << endl;
            current = current->next;
            nomor++;
        }
    }
    cout << "+--------------------------------------------------------------------+" << endl;
}

// MODIFIKASI: Mengganti printf dengan cout dan <iomanip>
void tampilkanDariBelakang(Penerbangan* tail) {
    clearScreen();
    cout << "+--------------------------------------------------------------------+" << endl;
    cout << "|             DAFTAR JADWAL PENERBANGAN (DARI BELAKANG)              |" << endl;
    cout << "+--------------------------------------------------------------------+" << endl;
    
    if (tail == nullptr) {
        cout << "|                Jadwal penerbangan saat ini kosong.               |" << endl;
    } else {
        cout << "| No. | Kode Penerbangan |      Tujuan      |        Status        |" << endl;
        cout << "+-----+------------------+------------------+----------------------+" << endl;
        
        Penerbangan* current = tail;
        int nomor = jumlahJadwal;
        while (current != nullptr) {
            cout << "| " << left << setw(3) << nomor
                 << " | " << setw(16) << current->kodePenerbangan
                 << " | " << setw(16) << current->tujuan
                 << " | " << setw(20) << current->status << " |" << endl;
            current = current->prev;
            nomor--;
        }
    }
    cout << "+--------------------------------------------------------------------+" << endl;
}

void cariJadwalSpesifik(Penerbangan* head) {
    clearScreen();
    cout << "---[ 7. Cari Jadwal Spesifik ]---\n" << endl;

    if (head == nullptr) {
        cout << "   Jadwal penerbangan kosong." << endl;
        return;
    }

    string kodeCari;
    cout << "Masukkan Kode Penerbangan yang ingin dicari: ";
    getline(cin, kodeCari);

    Penerbangan* current = head;
    bool ditemukan = false;
    while (current != nullptr) {
        if (current->kodePenerbangan == kodeCari) {
            ditemukan = true;
            cout << "\n+---------------------------------------+" << endl;
            cout << "|           DETAIL DITEMUKAN            |" << endl;
            cout << "+---------------------------------------+" << endl;
            cout << "| Kode Penerbangan : " << current->kodePenerbangan << endl;
            cout << "| Tujuan           : " << current->tujuan << endl;
            cout << "| Status           : " << current->status << endl;
            cout << "+---------------------------------------+" << endl;
            break;
        }
        current = current->next;
    }

    if (!ditemukan) {
        cout << "\n   Jadwal dengan kode " << kodeCari << " tidak ditemukan." << endl;
    }
}


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\n   Tekan Enter untuk kembali ke menu...";
    cin.get();
}