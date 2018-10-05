#include "tree.h"

#include <bits/stdc++.h>

using namespace std;

PTreeNode *left_most(PTreeNode *node) {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    return node;
}

PTreeNode *in_order_succ(PTreeNode *node) {
    if (!node) return nullptr;
    if (node->right) return left_most(node->right);

    PTreeNode *parent = node->parent;
    while (parent && parent->left != node) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

int main(void) {
    PTreeNode *tree1 = new PTreeNode(3);
    PTreeNode *left = tree1->add_left(1);
    PTreeNode *right = tree1->add_right(5);
    left->add_left(0);
    left->add_right(2);
    right->add_left(4);

    cout << tree1->value << " succ: " << in_order_succ(tree1)->value << endl;
    cout << left->value << " succ: " << in_order_succ(left)->value << endl;
    cout << left->right->value << " succ: " << in_order_succ(left->right)->value << endl;

    return 0;
}
