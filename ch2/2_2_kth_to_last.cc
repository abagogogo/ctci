#include <iostream>

using namespace std;

struct Node {
    Node(int _value, Node *_next = nullptr) {
        value = _value;
        next  = _next;
    }
    Node *next;
    int   value;
};

Node *get_kth_to_last(Node *head, int k) {
    Node *runner = head;
    for (int i = 0; i < k; ++i) {
        if (!runner) return nullptr;
        runner = runner->next;
    }

    Node *curr = head;
    while (runner) {
        runner = runner->next;
        curr = curr->next;
    }
    return curr;
}

Node *_get_kth_to_last_rec(Node *head, int k, int &ridx) {
    if (nullptr == head) return nullptr;
    Node *nd = _get_kth_to_last_rec(head->next, k, ridx);
    ridx++;
    if (ridx == k) return head;
    else           return nd;
}

Node *get_kth_to_last_rec(Node *head, int k) {
    int ridx = 0;
    return _get_kth_to_last_rec(head, k, ridx);
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

    int k = 2;
    Node *tmp = get_kth_to_last_rec(head, k);
    cout << "k=" << k << ", node=" << tmp->value << endl;

    return 0;
}
