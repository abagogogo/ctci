#include <bits/stdc++.h>

using namespace std;

int factor_of_5(int i) {
    int cnt = 0;

    while (i % 5 == 0) {
        cnt++;
        i /= 5;
    }
    return cnt;
}

int count_fact_zeros(int num) {
    int count = 0;
    for (int i = 2; i < num; ++i) {
        count += factor_of_5(i);
    }
    return count;
}

int count_fact_zeros_v2(int num) {
    if (num < 0) return -1;

    int count = 0;
    for (int i = 5; num / i > 0; i *= 5) {
        count += num / i;
    }
    return count;
}

int main(void) {
    int num = 19;
    int num_zeros = count_fact_zeros(num);
    cout << num << "! has " << num_zeros << " trailing zeros" << (num_zeros == 3 ? "...OK" : "...NG") << endl;

    num_zeros = count_fact_zeros_v2(num);
    cout << num << "! has " << num_zeros << " trailing zeros" << (num_zeros == 3 ? "...OK" : "...NG") << endl;

    return 0;
}
