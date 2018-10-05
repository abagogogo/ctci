#include <bits/stdc++.h>

using namespace std;

template <class T>
void swap_num(T &a, T &b) {
    cout << "original: a=" << a << ", b=" << b << endl;
    a = b - a;
    b = b - a;
    a = a + b;
    cout << "swapped : a=" << a << ", b=" << b << endl;
}

int main(void) {
    int ia = 3, ib = 5;
    swap_num(ia, ib);
    float fa = 1234.45, fb = -2134.0;
    swap_num(fa, fb);
    return 0;
}
