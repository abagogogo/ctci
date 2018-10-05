#include <iostream>
#include <vector>

using namespace std;

void nullify_row(vector<vector<int>> &matrix, int m, int n, int row) {
    for (int c = 0; c < n; ++c)
        matrix[row][c] = 0;
}

void nullify_col(vector<vector<int>> &matrix, int m, int n, int col) {
    for (int r = 0; r < m; ++r) 
        matrix[r][col] = 0;
}

void set_zeros(vector<vector<int>> &matrix, int m, int n) {
    bool first_row_zero = false;
    bool first_col_zero = false;

    // check if first row has zero
    for (int c = 0; c < n; ++c) {
        if (matrix[0][c] == 0) {
            first_row_zero = true;
            break;
        }
    }

    // check if first column has zero
    for (int r = 0; r < m; ++r) {
        if (matrix[r][0] == 0) {
            first_col_zero = true;
            break;
        }
    }

    // check for zeros in the reset of matrix
    for (int r = 1; r < m; ++r) {
        for (int c = 1; c < n; ++c) {
            if (matrix[r][c] == 0) {
                matrix[0][c] = 0;
                matrix[r][0] = 0;
            }
        }
    }

    // nullify rows based on values in first column
    for (int r = 1; r < m; ++r) {
        if (matrix[r][0] == 0)
            nullify_row(matrix, m, n, r);
    }

    // nullify columns based on values in first row
    for (int c = 1; c < n; ++c) {
        if (matrix[0][c] == 0)
            nullify_col(matrix, m, n, c);
    }

    // nullify first row
    if (first_row_zero) {
        nullify_row(matrix, m, n, 0);
    }


    // nullify first column
    if (first_col_zero) {
        nullify_col(matrix, m, n, 0);
    }
}

void print_matrix(vector<vector<int>> &matrix, int len, const string &msg) {
    cout << msg << endl;;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main(void) {
    vector<vector<int>> matrix = {
                { 1, 1, 2, 3},
                { 4, 5, 0, 7},
                { 8, 9, 0,11},
                { 1,13,14,15}};
    print_matrix(matrix, matrix.size(), "before set_zeros:");
    set_zeros(matrix, matrix.size(), matrix[0].size());
    print_matrix(matrix, matrix.size(), "after set_zeros:");

    return 0;
}
