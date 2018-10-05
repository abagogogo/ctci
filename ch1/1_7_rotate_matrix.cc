#include <iostream>
#include <vector>

using namespace std;

void rotate(vector<vector<int>> &matrix, int len) {
    if (len <= 1) return;

    for (int layer = 0; layer < len/2; ++layer) {
        int first = layer;
        int last  = len - 1 - layer;
        for(int i = first; i < last; ++i) {
            int offset = i - first;
            int top = matrix[first][i];

            // left -> top
            matrix[first][i] = matrix[last - offset][first];
            // bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset];
            // right -> bottom
            matrix[last][last - offset] = matrix[i][last];
            // top -> right
            matrix[i][last] = top;
        }
    }
}

// review
void rotate2(vector<vector<int>> &matrix, int len) {
    if (len <= 1) return;

    for (int layer = 0; layer < len/2; ++len) {
        for (int offset = 0; offset < len - layer - 1; ++offset) {
            int *top = &matrix[layer][layer + offset];
            int *left = &matrix[len - 1 - layer - offset][layer];
            int *bottom = &matrix[len - 1 - layer][len - 1 - layer - offset];
            int *right = &matrix[layer + offset][len - 1 - layer];

            int tmp = *top;
            *top = *left;
            *left = *bottom;
            *bottom = *right;
            *right = tmp;
        }
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
                { 0, 1, 2, 3},
                { 4, 5, 6, 7},
                { 8, 9,10,11},
                {12,13,14,15}};
    vector<vector<int>> matrix2 = matrix;

    print_matrix(matrix, matrix.size(), "before rotation:");
    rotate(matrix, matrix.size());
    print_matrix(matrix, matrix.size(), "after rotation:");

    print_matrix(matrix2, matrix.size(), "2 before rotation:");
    rotate(matrix2, matrix.size());
    print_matrix(matrix2, matrix.size(), "2 after rotation:");

    cout << ((matrix == matrix2) ? "PASS" : "NG") << endl;
    return 0;
}
