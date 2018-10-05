#include <iostream>
#include <vector>

using namespace std;

void sort_stack(vector<int> &s) {
    vector<int> r;

    while (!s.empty()) {
        // insert each element in s in reversely sorted order into r.
        int tmp = s.back(); s.pop_back();
        while (!r.empty() && r.back() > tmp) {
            s.push_back(r.back());
            r.pop_back();
        }
        r.push_back(tmp);
    }

    // copy the elements from r back to s. and it's now sorted order.
    while (!r.empty()) {
        s.push_back(r.back());
        r.pop_back();
    }
}

void print_vector(vector<int> &s, const string &msg) {
    cout << msg << endl;
    for (auto n : s) cout << n << ", ";
    cout << endl;
}

int main(void) {
    vector<int> s = {5, 3, 1, 4, 2};

    print_vector(s, "before");
    sort_stack(s);
    print_vector(s, "after");

    return 0;
}
