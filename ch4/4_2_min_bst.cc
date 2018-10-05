#include "tree.h"

#include <iostream>
#include <vector>

using namespace std;

TreeNode *create_bst(vector<int> &data, int from, int to) {
    int mid = (from + to) / 2;
    TreeNode *node = new TreeNode(data[mid]);
    if (from < mid) node->left = create_bst(data, from, mid - 1);
    if (mid < to) node->right = create_bst(data, mid + 1, to);
    return node;
}

TreeNode *create_bst(vector<int> &data) {
    return create_bst(data, 0, data.size() - 1);
}

int main(void) {
    vector<int> data = {0, 1, 2, 3, 4, 5, 6, 7};
    TreeNode *tree = create_bst(data);
    tree->print();
    return 0;
}
