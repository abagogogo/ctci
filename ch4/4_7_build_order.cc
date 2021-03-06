#include <bits/stdc++.h>

using namespace std;

enum SEARCH_STATE {
    BLANK,
    VISITING,
    COMPLETED,
};

class Project {
protected:
    vector<Project*> neighbors;
    map<string, Project*> dict;
    string name;
    int depend;

public:
    SEARCH_STATE state;

public:
    Project(const string &_name) {
        depend = 0;
        name = _name;
        state = BLANK;
    }

    void add_neighbor(Project *node) {
        if (dict.find(node->get_name()) == dict.end()) {
            neighbors.push_back(node);
            dict[node->get_name()] = node;
            node->inc_depend();
        }
    }

    const string &get_name(void) {
        return name;
    }

    int get_depend(void) {
        return depend;
    }

    void inc_depend(void) {
        ++depend;
    }

    void dec_depend(void) {
        --depend;
    }

    vector<Project *> get_neighbors(void) {
        return neighbors;
    }
};

class Graph {
protected:
    vector<Project*> nodes;
    map<string, Project*> dict;

public:
    Project *get_node(const string &name) {
        if (dict.find(name) == dict.end()) {
            Project *p = new Project(name);
            nodes.push_back(p);
            dict[name] = p;
        }
        return dict[name];
    }

    Project *add_node(const string &name) {
        return get_node(name);
    }

    void add_edge(const string &start, const string &end) {
        Project *s = get_node(start);
        Project *e = get_node(end);
        s->add_neighbor(e);
    }

    vector<Project*> &get_nodes(void) {
        return nodes;
    }
};

#if 1 // Topological sort
void add_non_depend(vector<Project *> &order, vector<Project *> &projects) {
    for (auto p : projects) {
        if (p->get_depend() == 0) {
            order.push_back(p);
        }
    }
}

bool order_projects(vector<Project *> &order, vector<Project *> &projects) {
    int to_process = 0;

    add_non_depend(order, projects);
    while (to_process < order.size()) {
        Project *curr = order[to_process];
        if (!curr) return false;

        vector<Project *> neighbors = curr->get_neighbors();
        for (auto next : neighbors) {
            next->dec_depend();
        }
        add_non_depend(order, neighbors);
        ++to_process;
    }
    return true;
}
#else // DFS
bool do_dfs(vector<Project *> &order, Project *proj) {
    if (proj->state == VISITING) return false; // cycle exists.
    if (proj->state == COMPLETED) return true;

    proj->state = VISITING;
    auto lists = proj->get_neighbors();
    for (auto next : lists) {
        if (!do_dfs(order, next)) return false;
    }
    proj->state = COMPLETED;
    order.push_back(proj);
    return true;
}

bool order_projects(vector<Project *> &order, vector<Project *> &projects) {
    for (auto proj : projects) {
        if (!do_dfs(order, proj)) {
            return false; // cycle exists, so, the build order isn't complete.
        }
    }
    std::reverse(order.begin(), order.end());
    return true;
}
#endif

void find_build_order(vector<Project *> &order, vector<string> projects, vector<pair<string, string>> dependencies) {
    Graph *g = new Graph();

    // build graph.
    for (auto name : projects) {
        g->add_node(name);
    }

    for (auto dep : dependencies) {
        g->add_edge(dep.first, dep.second);
    }

    order_projects(order, g->get_nodes());
}

int main(void) {
    vector<string> proj_names = {
        "a", "b", "c", "d", "e", "f", "g"};
    vector<pair<string, string>> proj_deps = {
        {"d", "g"},
        {"f", "c"},
        {"f", "a"},
        {"f", "b"},
        {"c", "a"},
        {"b", "a"},
        {"b", "e"}};

    vector<Project *> order;
    find_build_order(order, proj_names, proj_deps);
    for (auto p : order) {
        cout << p->get_name() << " -> ";
    }
    cout << endl;

    return 0;
}

