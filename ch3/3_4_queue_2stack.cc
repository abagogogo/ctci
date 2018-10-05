#include <iostream>
#include <vector>

using namespace std;

template <class T> 
class MyQueue {
public:
    MyQueue(void) {
        cout << "hello" << endl;
    }

    int size(void) {
        return oldest.size() + newest.size();
    }

    void add(T value) {
        // push onto newest stack, which always has the newest elements on top.
        newest.push_back(value);
    }

    T peek(void) {
        shift_stacks(); // ensure oldest has the current elements.
        return oldest.back();
    }

    T remove(void) {
        T value = peek();
        oldest.pop_back();
        return value;
    }

protected:
    void shift_stacks(void) {
        if (oldest.empty()) {
            while (!newest.empty()) {
                oldest.push_back(newest.back());
                newest.pop_back();
            }
        }
    }

protected:
    vector<T> oldest;
    vector<T> newest;
};

template <class T>
void print_vector(vector<T> &s, const string &msg) {
    cout << msg << endl;
    for (auto n : s) cout << n << ", ";
    cout << endl;
}

int main(void) {
    vector<int> t = {5, 3, 1, 4, 2};
    vector<int> u;
    MyQueue<int> q;

    print_vector(t, "t: ");
    for (auto n : t) {
        q.add(n);
    }
    while (q.size() > 0) {
        int value = q.remove();
        u.push_back(value);
    }

    if (t == u) cout << "[PASS] t == u" << endl;
    else cout << "[FAIL] t != u" << endl;

    return 0;
}
