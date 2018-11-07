#include <bits/stdc++.h>

using namespace std;

struct Solution {
    vector<pair<int, int>> print_pair_sums(vector<int> &arr, int sum) {
        unordered_map<int, int> unpaired_count;
        vector<pair<int, int>> result;

        for (auto n : arr) {
            int complement = sum - n;
            if (unpaired_count[complement] > 0) {
                result.push_back(make_pair(complement, n));
                unpaired_count[complement]--;
                cout << complement << ", " << n << endl;
            } else {
                unpaired_count[n]++;
            }
        }
        return result;
    }
};

bool equal(vector<pair<int, int>> &a, vector<pair<int, int>> &b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main(void) {
    Solution sol;

    vector<vector<int>> tests = {
        {-3, -1, 0, 3, 5, 6, 7, 9, 13, 14},
        };
    vector<vector<pair<int, int>>> answers = {
        {{3, 7}, {-3, 13}},
        };

    for (int i = 0; i < tests.size(); ++i) {
        auto ans = answers[i];
        auto res = sol.print_pair_sums(tests[i], 10);
        cout << (equal(ans, res) ? "[PASS]" : "[FAIL]") << "test-" << i << endl;
    }
    return 0;
}
