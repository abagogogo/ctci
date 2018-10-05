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

void delete_node(Node *nd) {
    if (!nd || !nd->next) return;

    nd->value = nd->next->value;
    nd->next  = nd->next->next;
}

int main(void) {
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);

    Node *head = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;

    print_list(head, "before");
    delete_node(&n3);
    print_list(head, "after");

    return 0;
}
