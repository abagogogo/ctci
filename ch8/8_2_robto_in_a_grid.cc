#include <bits/stdc++.h>

using namespace std;

// memoization on failed point reduce time complexity from O(2^r+c) to O(rc).
bool get_path(vector<vector<bool>> &maze, int row, int col, vector<pair<int, int>> &path, set<pair<int, int>> &fails) {
    // if out of bounds or not available */
    if (col < 0 || row < 0 || !maze[row][col]) return false;

    pair<int, int> point = {row, col};
    // if we've already visited this cell.
    if (fails.find(point) != fails.end()) return false;

    bool is_at_origin = ((row ==0) && (col == 0));

    if (is_at_origin || get_path(maze, row, col - 1, path, fails) 
        || get_path(maze, row - 1, col, path, fails)) {
        path.push_back(point);
        return true;
    }
    
    cout << "[DBG] (" << point.first << ", " << point.second << ") is added to fails" << endl;
    fails.insert(point);
    return false;
}

bool get_path(vector<vector<bool>> &maze, vector<pair<int, int>> &path) {
    set<pair<int, int>> fails;

    if (maze.empty()) return false;
    bool result = get_path(maze, maze.size() - 1, maze[0].size() - 1, path, fails);
    cout << "[DBG] fails.size: " << fails.size() << endl;
    return result;
}

int main(void) {
    vector<vector<bool>> maze = {{true, true, true},
                                 {true, false, true},
                                 {false, true, true}};
    vector<pair<int, int>> path;

    if (get_path(maze, path)) {
        cout << "[OK] found path: " << endl;
        for (auto pt : path) cout << "(" << pt.first << ", " << pt.second << ") -> ";
        cout << endl;
    } else {
        cout << "[NG] No path found." << endl;
    }
    return 0;
}
