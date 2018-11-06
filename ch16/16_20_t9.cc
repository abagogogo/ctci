#include <bits/stdc++.h>

using namespace std;

struct Solution {
    vector<vector<char>> t9_letters;
    unordered_map<char, char> letter_to_num;
    unordered_map<string, vector<string>> num_to_words;

    Solution(vector<string> &dict) {
        create_letter_to_num_map();
        create_num_to_words_map(dict);
    }

    void create_letter_to_num_map() {
        t9_letters.push_back({}); // 0
        t9_letters.push_back({}); // 1
        t9_letters.push_back({'a', 'b', 'c'}); // 2
        t9_letters.push_back({'d', 'e', 'f'}); // 3
        t9_letters.push_back({'g', 'h', 'i'}); // 4
        t9_letters.push_back({'j', 'k', 'l'}); // 5
        t9_letters.push_back({'m', 'n', 'o'}); // 6
        t9_letters.push_back({'p', 'q', 'r', 's'}); // 7
        t9_letters.push_back({'t', 'u', 'v'}); // 8
        t9_letters.push_back({'w', 'x', 'y', 'z'}); // 9

        for (int i = 0; i < t9_letters.size(); ++i) {
            for (char ch : t9_letters[i]) {
                letter_to_num[ch] = '0' + i;
            }
        }
    }

    void create_num_to_words_map(vector<string> &dict) {
        for (auto word : dict) {
            string num = convert_to_t9(word);
            num_to_words[num].push_back(word);
        }
    }

    string convert_to_t9(string word) {
        string num;
        for (auto ch : word) {
            auto it = letter_to_num.find(ch); 
            if (it != letter_to_num.end()) {
                num += it->second;
            }
        }
        return num;
    }

    vector<string> get_valid_t9_words(string numbers) {
        auto it = num_to_words.find(numbers);
        if (it != num_to_words.end()) {
            return it->second;
        } else {
            return {};
        }
    }
};

bool equal(vector<string> &a, vector<string> &b) {
    if (a.size() != b.size()) return false;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main(void) {
    vector<string> dict = {"apple", "used", "tree", "number", "letter", "bee", "cat"};
    Solution sol(dict);

    vector<string> tests = {
        "27753",
        "8733",
        };
    vector<vector<string>> answers = {
        {"apple"},
        {"used", "tree"},
        };

    for (int i = 0; i < tests.size(); ++i) {
        auto test = tests[i];
        auto ans = answers[i];
        vector<string> res = sol.get_valid_t9_words(test);
        cout << (equal(ans, res) ? "[PASS]" : "[FAIL]") << "test-" << i << endl;
    }
    return 0;
}
