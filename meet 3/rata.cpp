#include <bits/stdc++.h>
using namespace std;

int main(){

    int arr[5];
    int jumlah = 0;

    for(int i = 0; i < 5; i++){
        cout << "Masukkan nilai: ";
        cin >> arr[i];
        jumlah += arr[i];
    }

    float rata = jumlah / 5.0;

    cout << "Rata-rata = " << rata;

    return 0;
}
