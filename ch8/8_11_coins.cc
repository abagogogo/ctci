#include <bits/stdc++.h>

using namespace std;

#if 1 // memoization.
int make_change(int amount, const vector<int> &denoms, int index, map<pair<int, int>, int> &memo) {
    if (index >= denoms.size() - 1) return 1;

    pair<int, int> key = {amount, index};
    if (memo[key] > 0) return memo[key];

    int denom_amount = denoms[index];
    int ways = 0;
    for (int i = 0; i * denom_amount <= amount; ++i) {
        // go to next denom, assuming i coins of denom_amount picked.
        int remain_amount = amount - i * denom_amount;
        ways += make_change(remain_amount, denoms, index + 1, memo);
    }
    memo[key] = ways;
    return ways; 
}

int make_change(int amount) {
    vector<int> denoms = {25, 10, 5, 1};
    map<pair<int, int>, int> memo;

    return make_change(amount, denoms, 0, memo);
}
#else // DP: NG
int make_change(int amount) {
    vector<int> denoms = {25, 10, 5, 1};
    map<int, int> ways;

    ways[0] = ways[1] = 1;
    for (int i = 2; i <= amount; ++i) {
        for (auto denom : denoms) {
            if (i >= denom) {
                ways[i] += ways[i - denom];
            }
        }
    }
    return ways[amount];
}
#endif

int main(void) {
    
    int amount = 100;
    int ways = make_change(amount);
    cout << "amount = " << amount << " => " << ways << " ways" << endl;
    return 0;
}
