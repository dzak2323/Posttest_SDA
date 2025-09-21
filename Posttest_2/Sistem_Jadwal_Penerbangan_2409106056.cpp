#include <iostream>
#include <string>
#include <limits>

using namespace std;

// === STRUCT DEFINITIONS ===
struct Penerbangan {
    string kodePenerbangan;
    string tujuan;
    string status;
    Penerbangan* next;
};

// === GLOBAL VARIABLES & POINTERS ===
Penerbangan* head = nullptr;
Penerbangan* tail = nullptr;

string namaMahasiswa = "";
string nimMahasiswa = "";
string basisKodePenerbangan = "JT-";
int posisiSisip = 0;
int counterJadwal = 0;
int jumlahJadwal = 0; // <-- DEKLARASI YANG HILANG - TELAH DIPERBAIKI

// === FUNCTION PROTOTYPES ===
void inisialisasiProgram();
void tampilkanMenu();
void tambahJadwal(Penerbangan*& head, Penerbangan*& tail);
void sisipkanJadwal(Penerbangan*& head, Penerbangan*& tail);
void hapusJadwalAwal(Penerbangan*& head, Penerbangan*& tail);
void updateStatusPenerbangan(Penerbangan* head);
void tampilkanSemuaJadwal(Penerbangan* head);
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
            case 5: tampilkanSemuaJadwal(head); break;
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
    cout << "| 5. Tampilkan Semua Jadwal                                  |" << endl;
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

    if (counterJadwal == 0) {
        nodeBaru->kodePenerbangan = basisKodePenerbangan;
    } else {
        nodeBaru->kodePenerbangan = basisKodePenerbangan + "-" + to_string(counterJadwal);
    }
    counterJadwal++;
    jumlahJadwal++; // <-- PERBAIKAN

    if (tail != nullptr) {
        tail->next = nodeBaru;
    } else {
        head = nodeBaru;
    }
    tail = nodeBaru;

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
    
    if (counterJadwal == 0) {
        nodeBaru->kodePenerbangan = basisKodePenerbangan;
    } else {
        nodeBaru->kodePenerbangan = basisKodePenerbangan + "-" + to_string(counterJadwal);
    }
    counterJadwal++;
    jumlahJadwal++; // <-- PERBAIKAN

    if (posisiSisip == 1) {
        nodeBaru->next = head;
        head = nodeBaru;
        if (tail == nullptr) tail = head;
    } else {
        Penerbangan* temp = head;
        for (int i = 1; i < posisiSisip - 1 && temp != nullptr; ++i) {
            temp = temp->next;
        }
        if (temp != nullptr) {
            nodeBaru->next = temp->next;
            temp->next = nodeBaru;
            if (nodeBaru->next == nullptr) tail = nodeBaru;
        } else {
            cout << "   Posisi tidak valid." << endl;
            delete nodeBaru;
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
    head = head->next;
    
    if (head == nullptr) {
        tail = nullptr;
    }

    cout << "   Jadwal dengan kode " << nodeHapus->kodePenerbangan << " berhasil dihapus." << endl;
    delete nodeHapus;
    jumlahJadwal--; // <-- PERBAIKAN
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

void tampilkanSemuaJadwal(Penerbangan* head) {
    clearScreen();
    cout << "+--------------------------------------------------------------------+" << endl;
    cout << "|                    DAFTAR SEMUA JADWAL PENERBANGAN                 |" << endl;
    cout << "+--------------------------------------------------------------------+" << endl;
    
    if (head == nullptr) {
        cout << "|                Jadwal penerbangan saat ini kosong.               |" << endl;
    } else {
        cout << "| No. | Kode Penerbangan |      Tujuan      |        Status        |" << endl;
        cout << "+-----+------------------+------------------+----------------------+" << endl;
        
        Penerbangan* current = head;
        int nomor = 1;
        while (current != nullptr) {
            printf("| %-3d | %-16s | %-16s | %-20s |\n", 
                   nomor, 
                   current->kodePenerbangan.c_str(), 
                   current->tujuan.c_str(), 
                   current->status.c_str());
            current = current->next;
            nomor++;
        }
    }
    cout << "+--------------------------------------------------------------------+" << endl;
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