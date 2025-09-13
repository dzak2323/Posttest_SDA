#include <iostream>

using namespace std;

// Fungsi untuk menukar dua nilai integer menggunakan referensi (&)
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10;
    int y = 20;

    cout << "Sebelum ditukar:" << endl;
    cout << "Nilai x = " << x << endl;
    cout << "Nilai y = " << y << endl;

    // Memanggil fungsi swap, meneruskan referensi x dan y
    swap(x, y);

    cout << "\nSetelah ditukar:" << endl;
    cout << "Nilai x = " << x << endl;
    cout << "Nilai y = " << y << endl;

    return 0;
}