#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool is_unique(const string &s) {
    map<char, bool> found;
    char c;

    for (int i = 0; i < s.length(); ++i) {
        c = s[i];
        if (found.find(c) != found.end()) return false;
        found[c] = true;
    }

    return true;
}

int main(void) {
    string s1 = "hello";
    string s2 = "okay";

    for (auto s : {s1, s2}) { 
        cout << s << " is " << (is_unique(s) ? "unique" : "NOT unique") << endl;
    }

    return 0;
}

