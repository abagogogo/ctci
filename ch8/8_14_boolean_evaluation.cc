#include <bits/stdc++.h>

using namespace std;

bool to_bool(string &s) {
	return (s == "1");
}

int count_eval(string s, bool result, map<string, int> &memo) {
	if (s.length() == 0) return 0;
	if (s.length() == 1) return to_bool(s) == result ? 1 : 0;
    string key = to_string(result) + s;
	if (memo.find(key) != memo.end()) return memo[key];

	int ways = 0;
	for (int i = 1; i < s.length(); i += 2) {
		char ch = s[i];
		string left = s.substr(0, i);
		string right = s.substr(i+1);
		int left_true = count_eval(left, true, memo);
		int left_false = count_eval(left, false, memo);
		int right_true = count_eval(right, true, memo);
		int right_false = count_eval(right, false, memo);
		int total = (left_true + left_false) * (right_true + right_false);

		int total_true = 0;
		if (ch == '^') {
			total_true = left_true * right_false + left_false * right_true;
		} else if (ch == '&') {
			total_true = left_true * right_true;
		} else if (ch == '|') {
			total_true = left_true * right_true + left_true * right_false + left_false * right_true;
		}
		int sub_ways = result ? total_true : total - total_true;
		ways += sub_ways;
    }

    memo[key] = ways;
    return ways;
}

int main(void) {
    string expr = "1^0|0|1";
    bool result = false;
    map<string, int> memo;

    int ways = count_eval(expr, result, memo);
    cout << expr << " = " << result << ", ways = " << ways << endl;
    return 0;
}
