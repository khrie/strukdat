#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cout << "Jumlah data: ";
    cin >> n;

    int arr[n];

    for(int i = 0; i < n; i++){
        cout << "Masukkan nilai ke-" << i+1 << ": ";
        cin >> arr[i];
    }

    cout << "Data yang dimasukkan:" << endl;

    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }

    return 0;
}