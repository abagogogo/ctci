#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

#if 0
bool is_palindrome(char *input) {
    unordered_map<char, int> table;
    string str = input;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    cout << "str: " << str << endl;

    for (char c : str) {
        if (c >= 'a' && c <= 'z') table[c] += 1;
    }

    int num_odd = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        if (it->second % 2) {
            num_odd++;
            if (num_odd > 1) {
                //return false;
            }
        }
    }
    return true;
}
#else
#include <bits/stdc++.h>

bool is_palindrome(char *input) {
    unordered_map<char,int> cnt;

    int len = strlen(input);
    for (int i = 0; i < len; ++i) {
        int ch = input[i];
        if (ch == ' ') continue;
        //if (ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';
        ch = tolower(ch);
        cnt[ch]++;
    }

    int num_odd = 0;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        if (it->second % 2 == 1) {
            if (++num_odd > 1) return false;
        }
    }
    return true;
}
#endif

int main(void) {
    char input[] = "Tact Coa";

    printf("%s: %s\n", input, (is_palindrome(input) ? "[PASS]" : "[FAIL]"));
    return 0;
}
