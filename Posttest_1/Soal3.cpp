#include <iostream>
#include <string>

using namespace std;

// Mendefinisikan struktur Mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    double ipk;
};


void sortMahasiswa(Mahasiswa mhs[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            
            if (mhs[j].ipk > mhs[j + 1].ipk) {
                Mahasiswa temp = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = temp;
            }
        }
    }
}


void displayMahasiswa(Mahasiswa mhs[], int size) {
    cout << "Data Mahasiswa setelah diurutkan berdasarkan IPK (menaik):" << endl;
    cout << "---------------------------------------------------------" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Mahasiswa ke-" << i + 1 << ":" << endl;
        cout << "  Nama: " << mhs[i].nama << endl;
        cout << "  NIM:  " << mhs[i].nim << endl;
        cout << "  IPK:  " << mhs[i].ipk << endl;
        cout << "---------------------------------------------------------" << endl;
    }
}

int main() {
    
    const int numMahasiswa = 4;
    Mahasiswa daftarMahasiswa[numMahasiswa];

    
    daftarMahasiswa[0] = {"Budianto", "2409106000", 3.85};
    daftarMahasiswa[1] = {"Sutrisno", "2409106001", 3.92};
    daftarMahasiswa[2] = {"Joko dodo", "2409106002", 3.75};
    daftarMahasiswa[3] = {"Rin", "2409106003", 3.90};

    
    sortMahasiswa(daftarMahasiswa, numMahasiswa);

    
    displayMahasiswa(daftarMahasiswa, numMahasiswa);

    return 0;
}