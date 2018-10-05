#include <bits/stdc++.h>

using namespace std;

int GRID_SIZE = 8;

bool check_valid(vector<int> &columns, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (columns[i] == col 
         || abs(columns[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void place_queens(int row, vector<int> &columns, vector<vector<int>> &results) {
    if (row == GRID_SIZE) { // Found valid placement
        results.push_back(columns);
    } else {
        for (int col = 0; col < GRID_SIZE; ++col) {
            if (check_valid(columns, row, col)) {
                columns[row] = col;
                place_queens(row + 1, columns, results);
            }
        }
    }
}

int main(void) {
    vector<int> columns(8, 0);
    vector<vector<int>> results;

    place_queens(0, columns, results);
    cout << "ways: " << results.size() << endl;
    return 0;
}
