#include <bits/stdc++.h>

using namespace std;

#if 0 // top-down, memoization solution.
int count_ways(int n, map<int, int> &memo) {
    if (n < 0 ) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (memo.find(n) != memo.end()) {
        return memo[n];
    } else {
        memo[n] = count_ways(n - 1, memo) + count_ways(n - 2, memo) + count_ways(n - 3, memo);
        return memo[n];
    }
}

int count_ways(int n) {
    map<int, int> memo;
    return count_ways(n, memo);
}
#else // bottom-up.
int count_ways(int n) {
    vector<int> memo(n + 1, 0);

    memo[0] = 1;
    memo[1] = 1;
    memo[2] = 2;
    for (int i = 3; i <= n; ++i) {
        memo[i] = memo[i - 1] + memo[i - 2] + memo[i - 3];
    }
    return memo[n];
}
#endif

int main(void) {
    for (int n = 0; n < 37; ++n) {
        cout << "n = " << n << " => ways = " << count_ways(n) << endl;
    }
    return 0;
}
