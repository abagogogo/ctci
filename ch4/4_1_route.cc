#include "graph.h"

#include <iostream>
#include <vector>

using namespace std;

bool has_route(Graph &g, int start, int end, vector<bool> &visited, vector<bool> &predece) {
    vector<int> list = g.get_neighbors(start);
    for (int next : list) {
        if (next == end) return true;
        if (visited[next]) continue;
        visited[next] = true;
        if (has_route(g, next, end, visited, predece)) return true;
    }
    return false;
}

bool has_route(Graph &g, int start, int end) {
    vector<bool> visited(g.get_node_cnt(), false);
    vector<bool> predece(g.get_node_cnt(), false);

    return has_route(g, start, end, visited, predece);
}

int main(void) {
    Graph g1;

    g1.add_edge(0, 1);
    g1.add_edge(0, 2);
    g1.add_edge(1, 4);
    g1.add_edge(2, 3);
    g1.print();

    cout << "from 0 to 3: " << (has_route(g1, 0, 3) ? "TRUE" : "FALSE") << endl;
    cout << "from 3 to 4: " << (has_route(g1, 3, 4) ? "TRUE" : "FALSE") << endl;

    return 0;
}
