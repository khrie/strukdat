#include <bits/stdc++.h>
using namespace std;

int main(){

    int arr[5];

    for(int i = 0; i < 5; i++){
        cout << "Masukkan nilai: ";
        cin >> arr[i];
    }

    int maks = arr[0];

    for(int i = 1; i < 5; i++){
        if(arr[i] > maks){
            maks = arr[i];
        }
    }

    cout << "Nilai maksimum = " << maks;

    return 0;
}