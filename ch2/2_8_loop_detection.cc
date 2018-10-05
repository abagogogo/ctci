#include <iostream>

using namespace std;

struct node {
    node(char _value, struct node *_next = nullptr) {
        value = _value;
        next  = _next;
    }

    struct node *next;
    char         value;
};

struct list {
    list(void) {
        head = tail = nullptr;
    }

    bool is_empty(void) {
        return (nullptr == head);
    }

    void insert(struct node *n) {
        if (is_empty()) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        n->next = nullptr;
    }

    struct node *head;
    struct node *tail;
};

struct node *find_loop_begin(struct node *head) {
    struct node *slow = head;
    struct node *fast = head;

    if (!head) return nullptr;

    // Check if loops exist and if so, 
    // find 1st meet point (loop_size - k).
    bool has_loop = false;
    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            has_loop = true;
            break;
        }
    };

    if (!has_loop) return nullptr;

    // Move both of them at the same pace to find 2nd meeting point 
    // as the beginning of the loop.
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

int main(void) {
    struct node a('a');
    struct node b('b');
    struct node c('c');
    struct node d('d');
    struct node e('e');

    struct node *head;
    head = &a;
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &c;

    struct node *k = find_loop_begin(head);
    cout << "loop begins at " << k->value << endl;

//    struct node *cur = head;
//    for (int i = 0; i < 6 && cur; ++i) {
//        cout << cur->value << " -> ";
//        cur = cur->next;
//    }
//    cout << endl;

    return 0;
}
