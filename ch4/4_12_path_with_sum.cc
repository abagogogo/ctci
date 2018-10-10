#include "tree.h"
#include <bits/stdc++.h>

using namespace std;

#if 0 // time: O(nlogn)
int count_paths_with_sum(TreeNode *node, int target, int acc) {
    if (!node) return 0;

    int total_path = 0;
    acc += node->value;
    if (acc == target) {
        ++total_path;
    }

    total_path += count_paths_with_sum(node->left, target, acc);
    total_path += count_paths_with_sum(node->right, target, acc);
    return total_path;
}

int count_paths_with_sum(TreeNode *root, int target) {
    if (!root) return 0;

    int from_root = count_paths_with_sum(root, target, 0);
    int from_left = count_paths_with_sum(root->left, target);
    int from_right = count_paths_with_sum(root->right, target);
    return from_root + from_left + from_right;
}

#else // O(n)
void inc_sum2pathcnt(map<int, int> &sum2pathcnt, int key, int delta) {
    auto it = sum2pathcnt.find(key);
    if (it != sum2pathcnt.end()) {
        it->second += delta;
        if (it->second == 0) sum2pathcnt.erase(it);
    } else {
        sum2pathcnt[key] = delta;
    }
}

int count(TreeNode *node, int target, int running_sum, map<int, int> &sum2pathcnt) {
    if (!node) return 0;

    // count paths with sum ending at current node.
    running_sum += node->value;
    int sum = running_sum - target;
    int num_paths = sum2pathcnt[sum];
    printf("DBG: node value=%d, running_sum=%d, sum=%d -> num_paths=%d\n", node->value, running_sum, sum, num_paths);

    // if running sume equals target, then one additional path starts at node.
    if (running_sum == target) {
        ++num_paths;
    }

    // increment sum2pathcnt, recurse, then decrement sum2pathcnt.
    inc_sum2pathcnt(sum2pathcnt, running_sum, 1);
    num_paths += count(node->left, target, running_sum, sum2pathcnt);
    num_paths += count(node->right, target, running_sum, sum2pathcnt);
    inc_sum2pathcnt(sum2pathcnt, running_sum, -1);

    return num_paths;
}

int count_paths_with_sum(TreeNode *root, int target) {
    map<int, int> sum2pathcnt;
    return count(root, target, 0, sum2pathcnt);
}
#endif

int main(void) {
    TreeNode *tree1 = new TreeNode(10);
    TreeNode *left = tree1->add_left(5);
    TreeNode *right = tree1->add_right(-3);
    TreeNode *left_l = left->add_left(3);
    TreeNode *left_r = left->add_right(2);
    left_l->add_left(3);
    left_l->add_right(-2);
    left_r->add_right(1);
    right->add_right(11);
    tree1->print();

    int target = 8;
    int num_paths = count_paths_with_sum(tree1, target);
    if (num_paths == 3) {
        cout << "[OK] tree1 #path with sum=" << target << ": " << num_paths << endl;
    } else {
        cout << "[NG] tree1 #path with sum=" << target << ": " << num_paths << endl;
    }

    return 0;
}
