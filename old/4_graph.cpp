#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>

using namespace std;

#define tr(c, it) \
        for(typeof(c.begin())it = c.begin(); it != c.end(); it++)

class Graph {
public:
    Graph(int vert_cnt)
    {
        m_adj.resize(vert_cnt);
        cout << "initial vertext count = " << m_adj.size() << endl;
    }

    void add_edge(int u, int v)
    {
        int m = max(u, v);
        if (m >= m_adj.size()) {
            m_adj.resize(m + 1);
        }
        m_adj[u].push_back(v);
    }

    void show(void)
    {
        int u, v;

        for (u = 0; u < m_adj.size(); u++) {
            tr (m_adj[u], it) {
                v = *it;
                cout << "(" << u << " -> " << v << ")" << endl;
            }
        }
    }

    void dfs(int start);
    void bfs(int start);
    bool has_cycle(void);
    bool has_route(int start, int end);

protected:
    bool has_cycle_r(int start, bool *visited, bool *pred);
    bool has_route(int start, int end, bool *visited);

protected:
    vector< vector<int> > m_adj;
};

void Graph::dfs(int start)
{
    bool *visited = new bool[m_adj.size()]();
    stack<int> to_trav;
    int curr;

    cout << "DFS: start from: " << start << endl;
    to_trav.push(start);

    while (!to_trav.empty()) {
        curr = to_trav.top();
        to_trav.pop();

        //if (!visited[curr]) {
            visited[curr] = true;
            cout << curr << ",";

            tr (m_adj[curr], it) {
                if (!visited[*it]) {
                    to_trav.push(*it);
                }
            }
        //}
    }
    cout << endl;
}

void Graph::bfs(int start)
{
    bool *visited = new bool[m_adj.size()]();
    deque<int> to_trav;
    int curr;

    cout << "BFS: start from " << start << endl;
    to_trav.push_back(start);
    visited[start] = true;

    while (!to_trav.empty()) {
        curr = to_trav.front();
        to_trav.pop_front();
        cout << curr << ", ";

        tr (m_adj[curr], it) {
            if (!visited[*it]) {
                to_trav.push_back(*it);
                visited[*it] = true;
            }
        }
    }
    cout << endl;

    delete [] visited;
}

bool Graph::has_cycle_r(int start, bool *visited, bool *pred)
{
    bool result = false;

    if (!visited[start]) {
        visited[start] = true;
        pred[start] = true;
        
        tr(m_adj[start], it) {
            if (!pred[*it]) {
                result = has_cycle_r(*it, visited, pred);
                cout << "start=" << start << ", *it=" << *it << ", result=" << result << endl;
            } else {
                cout << "start=" << start << ", *it=" << *it << ", found cycel!" << endl;
                result = true;
            }
            if (result) break;
        }
        pred[start] = false;
    }    

    return result;
}

bool Graph::has_cycle(void)
{
    bool *visited = new bool[m_adj.size()]();
    bool *pred = new bool[m_adj.size()]();
    bool  result = false;
    int   start = 0;
    
    for (start = 0; start < m_adj.size(); start++) {
        result = has_cycle_r(start, visited, pred);
        if (result) break;
    }

    delete [] visited;
    delete [] pred;
    return result;
}

bool Graph::has_route(int start, int end, bool *visited)
{
    bool result = false;

    if (!visited[start]) {
        visited[start] = true;

        tr (m_adj[start], it) {
            if (!visited[*it]) {
                if (*it == end) {
                    result = true;
                } else {
                    result = has_route(*it, end, visited);
                }
                if (result) break;
            }
        }
    }

    return result;
}

bool Graph:: has_route(int start, int end)
{
    bool *visited = new bool[m_adj.size()]();
    bool  result = false;

    result = has_route(start, end, visited);

    delete [] visited;
    return result;
}

int main(void)
{
    Graph g1(5);
    Graph g2(5);

    g1.add_edge(0, 1);
    g1.add_edge(1, 2);
    g1.add_edge(1, 4);
    g1.add_edge(2, 0);
    g1.add_edge(2, 3);
    g1.show();

    g1.dfs(0);
    g1.bfs(0);

    if (g1.has_cycle()) {
        cout << "g1 has cycle." << endl;
    } else {
        cout << "[NG] g1 has no cycle!" << endl;
    }

    g2.add_edge(0, 1);
    g2.add_edge(0, 2);
    g2.add_edge(1, 2);
    g2.add_edge(1, 4);
    g2.add_edge(2, 3);
    g2.show();
    if (!g2.has_cycle()) {
        cout << "g2 has no cycle." << endl;
    } else {
        cout << "[NG] g2 has cycle!" << endl;
    }

    if (g1.has_route(0, 3)) {
        cout << "g1 has a route from 0 to 3." << endl;
    } else {
        cout << "[NG] g1 has no route from 0 to 3!" << endl;
    }

    if (!g1.has_route(4, 0)) {
        cout << "g1 has no route from 4 to 0." << endl;
    } else {
        cout << "[NG] g1 has a route from 4 to 0!" << endl;
    }

    return 0;
}
