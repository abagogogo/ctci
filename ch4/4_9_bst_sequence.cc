#include "tree.h"
#include <bits/stdc++.h>

using namespace std;

void print_sequences(const vector<deque<int>> &sequences, const string &msg) {
    cout << msg << endl;
    for (auto seq : sequences) {
        for (auto n : seq) {
            cout << n << ", ";
        }
        cout << endl;
    }
}

deque<int> join(const deque<int> &first, const deque<int> &second) {
    deque<int> ret;

    for (auto n : first) ret.push_back(n);
    for (auto n : second) ret.push_back(n);
    return ret;
}

void weave(deque<int> &first, deque<int> &second, deque<int> &prefix, vector<deque<int>> &sequences) {
    if (first.empty() || second.empty()) {
        sequences.push_back(
                    join(
                        join(prefix, first), 
                        second));
        return;
    }

    int tmp = first.front();
    first.pop_front();
    prefix.push_back(tmp);
    weave(first, second, prefix, sequences);
    prefix.pop_back();
    first.push_front(tmp);

    tmp = second.front();
    second.pop_front();
    prefix.push_back(tmp);
    weave(first, second, prefix, sequences);
    prefix.pop_back();
    second.push_front(tmp);
}

void get_all_seq(TreeNode *tree, vector<deque<int>> &sequences) {
    if (!tree) {
        sequences.push_back({}); // add an empty sequence.
        return;
    }

    vector<deque<int>> left_sequences;
    vector<deque<int>> right_sequences;
    deque<int> prefix;

    prefix.push_back(tree->value);
    get_all_seq(tree->left, left_sequences);
    get_all_seq(tree->right, right_sequences);

    for (auto left : left_sequences) {
        for (auto right : right_sequences) {
            weave(left, right, prefix, sequences);
        }
    }
}

int main(void) {
    vector<deque<int>> sequences;

    TreeNode *tree1 = new TreeNode(2);
    tree1->add_left(1);
    tree1->add_right(3);
    sequences.clear();
    get_all_seq(tree1, sequences);
    print_sequences(sequences, "tree1 sequences:");

    return 0;
}
