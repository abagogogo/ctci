#include <iostream>
#include <string>

using namespace std;

bool is_rotate(const string &str1, const string &str2) {
    if (str1.length() != str2.length()) return false;

    // concatnate 1st string.
    string str_cc = str1 + str1;

    // find in the concated one.
    return (str_cc.find(str2) != string::npos);
}

int main(void) {
    string str1 = "waterbottle";
    string str2 = "erbottlewat";

    cout << str1 << ", ";
    cout << str2 << ", ";
    cout << (is_rotate(str1, str2) ? "TRUE" : "FALSE") << endl;

    return 0;
}
