#include <bits/stdc++.h>

using namespace std;

struct Solution {
    int get_max_sum(const vector<int> &arr) {
        int max_sum = 0;
        int sum = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sum += arr[i];
            if (max_sum < sum) {
                max_sum = sum;
            } else if (sum < 0) {
                sum = 0;
            }
        }
        return max_sum;
    }
};

int main(void) {
    Solution sol;

    vector<vector<int>> tests = {
        {2, -8, 3, -2, 4, -10},
        {2, 3, -8, -1, 2, 4, -2, 3},
        };
    vector<int> answers = {5, 7};

    for (int i = 0; i < tests.size(); ++i) {
        auto test = tests[i];
        int ans = answers[i];
        int res = sol.get_max_sum(test);
        cout << ((ans == res) ? "[PASS]" : "[FAIL]") << "test-" << i <<  " res = " << res << endl;
    }
    return 0;
}
