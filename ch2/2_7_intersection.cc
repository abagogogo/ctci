#include <iostream>

using namespace std;

struct Node {
    Node(int a_value) {
        value = a_value;
        next = nullptr;
    }

    Node *next;
    int value;
};

void print_list(Node *head, const string &msg = "") {
    cout << msg << endl;
    for (Node *curr = head; curr; curr = curr->next) {
        cout << curr->value << " -> ";
    }
    cout << endl;
}

int get_list_len_tail(Node *head, Node **tail) {
    int len = 0;
    while (head) {
        *tail = head;
        ++len;
        head = head->next;
    }
    return len;
}

Node *find_intersection(Node *list1, Node *list2) {
    int len1, len2;
    Node *tail1, *tail2;

    len1 = get_list_len_tail(list1, &tail1);
    len2 = get_list_len_tail(list2, &tail2);
    if (tail1 != tail2) return nullptr; // no intersection

    Node *longer, *shorter;
    int to_shift = 0;
    if (len1 >= len2) {
        longer = list1;
        shorter = list2;
        to_shift = len1 - len2;
    } else {
        longer = list2;
        shorter = list1;
        to_shift = len2 - len1;
    }
    for (;to_shift > 0; --to_shift) {
        longer = longer->next;
    }

    while (longer && shorter) {
        if (longer == shorter) {
            return longer; // found intersection
        }
        longer = longer->next;
        shorter = shorter->next;
    }
    return nullptr;
}

int main(void) {
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    Node n6(6);
    Node n7(7);
    Node n9(9);

    n7.next = &n2;
    n2.next = &n1;

    Node *list1 = &n3;
    n3.next = &n5;
    n5.next = &n9;
    n9.next = &n7;

    Node *list2 = &n4;
    n4.next = &n6;
    n6.next = &n7;

    print_list(list1, "list 1");
    print_list(list2, "list 2");
    
    Node *nd = find_intersection(list1, list2);
    if (nd) 
        cout << "intesection is at node " << nd->value << endl;
    else 
        cout << "No intesection!" << endl;

    return 0;
}
