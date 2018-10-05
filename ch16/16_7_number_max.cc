#include <bits/stdc++.h>

using namespace std;

int flip(int bit) {
    return (bit ^ 1);
}

// Return 1 if a is positive, and 0 if a is negative.
int sign(int a) {
    return flip((a >> 31) & 0x1);
}

int get_max(int a, int b) {
    int diff = a -b;

    int sa = sign(a); // if a >= 0, then 1 else 0
    int sb = sign(b); // if b >= 0, then 1 else 0
    int a_is_max = sign(diff); // depends on wheter or not a- b overflows

    // Goal: define a value k which is 1 if a > 0 and 0 if a < b.
    // if a == b, it doesn't matter what value k is.

    // If a and be have different signs, then k = sign(a)
    // When a - b overflow:
    // case 1: a > 0 and b < 0 => use a, so k = 1 = sign(a)
    // case 2: a < 0 and b > 0 => use b, so k = 0 = sign(a)
    int overflow = sa ^ sb;
    int k = overflow * sa + flip(overflow) * a_is_max;

    return k * a + flip(k) * b;
}

int main(void) {
    vector<vector<int>> tests = {
        {INT_MAX - 2, -15, INT_MAX - 2},
        {INT_MAX, 1, INT_MAX},
        {1, 2, 2},
        {-1, -2, -1}};

    for (auto t : tests) {
        int a = t[0];
        int b = t[1];
        int max_val = t[2];
        int ans = get_max(a, b);
        cout << "max(" << a << ", " << b << ") is " << ans << (ans == max_val ? "...[OK]" : "...[NG]") << endl;
    }

    return 0;
}
