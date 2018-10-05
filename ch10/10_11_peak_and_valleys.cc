#include <bits/stdc++.h>

using namespace std;

int max_idx(vector<int> &arr, int a, int b, int c) {
    int len = arr.size();
    int a_val = (a >= 0 && a < len) ? arr[a] : INT_MIN;
    int b_val = (b >= 0 && b < len) ? arr[b] : INT_MIN;
    int c_val = (c >= 0 && c < len) ? arr[c] : INT_MIN;

    int max = std::max(a_val, std::max(b_val, c_val));
    if (a_val == max) return a;
    else if (b_val == max) return b;
    else return c;
}

void sort_valley_peak(vector<int> &arr) {
    for (int i = 1; i < arr.size(); i +=2) {
        int biggest_idx = max_idx(arr, i-1, i, i+1);
        if (i != biggest_idx) {
            swap(arr[i], arr[biggest_idx]);
        }
    }
}

int main(void) {
    vector<int> arr = {9, 1, 0, 4, 8, 7};
    sort_valley_peak(arr);
    for (auto n : arr) cout << n << ", ";
    cout << endl;
    return 0;
}
