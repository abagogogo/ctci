#include <bits/stdc++.h>

using namespace std;

struct Solution {
    vector<int> compute_pond_sizes(vector<vector<int>> &land) {
        vector<int> res;

        for (int r = 0; r < land.size(); ++r) {
            for (int c = 0; c < land[r].size(); ++c) {
                if (land[r][c] == 0) {
                    int size = compute_size(land, r, c);
                    res.push_back(size);
                }
            }
        }
        return res;
    }

    int compute_size(vector<vector<int>> &land, int r, int c) {
        if (r < 0 || c < 0 || r >= land.size() || c >= land[r].size()) return 0;
        if (land[r][c] != 0) return 0; // visited.

        int size = 1;
        land[r][c] = -1; // mark visited
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc) 
                size += compute_size(land, r + dr, c + dc);
        return size;
    }
};

bool equal(vector<int> &a, vector<int> &b) {
    if (a.size() != b.size()) return false;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main(void) {
    Solution sol;

    vector<vector<vector<int>>> tests = {
        {{0, 2, 1, 0},
         {0, 1, 0, 1},
         {1, 1, 0, 1},
         {0, 1, 0, 1}}, 
        {{0, 2, 1, 0},
         {1, 0, 0, 1},
         {1, 1, 0, 1},
         {0, 1, 0, 0}}, 
        };
    vector<vector<int>> answers = {
        {2, 4, 1},
        {1, 7},
        };

    for (int i = 0; i < tests.size(); ++i) {
        auto test = tests[i];
        auto ans = answers[i];
        vector<int> res = sol.compute_pond_sizes(test);
        cout << (equal(ans, res) ? "[PASS]" : "[FAIL]") << "test-" << i << endl;
    }
    return 0;
}
