#include <bits/stdc++.h>

using namespace std;

struct Listy {
    vector<int> data;

    int element_at(int pos) {
        if (pos < 0 || pos >= data.size()) return -1;
        return data[pos];
    }

    int push_back(int value) {
        data.push_back(value);
    }
};

int binary_search(Listy &list, int target, int low, int high) {
    int mid;
    int cur_val;

    while (low <= high) {
        mid = (low + high) / 2;

        cur_val = list.element_at(mid);
        if (cur_val == -1 || cur_val > target) {
            high = mid - 1;
        } else if (cur_val < target) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int search(Listy &list, int value) {
    int index = 1;
    while (list.element_at(index) != -1 
       && list.element_at(index) < value) {
        index *= 2;
    }
    return binary_search(list, value, index / 2, index);
}

int main(void) {
    Listy list;

    list.push_back(1);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(10);

    int value;
    value = 1;
    cout << "search " << value << " = " << search(list, value) << endl;
    value  = 3;
    cout << "search " << value << " = " << search(list, value) << endl;
    value  = 6;
    cout << "search " << value << " = " << search(list, value) << endl;
    value = 10;
    cout << "search " << value << " = " << search(list, value) << endl;
    value = 11;
    cout << "search " << value << " = " << search(list, value) << endl;

    return 0;
}
