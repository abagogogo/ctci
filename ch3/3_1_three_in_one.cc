#include <bits/stdc++.h>

using namespace std;

struct FixedMultiStack {
    int num_stack;
    int capacity;
    int *sizes;
    int *values;

    FixedMultiStack(int num, int size) {
        num_stack = num;
        capacity = size;
        sizes = new int[num_stack]();
        values = new int[num_stack * capacity];
    }

    virtual ~FixedMultiStack(void) {
        delete sizes;
        delete values;
    }

    bool is_full(int no) {
        return sizes[no] == capacity;
    }

    bool is_empty(int no) {
        return sizes[no] == 0;
    }

    int index_top(int no) {
        int idx = (no * capacity) + sizes[no] - 1;
        return idx;
    }

    int peek(int no) {
        if (is_empty(no)) assert(false);
        return values[index_top(no)];
    }

    void push(int no, int val) {
        if (is_full(no)) assert(false);
        ++sizes[no];
        values[index_top(no)] = val;
    }

    int pop(int no) {
        if (is_empty(no)) assert(false);
        int val = values[index_top(no)];
        --sizes[no];
        return val;
    }

    void debug(void) {
        printf("DBG: stack numbers: %d, capacity: %d\n", num_stack, capacity);
        for (int i = 0; i < num_stack; ++i) {
            printf("DBG: stack-%d size: %d\n", i, sizes[i]);
        }
        for (int i = 0; i < num_stack * capacity; ++i) {
            printf("DBG: [%d] %d\n", i, values[i]);
        }
    }
};

struct StackInfo {
    int start;
    int size;
    int capacity;
    int buf_size; // Size of buffer shared for all stacks.

    StackInfo(int a_start, int a_capacity, int a_buf_size) {
        start = a_start;
        size = 0;
        capacity = a_capacity;
        buf_size = a_buf_size;
    }

    int adjust(int index) {
        return ((index % buf_size) + buf_size) % buf_size;
    }

    bool is_within_stack_capacity(int index) {
        if (index < 0 || index >= buf_size) return false;

        int contiguous_idx = index < start ? index + buf_size : index;
        int end = start + capacity;
        return start <= contiguous_idx && contiguous_idx < end;
    }

    bool is_full(void) {
        return size == capacity;
    }

    bool is_empty(void) {
        return size == 0;
    }

    int capacity_index(void) {
        return adjust(start + capacity - 1);
    }

    int top_index(void) {
        return adjust(start + size - 1);
    }
};

struct MultiStack {
    vector<StackInfo *>info;
    int *values;
    int buf_size;

    MultiStack(int num, int size) {
        buf_size = num * size;

        values = new int[buf_size]();
        for (int i = 0; i < num; ++i) {
            int start = i * size;
            StackInfo *si = new StackInfo(start, size, buf_size);
            info.push_back(si);
        }
    }

    int num_of_elements(void) {
        int num = 0;
        for (auto si : info) {
            num += si->size;           
        }
        return num;
    }

    bool all_stacks_full(void) {
        return num_of_elements() == buf_size;
    }

    int adjust(int index) {
        return ((index % buf_size) + buf_size) % buf_size;
    }

    int next_index(int index) {
        return adjust(index + 1);
    }

    int prev_index(int index) {
        return adjust(index - 1);
    }

    void push(int no, int val) {
        if (all_stacks_full()) assert(false);
        
        StackInfo *si = info[no];
        if (si->is_full()) {
            expand(no);
        }
        si->size++;
        values[si->top_index()] = val;
    }

    void expand(int no) {
        printf("DBG: expanding stack-%d\n", no);
        shift((no + 1) % info.size());
        info[no]->capacity++;
    }

    void shift(int no) {
        printf("DBG: shifting stack-%d\n", no);
        StackInfo *si = info[no];

        if (si->size == si->capacity) {
            int next_no = (no + 1) % info.size();
            shift(next_no);
            si->capacity++;
        }

        int index = si->capacity_index();
        while (si->is_within_stack_capacity(index)) {
            values[index] = values[prev_index(index)];
            index = prev_index(index);
        }

        si->start = next_index(si->start);
        si->capacity--;
    }

    int pop(int no) {
        StackInfo *si = info[no];
        
        if (si->is_empty()) assert(false);
        int val = values[si->top_index()];
        si->size--;
        return val;
    }

    void debug(void) {
        int num_stack = info.size();
        printf("DBG: stack numbers: %d, buf_size: %d\n", num_stack, buf_size);
        for (int i = 0; i < num_stack; ++i) {
            printf("DBG: stack-%d start: %d, size: %d, capacity: %d\n", 
                   i, info[i]->start, info[i]->size, info[i]->capacity);
        }
        for (int i = 0; i < buf_size; ++i) {
            printf("DBG: [%d] %d\n", i, values[i]);
        }
    }
};

int main(void) {
    FixedMultiStack fs(3, 5);

    fs.push(0, 1);
    fs.push(1, 2);
    fs.push(2, 3);
    fs.push(0, 4);
    assert(fs.pop(1) == 2);
    assert(fs.peek(0) == 4);
    assert(fs.pop(0) == 4);

    MultiStack ms(3, 2);
    ms.push(0, 1);
    ms.push(1, 10);
    ms.push(2, 20);
    ms.debug();
    ms.push(0, 2);
    ms.push(0, 3);
    ms.debug();
    assert(ms.pop(0) == 3);
    assert(ms.pop(2) == 20);

    return 0;
}
