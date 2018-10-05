#include <bits/stdc++.h>

using namespace std;

#if 0 // recursion
int product_helper(int smaller, int bigger) {
    if (smaller == 0) return 0;
    else if (smaller == 1) return bigger;

    // compute half.
    int s = smaller >> 1;
    int side1 = product_helper(s, bigger);
    int side2 = side1;
    if (smaller % 2 == 1) side2 += bigger;
    return side1 + side2;
}

int product(int a, int b) {
    int bigger = (a >= b ? a : b);
    int smaller = (a < b ? a : b);
    return product_helper(smaller, bigger);
}
#else // shif-and-add, it won't hit. stack overflow limiation as recursion version.
int product(int a, int b) {
    int bigger = (a >= b ? a : b);
    int smaller = (a < b ? a : b);

    int sum = 0;
    while (smaller) {
        if (smaller & 0x1) sum += bigger;
        bigger <<= 1;
        smaller >>= 1;
    }
    return sum;
}
#endif

int main(void) {
    int a = 17;
    int b = 23;
    int ret = product(a, b);
    cout << a << " * " << b << " = " << ret << (ret == a * b ? "...OK" : "...NG") << endl;

    a = 83, b = 32;
    ret = product(a, b);
    cout << a << " * " << b << " = " << ret << (ret == a * b ? "...OK" : "...NG") << endl;

    a = 83237944, b = 39542;
    for (int i = 0; i < 1000000; ++i) {
        a++;
        b--;
        ret = product(a, b);
    }
    cout << a << " * " << b << " = " << ret << (ret == a * b ? "...OK" : "...NG") << endl;
    return 0;
}
