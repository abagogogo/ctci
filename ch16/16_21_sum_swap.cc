#include <bits/stdc++.h>

using namespace std;

struct Solution {
    pair<int, int> find_swap_values(const vector<int> &arr1, const vector<int> &arr2) {
        int sum1 = sum(arr1);
        int sum2 = sum(arr2);
        if ((sum1 - sum2) % 2 != 0) return {INT_MIN, INT_MIN};
        int target = (sum1 - sum2) / 2;
        printf("DBG: sum1=%d, sum2=%d, target=%d\n", sum1, sum2, target);

        unordered_set<int> contents2;
        for (auto n : arr2) contents2.insert(n);

        for (int one : arr1) {
            int two = one - target;
            printf("DBG: one=%d, two=%d\n", one, two);
            if (contents2.find(two) != contents2.end()) {
                return {one, two};
            }
        }
        return {};
    }

    int sum(const vector<int> &arr) {
        int sum = 0;
        for (auto n : arr) sum += n;
        return sum;
    }
};

int main(void) {
    Solution sol;

    vector<vector<int>> tests = {
        {1, 4, 2, 1, 1, 2}, {3, 6, 3, 3},
        };
    vector<pair<int, int>> answers = {
        {1, 3},
        };

    for (int i = 0; i < tests.size(); i += 2) {
        auto ans = answers[i];
        auto res = sol.find_swap_values(tests[i], tests[i+1]);
        cout << ((ans == res) ? "[PASS]" : "[FAIL]") << "test-" << i <<  " res = " << res.first << ", " << res.second << endl;
    }
    return 0;
}
