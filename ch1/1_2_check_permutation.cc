#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void count_string_map(const string &s, map<char, int> &m) {
    char c;

    for (int i = 0; i < s.length(); ++i) {
        c = s[i];
        //if (m.find(c) != m.end()) m[c] += 1;
        //else                      m[c]  = 1;
        m[c] += 1;
    }
}

bool is_perm_map(const string &s1, const string &s2) {
    map<char, int> m1, m2;

    if (s1.length() != s2.length()) return false;

    count_string_map(s1, m1); 
    count_string_map(s2, m2); 

    if (m1.size() != m2.size()) return false;
    for (auto it = m1.begin(); it != m1.end(); ++it) {
        if (it->second != m2[it->first]) return false;
    }
    return true;
}

void count_string_arr(const string &s, int *arr) {
    char c;

    for (int i = 0; i < s.length(); ++i) {
        c = s[i];
        arr[c] += 1;
    }
}

bool is_perm_arr(const string &s1, const string &s2) {
    int *arr1 = new int[26]();
    int *arr2 = new int[26]();

    if (s1.length() != s2.length()) return false;

    count_string_arr(s1, arr1); 
    count_string_arr(s2, arr2); 

    for (int i = 0; i < 26; ++i) {
        if (arr1[i] != arr2[i]) return false;
    }

    delete arr1;
    delete arr2;
    return true;
}

bool is_perm_sort(const string &s1, const string &s2) {
    string sorted1 = s1;
    string sorted2 = s2;

    sort(sorted1.begin(), sorted1.end());
    sort(sorted2.begin(), sorted2.end());
    return (sorted1.compare(sorted2) == 0);
}

bool is_perm(const string &s1, const string &s2) {
    //return is_perm_map(s1, s2);
    //return is_perm_arr(s1, s2);
    return is_perm_sort(s1, s2);
}

int main(void) {
    string s1 = "hello";
    string s2 = "okay";

    cout << (is_perm(s1, s2) ? "TRUE" : "FALSE") << endl;
    cout << (is_perm("oka", "kao") ? "TRUE" : "FALSE") << endl;
    return 0;
}

