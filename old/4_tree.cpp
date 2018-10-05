#include <iostream>
#include <algorithm>

using namespace std;

class TreeNode {
public:
    TreeNode(int _id)
    {
        left = right = NULL;
        id = _id;
    }
    ~TreeNode(void)
    {
        if (left) delete left;
        if (right) delete right;
    }

    void preorder(void) { preorder(this); }
    void preorder(TreeNode *node);
    int get_depth(void) { return get_depth(this); }
    int get_depth(TreeNode *node);
    int get_min_depth(TreeNode *node);
    bool is_balanced(void);

public:
    TreeNode *left;
    TreeNode *right;
    int       id;
};

void TreeNode::preorder(TreeNode *node)
{
    if (node) {
        cout << node->id << ", ";
        preorder(node->left);
        preorder(node->right);
    }
}

int TreeNode::get_depth(TreeNode *node)
{
    if (node) {
        return (max(get_depth(node->left), get_depth(node->right)) + 1);
    } else {
        return 0;
    }
}

int TreeNode::get_min_depth(TreeNode *node)
{
    if (node) {
        return (min(get_min_depth(node->left), get_min_depth(node->right)) + 1);
    } else {
        return 0;
    }
}

bool TreeNode::is_balanced(void)
{
    int max_depth = get_depth(this);
    int min_depth = get_min_depth(this);

    return ((max_depth - min_depth) <= 1);
}

int main(void)
{
    TreeNode root1(0);

    root1.left = new TreeNode(1);
    root1.right = new TreeNode(4);
    root1.left->left = new TreeNode(2);
    root1.left->right = new TreeNode(3);
    root1.right->left = new TreeNode(5);

    cout << "root1 preorder..." << endl;
    root1.preorder();
    cout << endl;

    cout << "root1 depth = " << root1.get_depth() << endl;

    if (root1.is_balanced()) {
        cout << "root1 is balanced" << endl;
    } else {
        cout << "[NG] root1 is not balanced" << endl;
    }
    return 0;
}
