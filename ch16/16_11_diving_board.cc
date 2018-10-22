#include <bits/stdc++.h>

using namespace std;

#if 0 // O(k^2)
void get_all_lengths(int remain, int total_len, int shorter, int longer,
                     set<int> &lengths, set<string> memo) {
    if (remain == 0) {
        lengths.insert(total_len);
        return;
    }

    string key = to_string(remain) + " " + to_string(total_len);
    if (memo.find(key) != memo.end()) return;
    get_all_lengths(remain - 1, total_len + longer, shorter, longer, lengths, memo);
    get_all_lengths(remain - 1, total_len + shorter, shorter, longer, lengths, memo);
}

set<int> all_lengths(int k, int shorter, int longer) {
    set<int> lengths;
    set<string> memo;
    get_all_lengths(k, 0, shorter, longer, lengths, memo);
    return lengths;
}
#else

set<int> all_lengths(int k, int shorter, int longer) {
    set<int> lengths;
    for (int cnt = 0; cnt <= k; ++cnt) {
        int len = cnt * shorter + (k - cnt) * longer;
        lengths.insert(len);
    }
    return lengths;
}
#endif

int main(void) {
    int k = 4;
    int shorter = 1;
    int longer = 2;

    set<int> lengths = all_lengths(k, shorter, longer);
    cout << lengths.size() << " kinds of lengths:" << endl;
    for (auto it = lengths.begin(); it != lengths.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;
    return 0;
}
