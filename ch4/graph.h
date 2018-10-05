#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
public:
    Graph(int num_nodes = 10) {
        adj_list.resize(num_nodes);
    }

    int get_node_cnt(void) {
        return adj_list.size();
    }

    vector<int> & get_neighbors(int u) {
        return adj_list[u];
    }

    void add_edge(int u, int v) {
        int m = max(u, v);
        if (m >= adj_list.size()) {
            adj_list.resize(m + 1);
        }
        adj_list[u].push_back(v);
    }

    void print(void) {
        for (int u = 0; u <  adj_list.size(); ++u) {
            for (int v : adj_list[u]) {
                cout << "(" << u << " -> " << v << ")" << endl;
            }
        }
    }

protected:
    vector<vector<int>> adj_list;
};

#endif
