#include <bits/stdc++.h>

using namespace std;

#define METHOD 2

struct Coordinate {
    int row, col;

    Coordinate(void) {
        row = col = 0;
    }

    Coordinate(int r, int c) {
        row = r;
        col = c;
    }

    bool in_bounds(vector<vector<int>> &matrix) {
        return row >= 0 && row < matrix.size() 
            && col >= 0 && col < matrix[0].size();
    }

    bool is_before(const Coordinate &p) {
        return row <= p.row && col <= p.col;
    }

    bool set_to_average(const Coordinate &from, const Coordinate &to) {
        row = (from.row + to.row) / 2;
        col = (from.col + to.col) / 2;
    }

    bool is_valid(void) {
        return row >= 0 && col >= 0;
    }
};

#if METHOD==1 // O(m+n)
    Coordinate find_element(vector<vector<int>> &matrix, int elem) {
        int row = 0;
        int col = matrix[0].size() - 1;

        while (row < matrix.size() && col >= 0) {
            if (matrix[row][col] == elem) {
                return Coordinate(row, col);
            } else if (matrix[row][col] > elem) {
                --col;
            } else {
                ++row;
            }
        }

        return Coordinate(-1, -1);
    }
#elif METHOD==2 // O(log(m)^2)
    Coordinate find_element(vector<vector<int>> &matrix, Coordinate orig, Coordinate dest, int elem);
    Coordinate partition_and_search(vector<vector<int>> &matrix, Coordinate orig, Coordinate dest, Coordinate pivot, int elem);

    Coordinate find_element(vector<vector<int>> &matrix, int elem) {
        Coordinate orig(0, 0);
        Coordinate dest(matrix.size() - 1, matrix[0].size() - 1);
        return find_element(matrix, orig, dest, elem);
    }

    Coordinate find_element(vector<vector<int>> &matrix, Coordinate orig, Coordinate dest, int elem) {
        if (!orig.in_bounds(matrix) || !dest.in_bounds(matrix)) {
            return Coordinate(-1, -1);
        }

        if (matrix[orig.row][orig.col] == elem) {
            return orig;
        } else if (!orig.is_before(dest)) {
            return Coordinate(-1, -1);
        }

        // Set start to start of diagnoal and end to the end of the diagnoal.
        // Since the grid may not be square, the end of diagonal may not equal dest.
        Coordinate start = orig;
        int diag_dist = min(dest.row - orig.row, dest.col - orig.col);
        Coordinate end(start.row + diag_dist, start.col + diag_dist);
        Coordinate p(0, 0);

        // Do binary search on the diagnoal, looking for the first one > element.
        while (start.is_before(end)) {
            p.set_to_average(start, end);
            if (matrix[p.row][p.col] < elem) {
                start.row = p.row + 1;
                start.col = p.col + 1;
            } else {
                end.row = p.row - 1;
                end.col = p.col - 1;
            }
        }

        // Split the grid into quadrants.
        // Search bottome left and top right.
        //printf("RJ_DBG: finding %d -> pivot = (%d, %d)\n", elem, start.row, start.col);
        return partition_and_search(matrix, orig, dest, start, elem);
    }


    Coordinate partition_and_search(vector<vector<int>> &matrix, Coordinate orig, Coordinate dest, Coordinate pivot, int elem) {
        Coordinate ll_orig(pivot.row, orig.col);
        Coordinate ll_dest(dest.row, pivot.col - 1);
        Coordinate ur_orig(orig.row, pivot.col);
        Coordinate ur_dest(pivot.row - 1, dest.col);

        //printf("RJ_DBG: searching lower left (%d, %d) ~ (%d, %d)\n", ll_orig.row, ll_orig.col, ll_dest.row, ll_dest.col);
        Coordinate lower_left = find_element(matrix, ll_orig, ll_dest, elem);
        if (!lower_left.is_valid()) {
            //printf("RJ_DBG: searching upper right (%d, %d) ~ (%d, %d)\n", ur_orig.row, ur_orig.col, ur_dest.row, ur_dest.col);
            return find_element(matrix, ur_orig, ur_dest, elem);
        } else {
            return lower_left;
        }
    }

#endif

int main(void) {
    vector<vector<int>> matrix {
        {15, 20,  40,  85},
        {20, 35,  80,  95},
        {30, 55,  95, 105},
        {40, 80, 100, 120}};

    vector<vector<int>> tests {
        {15,  0, 0},
        {120, 3, 3},
        {55,  2, 1},
        {85,  0, 3}, 
        {35,  1, 1}, 
        };

    for (auto test : tests) {
        Coordinate p = find_element(matrix, test[0]);
        if (p.row == test[1] && p.col == test[2]) {
            cout << "element " << test[0] << " is at (" << p.row << ", " << p.col << ")...[OK]" << endl;
        } else {
            cout << "element " << test[0] << " is at (" << p.row << ", " << p.col << ")...[NG]" << endl;
        }
    }

    return 0;
}
