#include <bits/stdc++.h>

using namespace std;

int make_change(int amount, const vector<int> &denoms, int index, vector<vector<int>> &memo) {
    if (index >= denoms.size() - 1) return 1;

    if (memo[amount][index] != 0) return memo[amount][index];

    int denom_amount = denoms[index];
    int ways = 0;
    for (int i = 0; i * denom_amount <= amount; ++i) {
        // go to next denom, assuming i coins of denom_amount picked.
        int remain_amount = amount - i * denom_amount;
        ways += make_change(remain_amount, denoms, index + 1, memo);
    }
    memo[amount][index] = ways;
    return ways; 
}

int make_change(int amount) {
    vector<int> denoms = {25, 10, 5, 1};
    //map<pair<int, int>, int> memo; // unordered_map cannot take pair as key.
    vector<vector<int>> memo(amount + 1, vector<int>(denoms.size(), 0));

    return make_change(amount, denoms, 0, memo);
}

int main(void) {
    
    int amount = 100;
    int ways = make_change(amount);
    cout << "amount = " << amount << " => " << ways << " ways" << endl;
    return 0;
}
