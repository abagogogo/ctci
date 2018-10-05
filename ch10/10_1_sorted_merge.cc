#include <bits/stdc++.h>

using namespace std;

void merge(int a[], int b[], int last_a, int last_b) {
    int curr = last_a + last_b + 1;
    while (last_a >= 0 && last_b >= 0) {
        if (a[last_a] >= b[last_b]) {
            a[curr--] = a[last_a--];
        } else {
            a[curr--] = b[last_b--];
        }
    }
    while (last_b >= 0) {
        a[curr--] = b[last_b--];
    }
}

void print_arr(int a[], int cnt) {
    for (int i = 0; i < cnt; ++i) {
        cout << a[i] << ", ";
    }
    cout << endl;
}

int main(void) {
    int a[20] = {1, 3, 5, 7, 9, 12};
    int b[6]  = {2, 4, 6, 8, 10,11};

    merge(a, b, 5, 5);
    print_arr(a, 12);
        
    return 0;
}
