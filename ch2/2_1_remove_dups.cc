#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

struct Node {
    Node(int _value, Node *_next = nullptr) {
        value = _value;
        next  = _next;
    }

    Node *next;
    int   value;
};

// O(n) time, O(n) extra space.
// TOOD: handle memory leakage.
void remove_dup(Node *head) {
    unordered_set<int> set;

    Node *cur  = head;
    Node *last = nullptr;
    while (cur) {
        if (set.find(cur->value) == set.end()) {
            set.insert(cur->value);
            last = cur;
        } else {
            last->next = cur->next;
        }
        cur = cur->next;
    }
}

// O(n^2) time but no extra buffer.
// TOOD: handle memory leakage.
void remove_dup_nobuf(Node *head) {
    Node *i, *j, *last;

    i = head;
    while (i) {
        last = i;
        j = i->next;
        while (j) {
            if (j->value == i->value) {
                last->next = j->next;
            } else {
                last = j;
            }
            j= j->next;
        }
        i = i->next;
    }
}

void print_list(Node *head, const string &msg) {
    cout << msg << endl;
    for (Node *cur = head; cur; cur = cur->next) {
        cout << cur->value << "->";
    }
    cout << endl;
}

int main(void) {
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4_2(2);
    Node n5_3(3);

    Node *head = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4_2;
    n4_2.next = &n5_3;

    print_list(head, "before");
    //remove_dup(head);
    remove_dup_nobuf(head);
    print_list(head, "after");

    return 0;
}
