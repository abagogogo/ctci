#include <bits/stdc++.h>

using namespace std;

enum Piece {
    EMPTY  = 0,
    NOUGHT = 1,
    CROSS  = 2,
};

struct PosIterator {
    int row_;
    int col_;
    int r_inc_;
    int c_inc_;
    int size_;

    PosIterator(int row,   // start row
                int col,   // start column 
                int r_inc, // row increment
                int c_inc, // column increment
                int size) {// size of the board
        // Do decrement for first call of next()
        row_ = row - r_inc; 
        col_ = col - c_inc;

        r_inc_ = r_inc;
        c_inc_ = c_inc;
        size_ = size;
    }

    bool has_next(void) {
        int next_r = row_ + r_inc_;
        int next_c = col_ + c_inc_;
        return next_r >= 0 && next_r < size_ 
            && next_c >= 0 && next_c < size_;
    }

    pair<int, int> next(void) {
        row_ += r_inc_;
        col_ += c_inc_;
        return {row_, col_};
    }
};

Piece has_won(vector<vector<Piece>> &board, PosIterator &it) {
    pair<int, int> pos = it.next();
    Piece first = board[pos.first][pos.second];

    while (it.has_next()) {
        pos = it.next();
        if (board[pos.first][pos.second] != first) {
            return EMPTY;
        }
    }
    return first;
}

Piece has_won(vector<vector<Piece>> &board) {
    if (board.size() != board[0].size()) return EMPTY;

    int n = board.size();
    vector<PosIterator> list;
    for (int i = 0; i < n; ++i) {
        list.push_back(PosIterator(i, 0, 0, 1, n)); // row i
        list.push_back(PosIterator(0, i, 1, 0, n)); // col i
    }
    list.push_back(PosIterator(0, 0, 1, 1, n)); // diagnoal
    list.push_back(PosIterator(0, n-1, 1, -1, n)); // diagnoal
    
    for (int i = 0; i < list.size(); ++i) {
        Piece winner = has_won(board, list[i]);
        if (winner != EMPTY) return winner;
    }
    return EMPTY;
}

int main(void) {
    vector<vector<Piece>> board = {
        {NOUGHT, EMPTY , CROSS },
        {CROSS , CROSS , EMPTY },
        {NOUGHT, NOUGHT, NOUGHT}};

    Piece winner = has_won(board);
    if (winner == EMPTY) {
        cout << "no winner" << endl;
    } else {
        cout << (winner == NOUGHT ? "NOUGHT" : "CROSS") << endl;
    }

    return 0;
}
