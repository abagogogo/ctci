#include <bits/stdc++.h>

using namespace std;

struct Result {
    int left;
    int right;

    Result() {
        left = right = 0;
    }

    Result(int l, int r) {
        left = l;
        right = r;
    }
    bool operator==(const Result &a) {
        return left == a.left && right == a.right;
    }
};

struct Solution {
    Result find_unsorted_seq(vector<int> arr) {
        Result res;
    
        // find left subsequence
        int end_left = find_end_of_left_seq(arr);
        cout << "[DBG] end_left=" << end_left << endl;
        if (end_left >= arr.size() - 1) return res;
    
        // find right subsequence
        int start_right = find_start_of_right_seq(arr);
        cout << "[DBG] start_right=" << start_right << endl;
    
        // get min and max
        int max_index = end_left; // max of left side
        int min_index = start_right; // min of right side
        for (int i = end_left + 1; i < start_right; ++i) {
            if (arr[i] < arr[min_index]) min_index = i;
            if (arr[i] > arr[max_index]) max_index = i;
        }
    
        // slide left until less than arr[min_index]
        res.left = shrink_left(arr, min_index, end_left);
        cout << "[DBG] shrink_left, " << "min_index=" << min_index << " =>" << res.left << endl;
    
        // slide right untill greater than array[max_index]
        res.right = shrink_right(arr, max_index, start_right);
        cout << "[DBG] shrink_right, " << "max_index=" << max_index << " =>" << res.right << endl;
        return res;
    }
    
    int find_end_of_left_seq(vector<int> &arr) {
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] < arr[i - 1]) return i - 1;
        }
        return arr.size() - 1;
    }
    
    int find_start_of_right_seq(vector<int> &arr) {
        for (int i = arr.size() - 2; i >= 0; --i) {
            if (arr[i] > arr[i + 1]) return i + 1;
        }
        return 0;
    }
    
    int shrink_left(vector<int> &arr, int min_index, int start) {
        int comp = arr[min_index];
        for (int i = start; i >= 0; --i) {
            if (arr[i] <= comp) return i + 1;
        }
        return 0;
    }
    
    int shrink_right(vector<int> &arr, int max_index, int start) {
        int comp = arr[max_index];
        for (int i = start; i < arr.size(); ++i) {
            if (arr[i] >= comp) return i - 1;
        }
        return arr.size() - 1;
    }
};

struct MySolution {
    Result find_unsorted_seq(vector<int> arr) {
        Result res;
        if (arr.empty()) return res;

        vector<bool> left(arr.size(), false);
        vector<bool> right(arr.size(), false);

        // for each x, max of left to x shall <= x if it's sorted.
        int max = arr[0];
        for (int i = 0; i < arr.size(); ++i) {
            if (max <= arr[i]) {
                left[i] = true;
                max = arr[i];
            }
            //cout << "DBG: left[" << i << "] = " << left[i] << endl;
        }

        // for each x, min of right to x shall >= x if it's sorted.
        int min = arr.back();
        for (int i = arr.size() - 1; i >= 0; --i) {
            if (min >= arr[i]) {
                right[i] = true;
                min = arr[i];
            }
            //cout << "DBG: right[" << i << "] = " << right[i] << endl;
        }

        // intersection of both condition get the anser
        res.left = arr.size();
        for (int i = 0; i < arr.size(); ++i) {
            if (!left[i] || !right[i]) {
                res.left = i;
                break;
            }
        }
        res.right = -1;
        for (int i = arr.size() - 1; i >= 0; --i) {
            if (!left[i] || !right[i]) {
                res.right = i;
                break;
            }
        }
        return res;
    }
};

int main(void) {
    //Solution sol;
    MySolution sol;

    vector<int> test = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
    Result ans = {3, 9};
    Result res = sol.find_unsorted_seq(test);
    cout << ((ans == res) ? "[PASS]" : "[FAIL]") << " left = " << res.left << ", right = " << res.right << endl;
    
    return 0;
}
