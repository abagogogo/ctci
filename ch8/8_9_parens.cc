#include <bits/stdc++.h>

using namespace std;

void add_paren(vector<string> &list, int left_rem, int right_rem, char *str, int index) {
    if (left_rem < 0 || right_rem < left_rem) return; // invalid state.

    if (left_rem == 0 && right_rem == 0) {
        list.push_back(str);
    } else {
        str[index] = '(';
        add_paren(list, left_rem - 1, right_rem, str, index + 1);

        str[index] = ')';
        add_paren(list, left_rem, right_rem - 1, str, index + 1);
    }
}

void gen_parens(int count, vector<string> &list) {
    char * str = new char[count * 2 + 1]();
    add_paren(list, count, count, str, 0);
}

int main(void) {
    vector<string> result;
    gen_parens(3, result);

    for (auto s : result) {
        cout << s << endl;
    }
    return 0;
}
