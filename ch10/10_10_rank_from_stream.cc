#include <bits/stdc++.h>

using namespace std;

struct RankNode {
    int data;
    int left_size;
    RankNode *left;
    RankNode *right;

    RankNode(void) {
        data = 0;
        left_size = 0;
        left = right = nullptr;
    }

    RankNode(int d) {
        RankNode();
        data = d;
    }

    void insert(int d) {
        if (d <= data) {
            if (left) left->insert(d);
            else left = new RankNode(d);
            left_size++;
        } else {
            if (right) right->insert(d);
            else right = new RankNode(d);
        }
    }

    int get_rank(int d) {
        if (d == data) return left_size;
        else if (d < data) {
            if (left) return left->get_rank(d);
            else return -1;
        } else {
            int right_rank = right ? right->get_rank(d) : -1;
            if (right_rank == -1) return -1;
            else return left_size + 1 + right_rank;
        }
    }
};

RankNode *g_root = nullptr;

void track(int number) {
    if (g_root == nullptr) {
        g_root = new RankNode(number);
    } else {
        g_root->insert(number);
    }
}

int get_rank_of_number(int number) {
    if (!g_root) return -1;
    else return g_root->get_rank(number);
}

int main(void) {

    vector<int> stream = {5, 1, 4, 4, 5, 9, 7 ,13, 3};

    for (auto num : stream) track(num);

    for (auto num : {1, 3, 4}) {
        cout << "rank of " << num << " = " << get_rank_of_number(num) << endl;
    }
    return 0;
}
