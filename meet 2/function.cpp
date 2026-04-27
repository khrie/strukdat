#include <bits/stdc++.h>
using namespace std;

int tambah(int a, int b) {
    return a + b;
}

int kurang(int a, int b) {
    return a - b;
}

int main() {
    int hasil = tambah(5, 3);
    cout << "Hasil tambah: " << hasil << endl;

    hasil = kurang(5, 3);
    cout << "Hasil kurang: " << hasil;

    return 0;
}