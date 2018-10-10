#include <bits/stdc++.h>

using namespace std;

#if 0 // insert first char to all locations of pemutation of reminder. 
string insert_at(const string &word, char ch, int pos) {
    string start = word.substr(0, pos);
    string end   = (pos < word.length() ? word.substr(pos) : "");
    //cout << "DBG: insert_at() end=" << end << endl;
    return start + ch + end;
}

vector<string> get_perms(const string &str) {
    vector<string> perms;

    if (str.length() == 0) {
        perms.push_back("");
        return perms;
    }

    char first = str[0];
    string reminder = str.substr(1);
    //cout << "DBG: first: " << first << " , reminder: " << reminder << endl;
    vector<string> words = get_perms(reminder);
    for (auto word : words) {
        //cout << "DBG: word: " << word << endl;
        for (int pos = 0; pos <= word.length(); ++pos) {
            string s = insert_at(word, first, pos);
            //cout << "DBG: s to push_back(): " << s << endl;
            perms.push_back(s);
        }
    }

    return perms;
}
#else // recurse with prefix which append each char of reminder in turns.
void get_perms(const string &prefix, const string &reminder, vector<string> &perms) {
    int len = reminder.length();
    if (len <= 1) {
        perms.push_back(prefix + reminder);
        return;
    }

    for (int pos = 0; pos < len; ++pos) {
        string before = reminder.substr(0, pos);
        string after  = (pos + 1 < len ? reminder.substr(pos + 1) : "");
        char ch = reminder[pos];

        get_perms(prefix + ch, before + after, perms);
    }
}

vector<string> get_perms(const string &str) {
    vector<string> perms;
    get_perms("", str, perms);
    return perms;
}
#endif

int main(void) {
    string str = "abcd";
    vector<string> perms = get_perms(str);
    for (int i = 0; i < perms.size(); ++i) {
        auto s = perms[i];
        cout << "[" << i << "] " << s << endl;
    }
    return 0;
}
