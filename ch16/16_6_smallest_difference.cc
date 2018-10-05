#include <bits/stdc++.h>

using namespace std;

int find_smallest_diff(vector<int> &arr1, vector<int> &arr2) {
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());

    int ans = INT_MAX;
    int idx1 = 0;
    int idx2 = 0;
    while (idx1 < arr1.size() && idx2 < arr2.size()) {
        ans = min(ans, abs(arr1[idx1] - arr2[idx2]));

        if (arr1[idx1] <= arr2[idx2]) {
            idx1++;
        } else {
            idx2++;
        }
    }
    return ans;
}

int main(void) {
    vector<int> a = {1, 2, 11, 15};
    vector<int> b = {4, 12, 19, 23, 127, 235};

    int d = find_smallest_diff(a, b);
    cout << "smallest difference = " << d << endl;
    return 0;
}
