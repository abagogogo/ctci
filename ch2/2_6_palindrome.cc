#include <bits/stdc++.h>

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

int get_list_len(Node *head) {
    int len = 0;
    while (head) {
        ++len;
        head = head->next;
    }
    return len;
}

struct PalRet {
    PalRet(bool _result, Node *_head) {
        result = _result;
        head   = _head;
    }
    bool result;
    Node *head;
};

#if 0
PalRet *is_palindrome_rec(Node *head, int len) {
    if (!head || 0 >= len) { // even nodes
        return new PalRet(true, head);
    } else if (1 == len) { // odd nodes
        return new PalRet(true, head->next);
    }

    PalRet *ret = is_palindrome_rec(head->next, len - 2);
    if (!ret->result || !ret->head) return ret;

    ret->result = (ret->head->value == head->value);
    ret->head = ret->head->next;
    return ret;
}

bool is_palindrome(Node *head) {
    int len = get_list_len(head);
    PalRet *ret = is_palindrome_rec(head, len);
    bool result = ret->result;
    free(ret);
    return result;
}
#else // review

bool check_palindrome(vector<int> &values) {
    int head = 0;
    int tail = values.size() - 1;
    int half = values.size() / 2;
    for (int offset = 0; offset < half; ++offset) {
        if (values[head + offset] != values[tail - offset]) 
            return false;
    }
    return true;
}

bool is_palindrome_v1(Node *head) {
    vector<int> values;
    Node *curr = head;
    while (curr) {
        values.push_back(curr->value);
        curr = curr->next;
    }
    return check_palindrome(values);
}

bool is_palindrome_v2(Node *head) {
    vector<int> values;
    Node *curr = head;
    int len = get_list_len(head);
    int half = len / 2;

    for (int i = 0; i < half; ++i) {
        values.push_back(curr->value);
        curr = curr->next;
    }

    if (len % 2 == 1) curr = curr->next;

    while (curr) {
        int peer = values.back();
        values.pop_back();
        if (curr->value != peer) return false;
        curr = curr->next;
    }
    return true;
}

bool check_palindrome(Node *head, Node **peer, int len) {
    if (len <= 0) {
        *peer = head;
        return true;
    } else if (len == 1) {
        *peer = head->next;
        return true;
    }

    bool ret = check_palindrome(head->next, peer, len - 2);
    if (!ret || head->value != (*peer)->value) {
        return false;
    }

    *peer = (*peer)->next;
    return true;
}

bool is_palindrome_v3(Node *head) {
    int len = get_list_len(head);
    if (len <= 1) return true;
    Node *peer = nullptr;

    return check_palindrome(head, &peer, len);
}

bool is_palindrome(Node *head) {
    //return is_palindrome_v1(head);
    //return is_palindrome_v2(head);
    return is_palindrome_v3(head);
}

#endif

int main(void) {
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(2);
    Node n5(1);

    Node *head = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    Node *tail = &n5;

    print_list(head, "list");
    cout << (is_palindrome(head) ? "is " : "is NOT ");
    cout << "a palindome" << endl;

    return 0;
}
