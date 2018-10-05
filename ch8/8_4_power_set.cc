#include <bits/stdc++.h>

using namespace std;

void get_subsets(const vector<int> &a_set, int n, vector<vector<int>> &subsets) {
    if (n == 0) { // base case - add empty set
        subsets.push_back({});
        return;
    }

    get_subsets(a_set, n - 1, subsets);

    int size = subsets.size();
    int new_item = a_set[n - 1];
    for (int i = 0; i < size; ++i) {
        vector<int> &old_subset = subsets[i];
        vector<int> new_subset;
        for (auto num : old_subset) new_subset.push_back(num);
        new_subset.push_back(new_item);
        subsets.push_back(new_subset);
    }
}

int main(void) {
    vector<int> a_set = {1, 2, 3};
    vector<vector<int>> subsets;

    int n = a_set.size();
    get_subsets(a_set, n, subsets);
    int total_cnt = 0;
    for (int i = 0; i < subsets.size(); ++i) {
        cout << "[" << i << "] ";
        for (auto n : subsets[i]) {
            cout << n << ", ";
            total_cnt++;
        }
        cout << endl;
    }
    cout << "n=" << n << ", n*2^(n-1)=" << (n * (1 << (n-1))) << endl;
    cout << "total elemetns: " << total_cnt << endl;

    return 0;
}
