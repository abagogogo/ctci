#include <bits/stdc++.h>

using namespace std;

struct Result {
    int hits;
    int pseudo_hits;

    Result () {
        hits = pseudo_hits = 0;
    }

    Result (int _hits, int _pseudo_hits) {
        hits = _hits;
        pseudo_hits = _pseudo_hits;
    }

    bool operator==(const Result another) {
        return hits == another.hits && pseudo_hits == another.pseudo_hits;
    }
};

int get_code(char ch) {
    switch (ch) {
    case 'B':
        return 0;
    case 'G':
        return 1;
    case 'R':
        return 2;
    case 'Y':
        return 3;
    default:
        return -1;
    }
}

int MAX_COLORS = 4;

Result estimate(string guess, string solution) {
    Result res;
    if (guess.length() != solution.length()) return res;
    vector<int> frequencies(MAX_COLORS, 0);

    // compute hits and build frequency table.
    for (int i = 0; i < guess.length(); ++i) {
        if (guess[i] == solution[i]) {
            ++res.hits;
        } else {
            int code = get_code(solution[i]);
            frequencies[code]++;
        }
    }

    // compute pseudohtis.
    for (int i = 0; i < guess.length(); ++i) {
        int code = get_code(guess[i]);
        if (guess[i] != solution[i] &&
            code >= 0 && frequencies[code] > 0) {
            ++res.pseudo_hits;
            --frequencies[code];
        }
    }
    return res;
}

int main(void) {
    pair<string, string> test = {"GGRR", "RGBY"};
    Result ans = {1, 1};

    Result res = estimate(test.first /*guess*/, test.second /*solution*/);
    cout << ((ans == res) ? "[PASS]" : "FAIL") << endl;
}
