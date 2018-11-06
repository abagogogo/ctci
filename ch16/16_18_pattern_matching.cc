#include <bits/stdc++.h>

using namespace std;

struct Solution {
    bool does_match(const string &pattern, const string &value) {
        if (pattern.length() == 0) return value.length() == 0;

        char main_char = pattern[0];
        char alt_char = (main_char == 'a' ? 'b' : 'a');
        int size = value.length();

        int count_of_main = count_of(pattern, main_char);
        int count_of_alt = pattern.length() - count_of_main;
        //printf("DBG: main_char: %c, %d, alt_char: %c, %d\n", main_char, count_of_main, alt_char, count_of_alt);
        size_t first_alt = pattern.find_first_of(alt_char);
        int max_main_size = size / count_of_main;
        //printf("DBG: first_alt: %d, max_main_size: %d\n", first_alt, max_main_size);

        for (int main_size = 0; main_size <= max_main_size; ++main_size) {
            int remaining_length = size - main_size * count_of_main;
            string first = value.substr(0, main_size);

            if (count_of_alt == 0 || remaining_length % count_of_alt == 0) {
                int alt_index = first_alt * main_size;
                int alt_size = count_of_alt == 0 ? 0 : remaining_length / count_of_alt;
                string second = count_of_alt == 0 ? "" : value.substr(alt_index, alt_size);
                string cand = build_from_pattern(pattern, first, second);
                //printf("DBG: main_size: %d, first: %s, alt_size: %d, second: %s => cand = %s\n", main_size, first.c_str(), alt_size, second.c_str(), cand.c_str());
                if (value == cand) {
                    return true;
                }
            }
        }

        return false;
    }

    int count_of(const string &pattern, char ch) {
        int count = 0;
        for (int i = 0; i < pattern.length(); ++i) 
            if (pattern[i] == ch) count++;
        return count;
    }

    string build_from_pattern(const string &pattern, const string &main, const string &alt) {
        string res;
        char first = pattern[0];
        for (auto ch : pattern)
            res += (ch == first) ? main : alt;
        return res;
    }
};

int main(void) {
    Solution sol;

    vector<pair<string, string>> tests = {
        {"aabab", "catcatgocatgo"},
        {"a", "catcatgocatgo"},
        {"b", "catcatgocatgo"},
        {"ab", "catcatgocatgo"},
        };
    vector<bool> answers = {
        true, 
        true, 
        true, 
        true,
        };

    for (int i = 0; i < tests.size(); ++i) {
        auto test = tests[i];
        int ans = answers[i];
        const string &pattern = test.first;
        const string &value = test.second;
        int res = sol.does_match(pattern, value);
        cout << ((ans == res) ? "[PASS]" : "[FAIL]") << "test-" << i <<  " res = " << res << endl;
    }
    return 0;
}
