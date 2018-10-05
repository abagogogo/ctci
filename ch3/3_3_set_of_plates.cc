#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template<class T>
class MyStack {
public:
    MyStack(int _capacity) {
        capacity = _capacity;
    }

    bool push(T value) {
        if (full()) return false;
        data.push_back(value);
    }

    T pop(void) {
        T value = data.back();
        data.pop_back();
        return value;
    }

    T remove_bottom(void) {
        T value = data.front();
        data.pop_front();
        return value;
    }

    bool empty(void) {
        return data.empty();
    }

    bool full(void) {
        return data.size() == capacity;
    }

protected:
    int capacity;
    deque<T> data;
};

template<class T>
class SetOfStacks {
public:
    SetOfStacks(int _capacity) {
        capacity = _capacity;
    }

    void push(T value) {
        MyStack<T> last = get_last_stack();

        if (last && !last->full()) {
            last->push(value);
        } else {
            last = new MyStack<T>(capacity);
            last->push(value);
            stacks.push_back(last);
        }
    }

    T pop(void) {
        MyStack<T> last = get_last_stack();
        T value;

        if (!last) throw -1;

        value = last->pop();
        if (last->empty()) {
            stacks.pop_back();
            delete last;
        }
        return value;
    }

    T pop_at(int index) {
        return left_shift(index, true);
    }

    bool empty(void) {
        MyStack<T> *last = get_last_stack();
        return !last || last->empty();
    }

protected:
    MyStack<T> *get_last_stack(void) {
        if (stacks.empty) return nullptr;
        else return &stacks.back();
    }

    T left_shift(int index, bool remove_top) {
        MyStack<T> *stack = &stacks[index];
        T removed;

        if (remove_top) removed = stack->pop();
        else removed = stack->remove_bottom();
        if (stack->empty()) {
            stacks.erase(stacks.begin() + index);
            delete stack;
        } else if (index + 1 < stacks.size()) {
            T tmp = left_shift(index + 1, false);
            stack->push(tmp);
        }

        return removed;
    }

protected:
    vector<MyStack<T>> stacks;
    int capacity;
};

int main(void) {
    SetOfStacks<int> stacks(3);

    return 0;
}
