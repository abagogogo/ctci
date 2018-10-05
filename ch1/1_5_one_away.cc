#include <iostream>
#include <string>

using namespace std;

bool is_one_away(const string &str1, const string &str2) {
    const string &shorter = (str1.length() <= str2.length()) ? str1 : str2;
    const string &longer  = (str1.length()  > str2.length()) ? str1 : str2;

    int si = 0;
    int li = 0;
    bool found = false;
    while (si < shorter.length()) {
        if (shorter[si] == longer[li]) {
            si++;
            li++;
        } else {
            if (found) return false;
            found = true;
            if (shorter.length() == longer.length()) {
                si++;
                li++;
            } else {
                li++;
            }
        }
    }
    return true;
}

int main(void) {
    string str1 = "hello";
    string str2 = "hallo";

    bool one_away = is_one_away(str1, str2);
    cout << str1 << ", " << str2 << (one_away ? " are one away" : " are NOT one away") << endl;

    return 0;
}
