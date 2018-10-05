#include <bits/stdc++.h>

using namespace std;

int find_mid(vector<string> &list, int first, int last, int mid) {
    int left = mid - 1;
    int right = mid + 1;
    while (true) {
        if (left < first && right > last) {
            return -1;
        } else if (right < last && !list[right].empty()) {
            return right;
        } else if (left >= first && !list[left].empty()) {
            return left;
        }
        --left;
        ++right;
    }
}

int search(vector<string> &list, const string &target, int first, int last) {
    if (first < 0 || last >= list.size()) return -1;
    if (first > last) return -1;

    int mid = (first + last) / 2;

    if (list[mid].empty()) {
        mid = find_mid(list, first, last, mid);
        if (mid == -1) return -1;
    }
       
    if (list[mid] == target) {
        return mid;
    } else if (list[mid].compare(target) < 0) {
        return search(list, target, mid + 1, last);
    } else {
        return search(list, target, first, mid - 1);
    }
}

int main(void) {
    vector<string> list = {
        "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""
        };

    string target = "ball";
    int pos = search(list, target, 0, list.size()-1);
    cout << "search " << target << " => " << pos << endl;

    target = "car";
    pos = search(list, target, 0, list.size()-1);
    cout << "search " << target << " => " << pos << endl;

    target = "dad";
    pos = search(list, target, 0, list.size()-1);
    cout << "search " << target << " => " << pos << endl;

    return 0;
}
