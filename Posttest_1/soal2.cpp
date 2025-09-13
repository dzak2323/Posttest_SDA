#include <iostream>

using namespace std;

void printMatrix(int matrix[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}


int TotalGenap(int matrix[3][3]) {
    int total = 0;
    
    for (int i = 0; i < 3; i += 2) {
        for (int j = 0; j < 3; ++j) {
            total += matrix[i][j];
        }
    }
    return total;
}

int main() {
    
    int Matrikss[3][3] = {
        {1, 2, 3},  
        {4, 5, 6},  
        {7, 8, 9}   
    };

    // Menampilkan matriks
    cout << "Matriks 3x3 yang disimpan:" << endl;
    printMatrix(Matrikss);

    
    int sum = TotalGenap(Matrikss);
    cout << "\nJumlah elemen pada baris dengan indeks genap (0 dan 2): " << sum << endl;

    return 0;
}