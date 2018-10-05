#include <iostream>
#include <vector>
#include <climits> // for INT_MAX

using namespace std;

class StackMin {
public:
    StackMin(void) {
    }

    void push(int value) {
        if (value <= min()) {
            min_stack.push_back(value);
        }
        data.push_back(value);
    }

    int pop(void) {
        if (data.empty()) throw -1;
        int value = data.back(); data.pop_back();
        if (value == min_stack.back()) min_stack.pop_back();
        return value;
    }

    bool empty(void) {
        return data.empty();
    }

    int min(void) {
        if (min_stack.empty()) return INT_MAX;
        return min_stack.back();
    }

protected:
    vector<int> data;
    vector<int> min_stack;
};

int main(void) {
    StackMin s;

    s.push(2);
    cout << "min=" << s.min() << endl;
    s.push(1);
    cout << "min=" << s.min() << endl;
    s.push(1);
    cout << "min=" << s.min() << endl;
    s.push(3);
    cout << "min=" << s.min() << endl;

    while (!s.empty()) {
        s.pop();
        cout << "pop -> min=" << s.min() << endl;
    }

    return 0;
}
