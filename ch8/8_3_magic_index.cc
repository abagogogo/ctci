#include <bits/stdc++.h>

using namespace std;

int magic_show(const vector<int> &arr) {
    for (int i = 0; i < arr.size(); ++i) {
        if (i == arr[i]) {
            return i;
        }
    }
    return -1;
}

int magic_fast(const vector<int> &arr, int from, int to) {
    if (from > to) return -1;
    int mid = (from + to) / 2;

    if (arr[mid] == mid) {
        return mid;
    } 
    
    // search left
    int left = magic_fast(arr, from, min(mid-1, arr[mid]));
    if (left >= 0) return left;

    // search right
    return magic_fast(arr, max(mid + 1, arr[mid]), to);
}

int main(void) {
    vector<int> arr = {-40, -20, -1, 1, 2, 3, 5, 7, 9, 12, 13};

    cout << "magic_show: " << magic_show(arr) << endl;
    cout << "magic_fast: " << magic_fast(arr, 0, arr.size() - 1) << endl;

    vector<int> dup = {-10, -5, 2, 2, 2, 3, 4, 7, 9,12, 13};
    cout << "magic_fast on dup: " << magic_fast(dup, 0, dup.size() - 1) << endl;
    return 0;
}
