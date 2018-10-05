#include <bits/stdc++.h>

using namespace std;

void build_freq_table(const string &str, map<char, int> &freq) {
    for (int i = 0; i < str.length(); ++i) {
        freq[str[i]]++;
    }
}

void get_perms(const string &prefix, int remaining, map<char, int> &freq, vector<string> &perms) {
    if (remaining == 0) {
        perms.push_back(prefix);
        return;
    }

    for (auto it = freq.begin(); it != freq.end(); ++it) {
        if (it->second > 0) {
            it->second--;
            get_perms(prefix + it->first, remaining - 1, freq, perms);
            it->second++; 
        }
    }
}

vector<string> get_perms(const string &str) {
    vector<string> perms;
    map<char, int> freq;

    build_freq_table(str, freq);
    get_perms("", str.length(), freq, perms);
    return perms;
}

int main(void) {
    string str = "abb";
    vector<string> perms = get_perms(str);
    for (int i = 0; i < perms.size(); ++i) {
        auto s = perms[i];
        cout << "[" << i << "] " << s << endl;
    }
    return 0;
}
