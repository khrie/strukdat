#include <bits/stdc++.h>
using namespace std;

int main() {
    int angka;

    cout << "Masukkan angka: ";
    cin >> angka;

    if (angka > 0) {
        cout << "Bilangan Positif";
    } else if(angka == 0){
        cout << "Bilangan adalah Nol";
    } else {
        cout << "Bilangan Negatif";
    }

    return 0;
}