#include "tree.h"
#include <bits/stdc++.h>

#if 0 // with parent link
int depth(PTreeNode *node) {
    int depth = 0;
    while (node->parent) {
        node = node->parent;
        depth++;
    }
    return depth;
}

PTreeNode *move_up(PTreeNode *node, int levels) {
    while (levels > 0 && node) {
        levels--;
        node = node->parent;
    }
    return node;
}

PTreeNode *common_ancestor(PTreeNode *root, PTreeNode *p, PTreeNode *q) {
    int p_depth = depth(p);
    int q_depth = depth(q);
    PTreeNode *first = (p_depth <= q_depth) ? p : q;
    PTreeNode *second = (p_depth > q_depth) ? p : q;
    
    second = move_up(second, abs(p_depth - q_depth));
    while (first && second) {
        if (first == second) break;
        first = first->parent;
        second = second->parent;
    }
    return first;
}
#else
bool covers(PTreeNode *root, PTreeNode *node) {
    if (!root || !node) return false;
    if (root == node) return true;
    return covers(root->left, node) || covers(root->right, node);
}

PTreeNode *ancestor_helper(PTreeNode *root, PTreeNode *p, PTreeNode *q) {
    if (!root || !p || !q) return nullptr;
    if (root == p || root == q) return root;

    bool p_on_left = covers(root->left, p);
    bool q_on_left = covers(root->left, q);
    if (p_on_left != q_on_left) { // p and q are not on the same side.
        return root;
    }
    PTreeNode *child = p_on_left ? root->left : root->right;
    return ancestor_helper(child, p, q);
}

PTreeNode *common_ancestor(PTreeNode *root, PTreeNode *p, PTreeNode *q) {
    if (!covers(root, p) || !covers(root, q)) return nullptr;
    return ancestor_helper(root, p, q);
}
#endif

int main(void) {
    PTreeNode *tree1 = new PTreeNode(0);
    PTreeNode *left = tree1->add_left(1);
    PTreeNode *right = tree1->add_right(4);
    left->add_left(2);
    left->add_right(3);
    right->add_left(5);

    PTreeNode *a = left->left;
    PTreeNode *b = tree1->right->left;
    cout << "a=" << a->value << endl;
    cout << "b=" << b->value << endl;
    cout << "common ancestor=" << common_ancestor(tree1, a, b)->value << endl;

    a = left->left;
    b = left->right;
    cout << "a=" << a->value << endl;
    cout << "b=" << b->value << endl;
    cout << "common ancestor=" << common_ancestor(tree1, a, b)->value << endl;

    a = tree1;
    b = tree1;
    cout << "a=" << a->value << endl;
    cout << "b=" << b->value << endl;
    cout << "common ancestor=" << common_ancestor(tree1, a, b)->value << endl;

    return 0;
}
