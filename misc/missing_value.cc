#include <bits/stdc++.h>

using namespace std;

bool is_miss(const vector<int> &data, int value) {
    for (auto num : data) {
        if (num == value) return false;
    }
    return true;
}

#if 0 // miss one value
bool find_miss(const vector<int> &data, int &miss_val) {
    int min_val = data[0];
    int max_val = data[0];
    int act_sum = 0;

    for (auto num : data) {
        min_val = min(num, min_val);
        max_val = max(num, max_val);
        act_sum += num;
    }
    int exp_sum = ((min_val + max_val) * (max_val - min_val + 1)) / 2;
    int diff = (exp_sum - act_sum);
    if (diff < min_val || diff > max_val) {
        return false;
    }
    
    if (is_miss(data, diff)) {
        miss_val = diff;
        return true;
    }

    return false;
}
#else // for multiple missing value
bool find_miss_one(const vector<int> &data, int &miss_val, int lower, int upper) {
    // Invalid range.
    if (lower > upper) return false;

    // Only one suspect left.
    if (lower == upper) {
        if (is_miss(data, lower)) {
            miss_val = lower;
            return true;
        }
        return false;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    int act_sum = 0;

    for (auto num : data) {
        min_val = min(num, min_val);
        max_val = max(num, max_val);
        if (num < lower || num > upper) continue;
        act_sum += num;
    }
    int exp_sum = ((lower + upper) * (upper - lower + 1)) / 2;
    int diff = (exp_sum - act_sum);
    //printf("[DBG] min: %d, max: %d, exp_sum: %d, act_sum: %d, diff: %d\n", min_val, max_val, exp_sum, act_sum, diff);

    // No missing value.
    if (diff < min_val) {
        return false;
    }
    
    // If there's only one miss number, that'll be diff.
    if (diff <= max_val && is_miss(data, diff)) {
        miss_val = diff;
        return true;
    }

    // Recurse with smaller range.
    // So, the complextiy will be O(n) * O(lg2^64) = O(n).
    upper = (lower + upper) / 2;
    return find_miss_one(data, miss_val, lower, upper);
}

bool find_miss(const vector<int> &data, int &miss_val) {
    int min_val = data[0];
    int max_val = data[0];

    for (auto num : data) {
        min_val = min(num, min_val);
        max_val = max(num, max_val);
    }

    return find_miss_one(data, miss_val, min_val, max_val);
}
#endif

int main(void) {
    vector<vector<int>> tests = {
        {1}, // test 1: no
        {1, 2},  // test 2: no
        {3, 1, 2}, // test 3: no
        {4, 2, 1, 3}, // test 4: no
        {1, 3},  // test 5: 2
        {1, 2, 4},  // test 6: 3
        {8, 10, 5},  // test 7: 6, 7, 9
        {5, 4, 2, 8, 7, 6}, // test 8: 3
        {10, 5, 4, 2, 8, 7, 6}, // test 9: 3, 9
        {10, 2, 4, 5, 8, 7, 6}, // test 10: 3, 9
        {1, 2, 3, 4, 6, 7, 9, 10, 8}, // test 11: 5
        {11, 9, 8, 7, 6, 1, 5, 2, 4, 3}, // test 12: 10
        {1, 6, 8, 7, 9, 11, 5, 2, 4, 3}, // test 13: 10
        {1, 6, 8, 7, 9, 5, 11, 2, 4, 3}, // test 13: 10
    };

    int ith = 0;
    for (auto data : tests) {
        int  miss_val;
        bool is_missed = find_miss(data, miss_val);

        cout << "test " << ++ith << ": ";
        if (is_missed) cout << "found missing value: " << miss_val << endl; 
        else cout << "NOT found missing value." << endl;
    }
    return 0;
}
