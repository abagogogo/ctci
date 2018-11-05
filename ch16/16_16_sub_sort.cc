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

int main(void) {
    Solution sol;

    vector<int> test = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
    Result ans = {3, 9};
    Result res = sol.find_unsorted_seq(test);
    cout << ((ans == res) ? "[PASS]" : "[FAIL]") << " left = " << res.left << ", right = " << res.right << endl;
    
    return 0;
}
