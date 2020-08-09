#include <iostream>
#include <vector>

using namespace std;

#define tr(c, it) for(typeof(c.begin())it = c.begin(); it != c.end(); it++)

class Vertex;

class Edge {
public:
    Edge(Vertex *startVertex, Vertex *endVertex, int weightVal)
    {
        start = startVertex;
        end = endVertex;
        weight = weightVal;
    }

    Vertex *start;
    Vertex *end;
    int   weight;
};

class Vertex {
public:
    Vertex(int id_value)
    {
        id = id_value;
    }

    int id;
    vector<Edge *>edges;
};

class Graph {
public:
    ~Graph(void)
    {
        // TODO
    }

    vector<Vertex *> &get_adj_list(void)
    {
        return adj_list;
    }

protected:
    vector<Vertex *> adj_list;
};

void const_graph(Graph &graph)
{
    vector<Vertex *> &adj = graph.get_adj_list();

    for (int idx = 0; idx <= 5; idx++) {
        adj.push_back(new Vertex(idx));
    }
    
    adj[0]->edges.push_back(new Edge(adj[0], adj[1], 0));
    adj[0]->edges.push_back(new Edge(adj[0], adj[2], 0));

    adj[1]->edges.push_back(new Edge(adj[1], adj[0], 0));
    adj[1]->edges.push_back(new Edge(adj[1], adj[2], 0));
    adj[1]->edges.push_back(new Edge(adj[1], adj[4], 0));

    adj[2]->edges.push_back(new Edge(adj[2], adj[0], 0));
    adj[2]->edges.push_back(new Edge(adj[2], adj[1], 0));
    adj[2]->edges.push_back(new Edge(adj[2], adj[3], 0));

    adj[3]->edges.push_back(new Edge(adj[3], adj[2], 0));

    adj[4]->edges.push_back(new Edge(adj[4], adj[1], 0));
}

void show_graph(Graph &g)
{
    vector<Vertex *> &adj = g.get_adj_list();
    tr (adj, it) {
        cout << "vertext: " << (*it)->id << endl;
        tr ((*it)->edges, edge) {
            cout << "   (" << (*edge)->start->id << ", " << (*edge)->end->id << ")" << endl;
        }
    }
}

void dfs(Graph &g, Vertex *start)
{
    vector<Vertex *> &adj = g.get_adj_list();
    vector<bool> visited(adj.size(), false);
    vector<Vertex *> stack;
    Vertex *curr;
    Vertex *neighbor;

#if 0
    for (int idx = 0; idx < visited.size(); idx++) {
        cout << "visited[" << idx << "] = " << visited[idx] << endl;
    }
#endif

    cout << "DFS start = " << start->id << endl;
    stack.push_back(start);
    while (!stack.empty()) {
        curr = stack.back(); 
        stack.pop_back();
        
        if (!visited[curr->id]) {
            visited[curr->id] = true;
            cout << "visted vertex " << curr->id << endl;

            tr (curr->edges, edge) {
                neighbor = (*edge)->end;
                if (visited[neighbor->id] == false) {
                    stack.push_back(neighbor);
                }
            }
        }
    }
}

void dfs_rx(Graph &g, Vertex *curr, vector<bool> &visited) 
{
    Vertex *neighbor;

    if (visited[curr->id] == false) {
        visited[curr->id] = true;
        cout << "[R] visted vertex " << curr->id << endl;

        tr (curr->edges, edge) {
            neighbor = (*edge)->end;
            if (visited[neighbor->id] == false) {
                dfs_rx(g, neighbor, visited);
            }
        }
    }
}

void dfs_recur(Graph &g, Vertex *start)
{
    vector<Vertex *> &adj = g.get_adj_list();
    vector<bool> visited(adj.size(), false);
    Vertex *neighbor;

    cout << "DFS start = " << start->id << endl;
    visited[start->id] = true;
    cout << "[R] visted vertex " << start->id << endl;

    tr (start->edges, edge) {
        neighbor = (*edge)->end;
        if (visited[neighbor->id] == false) {
            dfs_rx(g, neighbor, visited);
        }
    }
}

void bfs(Graph &g, Vertex *start)
{
    vector<Vertex *> &adj = g.get_adj_list();
    vector<bool> visited(adj.size(), false);
    vector<Vertex *> queue;
    Vertex *curr;
    Vertex *neighbor;

    cout << "BFS start = " << start->id << endl;
    queue.push_back(start);
    while (!queue.empty()) {
        curr = queue[0];
        queue.erase(queue.begin());

        if (!visited[curr->id]) {
            visited[curr->id] = true;
            cout << "visted vertex " << curr->id << endl;

            tr (curr->edges, edge) {
                neighbor = (*edge)->end;
                if (!visited[neighbor->id]) {
                    queue.push_back(neighbor);
                }
            }
        }
    }
}

bool search_route(Graph &g, Vertex *start, Vertex *end)
{
    vector<Vertex *> &adj = g.get_adj_list();
    vector<bool> visited(adj.size(), false);
    vector<Vertex *> stack;
    Vertex *curr, *next;

    stack.push_back(start);
    while (!stack.empty()) {
        curr = stack.back();
        stack.pop_back();
        
        if (!visited[curr->id]) {
            visited[curr->id] = true;

            tr (curr->edges, edge) {
                next = (*edge)->end;
                if (!visited[next->id]) {
                    if (next == end) {
                        cout << "route exits from " << start->id << " to " << end->id << endl;
                        return true;
                    } else {
                        stack.push_back(next);
                    }
                }
            }
        }
    }

    cout << "route doesn't exit from " << start->id << " to " << end->id << endl;
    return false;
}

// ref: http://www.geeksforgeeks.org/detect-cycle-in-a-graph/
bool has_cycle_rec(Graph &g, Vertex *curr, vector<bool> &visited, vector<bool> &in_path)
{
    Vertex *next;

    if (!visited[curr->id]) {
        visited[curr->id] = true;
        in_path[curr->id] = true; 

        tr (curr->edges, edge) {
            next = (*edge)->end;

            if (!in_path[curr->id] &&
                 has_cycle_rec(g, next, visited, in_path)) {
                cout << "found a cycle, case 1: curr=" << curr->id << ", next=" << next->id << endl;
                return true;
            } else {
                cout << "found a cycle, case 2: curr=" << curr->id << ", next=" << next->id << endl;
                return true;
            }
        }

    }
    in_path[curr->id] = false; 
    return false;
}

bool has_cycle(Graph &g)
{
    vector<Vertex *> &adj = g.get_adj_list();
    vector<bool> visited(adj.size(), false);
    vector<bool> in_path(adj.size(), false);

    tr (adj, vertex) {
        if (has_cycle_rec(g, *vertex, visited, in_path)) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    Graph g;
    Vertex *start;

    const_graph(g);
    show_graph(g);

    start = g.get_adj_list()[0];
    dfs(g, start);
    dfs_recur(g, start);
    bfs(g, start);

    search_route(g, g.get_adj_list()[4], g.get_adj_list()[3]);
    search_route(g, g.get_adj_list()[3], g.get_adj_list()[5]);

    has_cycle(g);
    return 0;
}

