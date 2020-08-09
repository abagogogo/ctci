#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>

using namespace std;

#define tr(c, it) for(typeof(c.begin())it = c.begin(); it != c.end(); it++)

class ListNode {
public:
    ListNode(int _data)
    {
        data = _data;
        next = NULL;
    }
    ~ListNode(void)
    {
        if (next) delete next;
    }

public:
    ListNode *next;
    int       data;
};

class LinkList {
public:
    LinkList(void)
    {
        head = tail = NULL;
    }

    bool empty(void) {return (head == tail);}

    void insert_tail(ListNode *node)
    {
        node->next = NULL;
        if (tail != NULL) {
            tail->next = node;
            tail = node;
        } else {
            head = tail = node;
        }
    }

    ListNode *remove_head(void)
    {
        ListNode *node = NULL;

        if (head != NULL) {
            node = head;
            node->next = NULL;
            if (head != tail) {
                head = head->next;
            } else {
                head = tail = NULL;
            }
        }
        return node;
    }

public:
    ListNode *head;
    ListNode *tail;
};

class TreeNode {
public:
    TreeNode(int _data, TreeNode *_parent)
    {
        parent = _parent;
        data = _data;

        left = right = NULL;
    }
    ~TreeNode(void)
    {
        if (left) delete left;
        if (right) delete right;
    }

    void inorder(void) { inorder(this); }
    void inorder(TreeNode *node);
    vector<LinkList> *tolists(void);
    static TreeNode *in_succ(TreeNode *node);
    static TreeNode *left_most_child(TreeNode *node);
    static TreeNode *common_ancestor(TreeNode *root, TreeNode *p, TreeNode *q);
    static bool covers(TreeNode *root, TreeNode *p);
    static bool is_subtree(TreeNode *t1, TreeNode *t2);
    static bool is_matched(TreeNode *t1, TreeNode *t2);
    static void find_sum(TreeNode *node, int sum, vector<int> *path) ;
    static void print_path(vector<int> *path, int start);

protected:

public:
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    int       data;
};

void TreeNode::inorder(TreeNode *node)
{
    if (node) {
        inorder(node->left);
        cout << node->data << ", ";
        inorder(node->right);
    }
}

vector<LinkList> *TreeNode::tolists(void)
{
    vector<LinkList>   *lists = new vector<LinkList>;
    deque< pair<TreeNode *, int> > queue;
    TreeNode           *curr;
    int                 last_level = -1;
    int                 level;

    queue.push_back(pair<TreeNode *, int>(this, 0));
    while (!queue.empty()) {
        curr = queue.front().first;
        level = queue.front().second;
        queue.pop_front();

        if (level != last_level) {
            lists->resize(level + 1);
            last_level = level;
        }

        (*lists)[level].insert_tail(new ListNode(curr->data));

        if (curr->left) {
            queue.push_back(pair<TreeNode *, int>(curr->left, level + 1));
        }
        if (curr->right) {
            queue.push_back(pair<TreeNode *, int>(curr->right, level + 1));
        }
    }
    return lists;
}

TreeNode *TreeNode::in_succ(TreeNode *node)
{
    if (node) {
        if (node->right || !node->parent) {
            return left_most_child(node->right);
        } else {
            TreeNode *p;
            while ((p = node->parent) != NULL) { 
                if (p->left == node) {
                    break;
                }
                node = p;
            }
            return p;
        }
    }
    return NULL;
}

TreeNode *TreeNode::left_most_child(TreeNode *node)
{
    if (node) {
        while (node->left) {
            node = node->left;
        }
    }
    return node;
}

TreeNode *TreeNode::common_ancestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (covers(root->left, p) && covers(root->left, q)) {
        return common_ancestor(root->left, p, q);
    } else if (covers(root->right, p) && covers(root->right, q)) {
        return common_ancestor(root->right, p, q);
    } else {
        return root;
    }
}

bool TreeNode::covers(TreeNode *root, TreeNode *p)
{
    if (!root) return false;
    if (root == p)  return true;
    return (covers(root->left, p) || covers(root->right, p));
}

bool TreeNode::is_subtree(TreeNode *t1, TreeNode *t2)
{
    if (t2 == NULL) return true;
    if (t1 == NULL) return false;
    if (t1->data == t2->data) {
        if (is_matched(t1, t2)) {
            return true;
        }
    } 
    return (is_subtree(t1->left, t2) || is_subtree(t1->right, t2));
}

bool TreeNode::is_matched(TreeNode *t1, TreeNode *t2)
{
    if (t1 == NULL && t2 == NULL) {
        return true;
    }
    //if (t1 == NULL || t2 == NULL) {
    if (t2 == NULL) {
        return true;
    }
    if (t1->data == t2->data) {
        return (is_matched(t1->left, t2->left) && is_matched(t1->right, t2->right));
    }
    return false;
}

void TreeNode::find_sum(TreeNode *node, int sum, vector<int> *path) 
{
    if (node == NULL) return;

    path->push_back(node->data);
    int tmp = sum;
    for (int i = path->size() - 1; i >= 0; i--) {
        tmp -= path->at(i);
        if (0 == tmp) {
            cout << "Found sum=" << sum << endl;
            print_path(path, i);
        }
    }

    find_sum(node->left, sum, path);
    find_sum(node->right, sum, path);
    path->pop_back();
}

void TreeNode::print_path(vector<int> *path, int start)
{
    int idx;

    cout << "Path: ";
    for (idx = start; idx < path->size(); idx++) {
        cout << path->at(idx) << " ";
    }
    cout << endl;
}

int main(void)
{
    TreeNode root1(3, NULL);

    root1.left = new TreeNode(1, &root1);
    root1.right = new TreeNode(5, &root1);
    root1.left->left = new TreeNode(0, (root1.left));
    root1.left->right = new TreeNode(2, (root1.left));
    root1.right->left = new TreeNode(4, (root1.right));

    cout << "root1 inorder..." << endl;
    root1.inorder();
    cout << endl;

    vector<LinkList> *lists = root1.tolists();
    int level = 0;
    ListNode *curr, *next;
    tr ((*lists), it) {
        cout << "level " << level << "link list:" << &(*it) << endl;
        curr = it->head;
        while (curr != NULL) {
            next = curr->next;
            cout << " " << curr->data;
            curr = next;
        }
        cout << endl;
        
        level++;
    }
    delete lists;


    TreeNode *succ = TreeNode::in_succ(&root1);
    if (succ) {
        cout << "root1 in successor: " << succ->data << endl;
    } else {
        cout << "[NG] root1 has no successor!" << endl;
    }
    TreeNode *node = root1.left->left;
    succ = TreeNode::in_succ(node);
    if (succ) {
        cout << node->data << " in successor: " << succ->data << endl;
    } else {
        cout << node->data << " has no successor: " << endl;
    }
    node = root1.left->right;
    succ = TreeNode::in_succ(node);
    if (succ) {
        cout << node->data << " in successor: " << succ->data << endl;
    } else {
        cout << node->data << " has no successor: " << endl;
    }
    node = root1.left;
    succ = TreeNode::in_succ(node);
    if (succ) {
        cout << node->data << " in successor: " << succ->data << endl;
    } else {
        cout << node->data << " has no successor: " << endl;
    }

    TreeNode *p = root1.left->left;
    TreeNode *q = root1.left->right;
    TreeNode *ancestor = TreeNode::common_ancestor(&root1, p, q);
    cout << "common ancestor of " << p->data << " and " << q->data << "=" << ancestor->data << endl;

    q = root1.right->left;
    ancestor = TreeNode::common_ancestor(&root1, p, q);
    cout << "common ancestor of " << p->data << " and " << q->data << "=" << ancestor->data << endl;

    TreeNode root2(1, NULL);
    root2.left = new TreeNode(0, &root2);
    //root2.right = new TreeNode(2, &root2);
    if (TreeNode::is_subtree(&root1, &root2)) {
        cout << "root2 is a subtree of root1." << endl;
    } else {
        cout << "[NG] root2 is NOT a subtree of root1." << endl;
    }

    vector<int> tmp_path;
    TreeNode::find_sum(&root1, 3, &tmp_path);

    return 0;
}
