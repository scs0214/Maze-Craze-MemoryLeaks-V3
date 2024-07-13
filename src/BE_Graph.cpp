#include "BE_Graph.h"

const int rowSums[] = {-1, 1, 0, 0};
const int colSums[] = {0, 0, -1, 1};

bool BE_Graph::isValid(int row, int col, const vector<vector<BE_Node*>>& matrix) {
    return (row >= 0 && row < NODE_MATRIX_SIZE && col >= 0 && col < NODE_MATRIX_SIZE && !matrix[row][col]->checkVisited());
}

void BE_Graph::connectionUD(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol) {
    matrix[currentRow][currentCol]->setUp(matrix[newRow][newCol]);
    matrix[newRow][newCol]->setDown(matrix[currentRow][currentCol]);
}

void BE_Graph::connectionDU(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol) {
    matrix[currentRow][currentCol]->setDown(matrix[newRow][newCol]);
    matrix[newRow][newCol]->setUp(matrix[currentRow][currentCol]);
}

void BE_Graph::connectionLR(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol) {
    matrix[currentRow][currentCol]->setLeft(matrix[newRow][newCol]);
    matrix[newRow][newCol]->setRight(matrix[currentRow][currentCol]);
}

void BE_Graph::connectionRL(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol) {
    matrix[currentRow][currentCol]->setRight(matrix[newRow][newCol]);
    matrix[newRow][newCol]->setLeft(matrix[currentRow][currentCol]);
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
                    connectionUD(matrix, row, col, newRow, newCol);
                } else if (i == 1) { // Down
                    connectionDU(matrix, row, col, newRow, newCol);
                } else if (i == 2) { // Left
                    connectionLR(matrix, row, col, newRow, newCol);
                } else if (i == 3) { // Right
                    connectionRL(matrix, row, col, newRow, newCol);
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
                    connectionUD(matrix, row, col, newRow, newCol);
                } else if (i == 1) { // Down
                    connectionDU(matrix, row, col, newRow, newCol);
                } else if (i == 2) { // Left
                    connectionLR(matrix, row, col, newRow, newCol);
                } else if (i == 3) { // Right
                    connectionRL(matrix, row, col, newRow, newCol);
                }

                queue.push({newRow, newCol});
                matrix[newRow][newCol]->setVisited();
            }
        }
    }
}

int BE_Graph::findMissingConnections(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol) {
    int cont = 0;
    if(matrix[currentRow][currentCol]->getUp() == nullptr && currentRow > 0) {
        cont++;
    }
    if(matrix[currentRow][currentCol]->getDown() == nullptr && currentRow < NODE_SIZE) {
        cont++;
    }
    if(matrix[currentRow][currentCol]->getLeft() == nullptr && currentCol > 0) {
        cont++;
    }
    if(matrix[currentRow][currentCol]->getRight() == nullptr && currentRow > NODE_SIZE) {
        cont++;
    }
    return cont;
}

bool BE_Graph::isValidForExtra(int oldRow, int oldCol, int newRow, int newCol, const vector<vector<BE_Node*>>& matrix) {
    bool returnValue = true;
    if(newRow >= 0 && newRow < NODE_MATRIX_SIZE && newCol >= 0 && newCol < NODE_MATRIX_SIZE) {
        if(matrix[oldRow][oldCol]->getUp() == matrix[newRow][newCol]) {
            returnValue = false;
        }
        if(matrix[oldRow][oldCol]->getDown() == matrix[newRow][newCol]) {
            returnValue = false;
        }
        if(matrix[oldRow][oldCol]->getLeft() == matrix[newRow][newCol]) {
            returnValue = false;
        }
        if(matrix[oldRow][oldCol]->getRight() == matrix[newRow][newCol]) {
            returnValue = false;
        }
    }
    else {
        returnValue = false;
    }
    return returnValue;
}

void BE_Graph::connectNodeForExtra(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol) {
    random_device rd;
    mt19937 gen(rd());
    int missingCont = findMissingConnections(matrix, currentRow, currentCol);
    uniform_int_distribution<> possibleConnections(1, missingCont);
    missingCont = possibleConnections(gen);
    vector<int> directions = {0, 1, 2, 3};
    shuffle(directions.begin(), directions.end(), gen);

    for(int i : directions) {
        int newRow = currentRow + rowSums[i];
        int newCol = currentCol + colSums[i];
        while(missingCont > 0 && isValidForExtra(currentRow, currentCol, newRow, newCol, matrix)) {   
            if (i == 0) { // Up
                connectionUD(matrix, currentRow, currentCol, newRow, newCol);
                missingCont--;
            } 
            else if (i == 1) { // Down
                connectionDU(matrix, currentRow, currentCol, newRow, newCol);
                missingCont--;
            } 
            else if (i == 2) { // Left
                connectionLR(matrix, currentRow, currentCol, newRow, newCol);
                missingCont--;
            } 
            else if (i == 3) { // Right
                connectionRL(matrix, currentRow, currentCol, newRow, newCol);
                missingCont--;
            }
        }
    }
}

void BE_Graph::addExtraConnections(vector<vector<BE_Node*>>& matrix) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> values(0, 99);
    for(int i = 0; i < NODE_MATRIX_SIZE; i++) {
        for(int j = 0; j < NODE_MATRIX_SIZE; j++) {
            if(values(gen) < EXTRA_EDGE_PROB) {
                connectNodeForExtra(matrix, i, j);
            }
        }
    }
}