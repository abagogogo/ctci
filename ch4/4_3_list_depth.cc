#include "tree.h"

#include <iostream>
#include <vector>

using namespace std;

#if 0 // for DFS/preorder
void create_depth_lists(vector<vector<TreeNode *>> &lists, TreeNode *node, int depth) {
    if (!node) return;
    if (depth >= lists.size()) {
        vector<TreeNode *> *new_list = new vector<TreeNode *>;
        lists.push_back(*new_list);
    }
    lists[depth].push_back(node);
    create_depth_lists(lists, node->left, depth + 1);
    create_depth_lists(lists, node->right, depth + 1);
}

void create_depth_lists(vector<vector<TreeNode *>> &lists, TreeNode *tree) {
    if (!tree) return;
    create_depth_lists(lists, tree, 0);
}

#else // for BFS
void create_depth_lists(vector<vector<TreeNode *>> &lists, TreeNode *tree) {
    if (!tree) return;

    vector<TreeNode *> *new_list = new vector<TreeNode *>;
    new_list->push_back(tree);

    while(!new_list->empty()) {
        lists.push_back(*new_list);
        new_list = new vector<TreeNode *>;

        for (auto node : lists.back()) {
            if (node->left) new_list->push_back(node->left);
            if (node->right) new_list->push_back(node->right);
        }
    }
}
#endif

void print_lists(vector<vector<TreeNode *>> &lists) {
    int depth = 0;

    for (auto list : lists) {
        cout << "depth = " << depth++ << ":" << endl;
        for (auto node : list) {
            cout << node->value << ", ";
        }
        cout << endl;
    }
}

int main(void) {
    TreeNode *tree1 = new TreeNode(0);
    TreeNode *left = tree1->add_left(1);
    TreeNode *right = tree1->add_right(2);
    left->add_left(3);
    left->add_right(4);
    right->add_left(5);
    tree1->print();

    vector<vector<TreeNode *>> lists;
    create_depth_lists(lists, tree1);
    print_lists(lists);

    return 0;
}
