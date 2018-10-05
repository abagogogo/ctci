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

void free_list(Node *l) {
    Node *next; 
    Node *curr = l;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

int get_list_len(Node *head) {
    int len = 0;
    while (head) {
        ++len;
        head = head->next;
    }
    return len;
}

void pad_list(Node **head, int pad_len) {
    for (; pad_len > 0; --pad_len) {
        Node *nd = new Node(0);
        nd->next = *head;
        *head = nd;
    }
    // TODO: to free the padded node. creating all nodes by new might be easier.
}

Node *add_rev_list_rec(Node *l1, Node *l2, int carry) {
    if (!l1 && !l2 && !carry) return nullptr;

    int tmp = carry;
    if (l1) tmp += l1->value;
    if (l2) tmp += l2->value;

    Node *nd = new Node(tmp % 10);
    nd->next = add_rev_list_rec(
                    l1 ? l1->next : nullptr, 
                    l2 ? l2->next : nullptr, 
                    tmp > 10 ? 1 : 0);
    return nd;
}

Node *add_rev_list(Node *l1, Node *l2) {
    return add_rev_list_rec(l1, l2, 0);
}

struct SumWrap {
    SumWrap(void) {
        head = nullptr;
        carry = 0;
    }   
    Node *head;
    int   carry;
};

#if 0
void add_list_rec(Node *l1, Node *l2, SumWrap *wrap) {
    if (!l1 || !l2 || !wrap) return;

    add_list_rec(l1->next, l2->next, wrap);
    int value = l1->value + l2->value + wrap->carry;
    Node *nd = new Node(value % 10);
    nd->next = wrap->head;
    wrap->head = nd;
    wrap->carry = value > 10 ? 1 : 0;
}

Node *add_list(Node *l1, Node *l2) {
    SumWrap wrap;

    // get list lengths.
    int len1 = get_list_len(l1);
    int len2 = get_list_len(l2);

    // pad zero for short one.
    if (len1 != len2) {
        pad_list(len1 < len2 ? &l1 : &l2, abs(len1-len2));
    }

    add_list_rec(l1, l2, &wrap);
    if (wrap.carry) {
        Node *nd = new Node(wrap.carry);
        nd->next = wrap.head;
        return nd;
    } else {
        return wrap.head;
    }
}
#else
void add_list_rec_no_wrap(Node *l1, Node *l2, Node **new_head, int *carry) {
    if (!l1 || !l2 || !carry) return;

    add_list_rec_no_wrap(l1->next, l2->next, new_head, carry);
    int sum = *carry;
    if (l1) sum += l1->value;
    if (l2) sum += l2->value;

    Node *node = new Node(sum % 10);
    node->next = *new_head;
    *carry = sum / 10;
    *new_head = node;
}

Node *add_list(Node *l1, Node *l2) {
    int len1 = get_list_len(l1);
    int len2 = get_list_len(l2);

    if (len1 != len2) {
        pad_list((len1 > len2 ? &l2 : &l1), abs(len1 - len2));
    }

    Node *new_head = nullptr;
    int  carry = 0;
    add_list_rec_no_wrap(l1, l2, &new_head, &carry);
    return new_head;
}
#endif

int main(void) {
    Node n1(7);
    Node n2(1);
    Node n3(6);
    Node *l1 = &n1;
    n1.next = &n2;
    n2.next = &n3;
    
    Node n2_1(5);
    Node n2_2(9);
    Node n2_3(2);
    Node *l2 = &n2_1;
    n2_1.next = &n2_2;
    n2_2.next = &n2_3;

    print_list(l1, "list 1 (reverse)");
    print_list(l2, "list 2 (reverse)");
    Node *sum = add_rev_list(l1, l2);
    print_list(sum, "sum (revise)");
    free_list(sum);

    Node n4(1);
    l1 = &n4;
    n4.next = &n3;
    n3.next = &n2;
    n2.next = &n1;
    n1.next = nullptr;

    l2 = &n2_3;
    n2_3.next = &n2_2;
    n2_2.next = &n2_1;
    n2_1.next = nullptr;
    print_list(l1, "list 1");
    print_list(l2, "list 2");
    sum = add_list(l1, l2);
    print_list(sum, "sum");
    free_list(sum);

    return 0;
}
