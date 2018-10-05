#include "tree.h"
#include <bits/stdc++.h>

using namespace std;

#if 0 // time: O(n + m), space: O(n + m)
void get_string(TreeNode *root, string &order) {
    // TODO: inorder traverse.
    if (!root) {
        order += 'x';
        return;
    }

    order += std::to_string(root->value);
    get_string(root->left, order);
    get_string(root->right, order);
}

bool is_subtree(TreeNode *big, TreeNode *small) {
    string big_order;
    string small_order;

    get_string(big, big_order);
    cout << big_order << endl;
    get_string(small, small_order);
    cout << small_order << endl;
    return (big_order.find(small_order) != std::string::npos);
}
#else // time: O(n + km), space: O(lgn + lgm) 
bool match_tree(TreeNode *tree1, TreeNode *tree2) {
    if (!tree1 && !tree2) return true;
    if (!tree1 || !tree2) return false;
    
    if (tree1->value != tree2->value) {
        return false;
    } else {
        return match_tree(tree1->left, tree2->left) 
            && match_tree(tree1->right, tree2->right);
    }
}

bool is_subtree(TreeNode *big, TreeNode *small) {
    if (!big && !small) return true;
    if (!small) return true;
    if (!big) return false;

    if (big->value == small->value) {
        if (match_tree(big, small)) return true;
    }

    return is_subtree(big->left, small) 
        || is_subtree(big->right, small);
}
#endif

int main(void) {
    TreeNode *tree1 = new TreeNode(1);
    TreeNode *left = tree1->add_left(2);
    TreeNode *right = tree1->add_right(3);

    TreeNode *tree2 = new TreeNode(1);
    left = tree2->add_left(2);

    if (is_subtree(tree1, tree2)) {
        cout << "tree2 is a subtree...[NG]" << endl;
    } else {
        cout << "tree2 is NOT a subtree...[OK]" << endl;
    }

    tree1->left->add_left(4);
    TreeNode *tree3 = new TreeNode(2);
    tree3->add_left(4);

    if (is_subtree(tree1, tree3)) {
        cout << "tree3 is a subtree...[OK]" << endl;
    } else {
        cout << "tree3 is NOT a subtree...[NG]" << endl;
    }

    return 0;
}
