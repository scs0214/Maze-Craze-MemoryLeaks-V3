#include "BE_Graph.h"

const int rowSums[] = {-1, 1, 0, 0};
const int colSums[] = {0, 0, -1, 1};

bool BE_Graph::isValid(int row, int col, const vector<vector<BE_Node*>>& matrix) {
    return (row >= 0 && row < NODE_MATRIX_SIZE && col >= 0 && col < NODE_MATRIX_SIZE && !matrix[row][col]->checkVisited());
}

void BE_Graph::DFS(vector<vector<BE_Node*>>& matrix, int startRow, int startCol) {
    stack<pair<int, int>> stack;
    stack.push({startRow, startCol});
    matrix[startRow][startCol]->setVisited();

    random_device rd;
    mt19937 gen(rd());

    while (!stack.empty()) {
        auto [row, col] = stack.top();
        stack.pop();

        vector<int> directions = {0, 1, 2, 3};
        shuffle(directions.begin(), directions.end(), gen);

        for (int i : directions) {
            int newRow = row + rowSums[i];
            int newCol = col + colSums[i];
            if (isValid(newRow, newCol, matrix)) {
                if (i == 0) { // Up
                    matrix[row][col]->setUp(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setDown(matrix[row][col]);
                } else if (i == 1) { // Down
                    matrix[row][col]->setDown(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setUp(matrix[row][col]);
                } else if (i == 2) { // Left
                    matrix[row][col]->setLeft(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setRight(matrix[row][col]);
                } else if (i == 3) { // Right
                    matrix[row][col]->setRight(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setLeft(matrix[row][col]);
                }

                stack.push({newRow, newCol});
                matrix[newRow][newCol]->setVisited();
            }
        }
    }
}

void BE_Graph::BFS(vector<vector<BE_Node*>>& matrix, int startRow, int startCol) {
    queue<pair<int, int>> queue;
    queue.push({startRow, startCol});
    matrix[startRow][startCol]->setVisited();

    while (!queue.empty()) {
        auto [row, col] = queue.front();
        queue.pop();

        for (int i = 0; i < 4; ++i) {
            int newRow = row + rowSums[i];
            int newCol = col + colSums[i];
            if (isValid(newRow, newCol, matrix)) {
                if (i == 0) { // Up
                    matrix[row][col]->setUp(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setDown(matrix[row][col]);
                } else if (i == 1) { // Down
                    matrix[row][col]->setDown(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setUp(matrix[row][col]);
                } else if (i == 2) { // Left
                    matrix[row][col]->setLeft(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setRight(matrix[row][col]);
                } else if (i == 3) { // Right
                    matrix[row][col]->setRight(matrix[newRow][newCol]);
                    matrix[newRow][newCol]->setLeft(matrix[row][col]);
                }

                queue.push({newRow, newCol});
                matrix[newRow][newCol]->setVisited();
            }
        }
    }
}