#include <bits/stdc++.h>
using namespace std;

int main() {
    int x = 10;
    int *p = &x;

    cout << "Nilai x: " << x << endl;
    cout << "Alamat x: " << &x << endl;
    cout << "Isi pointer p: " << p << endl;
    cout << "Nilai yang ditunjuk p: " << *p << endl;

    return 0;
}