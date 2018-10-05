#include <iostream>

using namespace std;

struct Node {
    Node(int _value, Node *_next = nullptr) {
        value = _value;
        next  = _next;
    }
    Node   *next;
    int     value;
};

void print_list(Node *head, const string &msg) {
    cout << msg << endl;
    for (Node *curr = head; curr != nullptr; curr = curr->next)
        cout << curr->value << "->";
    cout << endl;
}

void insert_head(Node **head, Node **tail, Node *nd) {
    if (nullptr == *head) {
        *head = *tail = nd;
        nd->next = nullptr;
    } else {
        nd->next = *head;
        *head = nd;
    }
    //print_list(*head, "insert_head");
}

void insert_tail(Node **head, Node **tail, Node *nd) {
    if (nullptr == *head) {
        *head = *tail = nd;
        nd->next = nullptr;
    } else {
        (*tail)->next = nd;
        nd->next = nullptr;
        (*tail) = nd;
    }
    //print_list(*head, "insert_tail");
}

Node *partition(Node *head, int x) {
    Node *curr, *next;;
    Node *new_head = nullptr;
    Node *new_tail = nullptr;

    curr = head;
    while (curr) {
        next = curr->next;
        if (curr->value < x) {
            insert_head(&new_head, &new_tail, curr);
        } else {
            insert_tail(&new_head, &new_tail, curr);
        }
        curr = next;
    }
    return new_head;
}

int main(void) {
    Node n1(3);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(1);

    Node *head = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    Node *tail = &n5;

    print_list(head, "before");
    Node *new_head = partition(head, 3);
    print_list(new_head, "after");

    return 0;
}
