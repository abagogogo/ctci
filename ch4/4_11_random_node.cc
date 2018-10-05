#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    TreeNode(int _value) {
        //cout << "TreeNode(" << _value << ")" << endl;
        left = right = nullptr;
        value = _value;
        size = 1;
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

    // New API for binary search tree insertion.
    void insert_bst(int _value) {
        if (_value <= value) {
            if (!left) {
                add_left(_value);
            } else {
                left->insert_bst(_value);
            }
        } else {
            if(!right) {
                add_right(_value);
            } else {
                right->insert_bst(_value);
            }
        }
        ++size;
    }

    // New API for binary search tree insertion.
    TreeNode *find_bst(int _value) {
        if (_value == value) {
            return this;
        } else if (_value <= value) {
            if (left) return left->find_bst(_value);
        } else {
            if (right) return right->find_bst(_value);
        }
        return nullptr;
    }

    // New API for binary search tree to get ith-node.
    TreeNode *get_node(int ith) {
        // CAREFUL! size is size of the subtree!
        // That's why we are using left_size here.
        int left_size = (left ? left->size : 0);

        if (ith < left_size) {
            return left->get_node(ith);
        } else if (ith == left_size) {
            return this;
        } else {
            // skipping over left_size + 1 nodes, so substract them.
            return right->get_node(ith - (left_size + 1));
        }
    }

    TreeNode *left, *right;
    int value;
    int size; // New member to keep the size of this subtree.
};

struct Bst {
    Bst(void) {
        root = nullptr;
    }

    void insert(int value) {
        if (!root) {
            root = new TreeNode(value);
        } else {
            root->insert_bst(value);
        }
    }

    TreeNode *find(int value) {
        if (!root) return nullptr;
        return root->find_bst(value);
    }

    // TODO: delete a node.

    TreeNode *get_rand_node(void) {
        if (!root) return nullptr;

        int ith = std::rand() % size();
        return root->get_node(ith);
    }

    int size(void) {
        return (root ? root->size : 0);
    }

    int print(void) {
        if (root) root->print();
    }

    TreeNode *root;
};


int main(void) {
    std::srand(std::time(0));
    Bst tree1;
    tree1.insert(20);
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(3);
    tree1.insert(7);
    tree1.insert(15);
    tree1.insert(17);
    tree1.insert(30);
    tree1.insert(35);
    tree1.print();

    TreeNode *node;
    for (int i = 0; i < 10; ++i ) {
        node =  tree1.get_rand_node();
        cout << "[" << i << "] rand = " << (node ? to_string(node->value) : "null") << endl;
    }

    return 0;
}
