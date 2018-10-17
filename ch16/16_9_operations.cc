#include <bits/stdc++.h>

using namespace std;

// -a
int neg_op(int a) {
#if 1 // O(a)
    int new_sign = (a < 0) ? 1 : -1;
    int neg = 0;
    while (a) {
        a += new_sign;
        neg += new_sign;
    }
    return neg;
#else // O(loga*loga)
    int new_sign = (a < 0) ? 1 : -1;
    int neg = 0;
    int delta = new_sign;
    while (a) {
        bool diff_signs = ((a + delta > 0) != (a > 0));
        if (a + delta != 0 && diff_signs) { // if delta is too big, reset it
            delta = new_sign;
        }
        neg += delta;
        a += delta;
        delta += delta; // double the deta
    }
    return neg;
#endif
}

int abs_op(int a) {
    return (a >= 0) ? a : neg_op(a);
}

// a - b
int minus_op(int a, int b) {
    return a + neg_op(b);
}

// a * b: O(b)
int multiply_op(int a, int b) {
    if (a < b) {
        return multiply_op(b, a);
    }
    int sum = 0;
    for (int i = 0; i < abs_op(b); ++i) {
        sum += a;
    }
    if (b < 0) sum = neg_op(sum);
    return sum;
}

// a / b = O(a/b)
int divide_op(int a, int b) {
    if (b == 0) throw 0;

    int absa = abs_op(a);
    int absb = abs_op(b);

    int product = 0;
    int x = 0;
    while (product + absb <= absa) {
        product += absb;
        x++;
    }
    if ((a < 0 && b < 0) || (a > 0 && b > 0)) {
        return x;
    } else {
        return neg_op(x);
    }
}

int main(void) {
    int a, b, rst;
    a = 3233;
    b = 0;
    rst = neg_op(a);
    cout << "neg_op(a) = " << rst << ((rst == -a) ? "...OK" : "...NG") << endl;
    rst = minus_op(a, b);
    cout << "minus_op(a, b) = " << rst << ((rst == a - b) ? "...OK" : "...NG") << endl;
    rst = multiply_op(a, b);
    cout << "multiply_op(a, b) = " << rst << ((rst == a * b) ? "...OK" : "...NG") << endl;
    rst = divide_op(a, b);
    cout << "divide_op(a, b) = " << rst << ((rst == a / b) ? "...OK" : "...NG") << endl;

    return 0;
}
