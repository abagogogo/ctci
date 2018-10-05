#include <bits/stdc++.h>

using namespace std;

enum Color {
    BLACK,
    WHITE,
    RED,
    YELLO,
    GREEN
};

#if 1 // DFS
bool paint_fill(vector<vector<Color>> &screen, int row, int col, Color old_color, Color new_color) {
    if (row < 0 || row >= screen.size() || col < 0 || col >= screen[0].size()) return false;

    if (screen[row][col] == old_color) {
        screen[row][col] = new_color;
        paint_fill(screen, row-1, col, old_color, new_color); // up
        paint_fill(screen, row+1, col, old_color, new_color); // down 
        paint_fill(screen, row, col-1, old_color, new_color); // left
        paint_fill(screen, row, col+1, old_color, new_color); // right
    }
    return true;
}

bool paint_fill(vector<vector<Color>> &screen, int row, int col, Color new_color) {
    if (screen[row][col] == new_color) return false;
    return paint_fill(screen, row, col, screen[row][col], new_color);
}
#else // BFS
bool paint_fill(vector<vector<Color>> &screen, int row, int col, Color new_color) {
    if (screen[row][col] == new_color) return false;

    deque<pair<int, int>> q; 
    Color old_color = screen[row][col];

    screen[row][col] = new_color;
    q.push_back({row, col});

    while(!q.empty()) {
        pair<int, int> loc = q.front(); q.pop_front();
        int row = loc.first;
        int col = loc.second;
        
        if (row - 1 >= 0 && screen[row - 1][col] == old_color) {
            screen[row - 1][col] = new_color;
            q.push_back({row - 1, col});
        }
        if (row + 1 < screen.size() && screen[row + 1][col] == old_color) {
            screen[row + 1][col] = new_color;
            q.push_back({row + 1, col});
        }
        if (col - 1 >= 0 && screen[row][col - 1] == old_color) {
            screen[row][col - 1] = new_color;
            q.push_back({row, col - 1});
        }
        if (col + 1 < screen[row].size() && screen[row][col + 1] == old_color) {
            screen[row][col + 1] = new_color;
            q.push_back({row, col + 1});
        }
    }
    return true;
}
#endif

void print_screen(const vector<vector<Color>> &screen, const string &msg) {
    cout << msg << endl;
    for (auto row : screen) {
        for (auto pixel : row) {
            cout << pixel << ", ";
        }
        cout << endl;
    }
}

int main(void) {
    vector<vector<Color>> screen = {{BLACK, BLACK, BLACK, BLACK, BLACK}, 
                                    {BLACK, BLACK, BLACK, BLACK, BLACK}, 
                                    {BLACK, WHITE, BLACK, WHITE, BLACK}, 
                                    {BLACK, WHITE, BLACK, WHITE, BLACK}, 
                                    {BLACK, WHITE, WHITE, WHITE, BLACK}};

    print_screen(screen, "before");
    paint_fill(screen, 3, 1, GREEN);
    print_screen(screen, "after");
    return 0;
}
