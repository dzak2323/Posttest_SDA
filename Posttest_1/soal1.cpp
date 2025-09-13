#include <iostream>

using namespace std;

// Fungsi untuk memeriksa apakah sebuah bilangan adalah bilangan prima
bool CekPrima(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Fungsi untuk mengisi array dengan 7 bilangan prima pertama
void InputPrima(int arr[], int size) {
    int count = 0;
    int number = 2;
    while (count < size) {
        if (CekPrima(number)) {
            arr[count] = number;
            count++;
        }
        number++;
    }
}

// Fungsi untuk membalik urutan array menggunakan pointer
void reverseArray(int* arr, int size) {
    int* start = arr;
    int* end = arr + size - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Fungsi untuk menampilkan isi array
void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; ++i) {
        cout << arr[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int main() {
    const int SIZE = 7;
    int dataArray[SIZE];

    // Mengisi array dengan bilangan prima
    InputPrima(dataArray, SIZE);

    // Menampilkan array sebelum dibalik
    cout << "Array sebelum dibalik: ";
    printArray(dataArray, SIZE);

    // Membalik array
    reverseArray(dataArray, SIZE);

    // Menampilkan array setelah dibalik
    cout << "Array setelah dibalik: ";
    printArray(dataArray, SIZE);

    return 0;
}