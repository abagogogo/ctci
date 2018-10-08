#include "graph.h"

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#if 0 // DFS
bool has_route(Graph &g, int start, int end, vector<bool> &visited) {
    visited[start] = true;
    if (start == end) return true;

    vector<int> list = g.get_neighbors(start);
    for (int next : list) {
        if (!visited[next]) {
            if (has_route(g, next, end, visited)) 
                return true;
        }
    }
    return false;
}

bool has_route(Graph &g, int start, int end) {
    vector<bool> visited(g.get_node_cnt(), false);
    return has_route(g, start, end, visited);
}
#else // BFS

bool has_route(Graph &g, int start, int end) {
    vector<bool> mark(g.get_node_cnt(), false);
    deque<int> q;

    mark[start] = true;
    q.push_back(start);
    
    while (!q.empty()) {
        int curr = q.front(); q.pop_front();
        if (curr == end) return true;

        vector<int> list = g.get_neighbors(curr);            
        for (int next : list) {
            if (!mark[next]) {
                mark[next] = true;
                q.push_back(next);
            }
        }
    }
    return false;
}
#endif

int main(void) {
    Graph g1;

    g1.add_edge(0, 1);
    g1.add_edge(0, 2);
    g1.add_edge(1, 4);
    g1.add_edge(2, 3);
    g1.add_edge(4, 0);
    g1.add_edge(1, 0);
    g1.print();

    cout << "from 0 to 3: " << (has_route(g1, 0, 3) ? "TRUE" : "FALSE") << endl;
    cout << "from 3 to 4: " << (has_route(g1, 3, 4) ? "TRUE" : "FALSE") << endl;

    return 0;
}
