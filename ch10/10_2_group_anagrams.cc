#include <bits/stdc++.h>

using namespace std;

string sorted_string(const string &a) {
    string sorted;
    int freqs[128] = {0};

    for (auto ch : a) {
        freqs[ch]++;
    }
    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < freqs[i]; ++j) {
            sorted += (char)i;
        }
    }
    return sorted;
}

vector<string> sort(vector<string> arr) {
    map<string,vector<string>> map_list;
    vector<string> sorted;

    for (auto str : arr) {
        string key = sorted_string(str);
        map_list[key].push_back(str);
    }
    for (auto it = map_list.begin(); it != map_list.end(); ++it) {
        for (auto str : it->second) {
            sorted.push_back(str);            
        }
    }
    return sorted;
}

int main(void) {
    vector<string> arr = {
        "array",
        "acre",
        "rayra",
        "race",
        "cat",
        "care",
        "tca",
        };

    vector<string> sorted = sort(arr);
    for (auto str : sorted) 
        cout << str << endl;

    return 0;
}
