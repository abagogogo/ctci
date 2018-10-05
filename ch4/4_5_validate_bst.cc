#include "tree.h"

#include <bits/stdc++.h>

using namespace std;

#if 0

struct WrapInt {
    bool valid;
    int value;
};

bool check_bst(TreeNode *node, WrapInt *last) {
    if (!node) return true;

    // check left
    if (!check_bst(node->left, last)) return false;
    
    // check current
    if (last->valid && node->value <= last->value) return false;
    last->valid = true;
    last->value = node->value;

    // check right
    if (!check_bst(node->right, last)) return false;

    return true;
}

bool check_bst(TreeNode *node) {
    WrapInt w = {false, INT_MIN};
    return check_bst(node, &w);    
}

#else // Min / Max pointer
bool check_bst(TreeNode *node, int *min, int *max) {
    if (!node) return true;

    if (min && node->value <= *min) return false; // Watch out <=, it's for bst right subtree.
    if (max && node->value > *max) return false;

    if (!check_bst(node->left, min, &node->value) ||
        !check_bst(node->right, &node->value, max)) {
        return false;
    }
    return true;
}

bool check_bst(TreeNode *node) {
    check_bst(node, nullptr, nullptr);    
}
#endif

int main(void) {
    TreeNode *tree1 = new TreeNode(3);
    TreeNode *left = tree1->add_left(1);
    TreeNode *right = tree1->add_right(5);
    left->add_left(0);
    left->add_right(2);
    right->add_left(4);
    cout << "tree1 is " << (check_bst(tree1) ? "BST => OK" : "NOT BST => NG") << endl;

    TreeNode *tree2 = new TreeNode(20);
    right = tree2->add_right(20);
    cout << "tree2 is " << (check_bst(tree2) ? "BST => NG" : "NOT BST => OK") << endl;

    TreeNode *tree3 = new TreeNode(20);
    left = tree3->add_left(10);
    right = tree3->add_right(30);
    left->add_right(25);
    cout << "tree3 is " << (check_bst(tree3) ? "BST => NG" : "NOT BST => OK") << endl;
    
    return 0;
}
