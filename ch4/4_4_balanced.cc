#include "tree.h"

#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

#if 0
int max_depth(TreeNode *node) {
    if (!node) return 0;
    return (max(max_depth(node->left), max_depth(node->right)) + 1);
}

int min_depth(TreeNode *node) {
    if (!node) return 0;
    return (min(min_depth(node->left), min_depth(node->right)) + 1);
}

bool is_balanced(TreeNode *tree) {
    return (max_depth(tree) - min_depth(tree) <= 1);
}
#else
int check_height(TreeNode *node) {
    if (!node) return -1;

    int left_height = check_height(node->left);
    if (left_height == INT_MIN) return INT_MIN; // left tree is imbalanced.

    int right_height = check_height(node->right);
    if (right_height == INT_MIN) return INT_MIN; // right tree is imbalanced.

    if (abs(left_height - right_height) > 1) {
        return INT_MIN;
    } else {
        return max(left_height, right_height) + 1;
    }
}

bool is_balanced(TreeNode *tree) {
    return check_height(tree) != INT_MIN;
}
#endif

int main(void) {
    TreeNode *tree1 = new TreeNode(0);
    TreeNode *left = tree1->add_left(1);
    TreeNode *right = tree1->add_right(2);
    left->add_left(3);
    left->add_right(4);
    right->add_left(5);

    cout << "tree1 is " << (is_balanced(tree1) ? "balanced." : "NOT balanced.") << endl;
    
    TreeNode *tree2 = new TreeNode(0);
    tree2->add_left(1)->add_right(2)->add_left(3);
    cout << "tree2 is " << (is_balanced(tree2) ? "balanced." : "NOT balanced.") << endl;

    cout << "null tree is " << (is_balanced(nullptr) ? "balanced." : "NOT balanced.") << endl;

    return 0;
}
