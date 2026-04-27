#include <bits/stdc++.h>
using namespace std;

struct Mahasiswa{
    string nama;
    string nim;
    string hobi[3];
};

int main(){

    Mahasiswa mhs[3];

    for(int i = 0; i < 3; i++){
        cout << "Mahasiswa ke-" << i+1 << endl;

        cout << "Nama: ";
        cin >> mhs[i].nama;

        cout << "NIM: ";
        cin >> mhs[i].nim;

        for(int j = 0; j < 3; j++){
            cout << "Hobi ke-" << j+1 << ": ";
            cin >> mhs[i].hobi[j];
        }

        cout << endl;
    }

    cout << "Data Mahasiswa" << endl;

    for(int i = 0; i < 3; i++){
        cout << "Nama: " << mhs[i].nama << endl;
        cout << "NIM: " << mhs[i].nim << endl;

        cout << "Hobi: ";
        for(int j = 0; j < 3; j++){
            cout << mhs[i].hobi[j] << " ";
        }

        cout << endl << endl;
    }

    return 0;
}