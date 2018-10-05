#ifndef _TREE_H
#define _TREE_H

#include <iostream>

using namespace std;

struct TreeNode {
    TreeNode(int _value) {
        //cout << "TreeNode(" << _value << ")" << endl;
        left = right = nullptr;
        value = _value;
    }

    virtual TreeNode *add_left(int _value) {
        left = new TreeNode(_value);
        return left;
    }

    virtual TreeNode *add_right(int _value) {
        right = new TreeNode(_value);
        return right;
    }

    void print(void) {
        inorder(this);
        cout << endl;
    }

    static void inorder(TreeNode *node) {
        if (!node) return;
        inorder(node->left);
        cout << node->value << ", ";
        inorder(node->right);
    }

    TreeNode *left, *right;
    int value;
};

struct PTreeNode {
    PTreeNode(int _value) {
        //cout << "PTreeNode(" << _value << ")" << endl;
        parent = nullptr;
        left = right = nullptr;
        value = _value;
    }

    PTreeNode *add_left(int _value) {
        left = new PTreeNode(_value);
        ((PTreeNode *)left)->parent = this;
        return (PTreeNode *)left;
    }

    PTreeNode *add_right(int _value) {
        right = new PTreeNode(_value);
        ((PTreeNode *)right)->parent = this;
        return (PTreeNode *)right;
    }

    PTreeNode *parent;
    PTreeNode *left, *right;
    int value;
};

#endif
