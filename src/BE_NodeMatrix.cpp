#include "BE_NodeMatrix.h"
#include <iostream>

BE_NodeMatrix::BE_NodeMatrix() : rowAmount(NODE_MATRIX_SIZE), colAmount(NODE_MATRIX_SIZE), 
                                 matrix(NODE_MATRIX_SIZE, vector<BE_Node*>(NODE_MATRIX_SIZE, nullptr)) {}

BE_NodeMatrix::~BE_NodeMatrix() {
    for (int i = 0; i < rowAmount; ++i) {
        for (int j = 0; j < colAmount; ++j) {
            delete matrix[i][j];
        }
    }
}

vector<vector<BE_Node*>>& BE_NodeMatrix::getMatrix() {
    return matrix;
}

void BE_NodeMatrix::initializeNodeMatrix() {
    int idForNode = 1;
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            matrix[i][j] = new BE_Node(idForNode, NODE_SIZE, NODE_SIZE);
            matrix[i][j]->fillMatrix();
            idForNode++;
        }
    }
}

void BE_NodeMatrix::addEdgesToCorners() {
    for(int i = 0; i < NODE_MATRIX_SIZE; i++) {
        for(int j = 0; j < NODE_MATRIX_SIZE; j++) {
            if(i > 0 && j > 0) { // Up-Left Corner
                matrix[i][j]->getMatrix()[0][0] = new BE_CellNotAvailable(i, j);
            }
            if(i > 0 && j < NODE_MATRIX_SIZE-1) { // Up-Right Corner
                matrix[i][j]->getMatrix()[0][NODE_SIZE-1] = new BE_CellNotAvailable(i, j);
            }
            if(i < NODE_MATRIX_SIZE-1 && j > 0) { // Down-Left Corner
                matrix[i][j]->getMatrix()[NODE_SIZE-1][0] = new BE_CellNotAvailable(i, j);
            }
            if(i < NODE_MATRIX_SIZE-1 && j < NODE_MATRIX_SIZE-1) { // Down-Right Corner
                matrix[i][j]->getMatrix()[NODE_SIZE-1][NODE_SIZE-1] = new BE_CellNotAvailable(i, j);
            }
        }
    }
}

void BE_NodeMatrix::fillHorizontalEdges(int rowNM, int colNM, int rowValue) {
    for(int i = 0; i < NODE_SIZE; i++) {
        matrix[rowNM][colNM]->getMatrix()[rowValue][i] = new BE_CellNotAvailable(rowValue, i);
    }
}

void BE_NodeMatrix::fillVerticalEdges(int rowNM, int colNM, int columnValue) {
    for(int i = 0; i < NODE_SIZE; i++) {
        matrix[rowNM][colNM]->getMatrix()[i][columnValue] = new BE_CellNotAvailable(i, columnValue);
    }
}

void BE_NodeMatrix::addLinearEdges() {
    for(int i = 0; i < NODE_MATRIX_SIZE; i++) {
        for(int j = 0; j < NODE_MATRIX_SIZE; j++) {
            if(matrix[i][j]->getUp() == nullptr && i > 0) { // Up Edge
                fillHorizontalEdges(i, j, 0);
            }
            if(matrix[i][j]->getDown() == nullptr && i < NODE_MATRIX_SIZE-1) { // Down Edge
                fillHorizontalEdges(i, j, NODE_SIZE-1);
            }
            if(matrix[i][j]->getLeft() == nullptr && j > 0) { // Left Edge
                fillVerticalEdges(i, j, 0);
            }
            if(matrix[i][j]->getRight() == nullptr && j < NODE_MATRIX_SIZE-1) { // Right Edge
                fillVerticalEdges(i, j, NODE_SIZE-1);
            }
        }
    }
}

void BE_NodeMatrix::printNodeMatrix() {
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            printf("NODE %i: \n", matrix[i][j]->getNodeID());
            matrix[i][j]->printMatrix();
            matrix[i][j]->printConnections();
            printf("\n");
        }
    }
}

BE_Node* BE_NodeMatrix::getNode(int rowSearch, int colSearch) {
    BE_Node* returnNode = nullptr;
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            if (i == rowSearch && j == colSearch) {
                returnNode = matrix[i][j];
            }
        }
    }
    return returnNode;
}

void BE_NodeMatrix::getRowColFromNode(int& row, int& col, int nodeNumber) {
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            if (matrix[i][j]->getNodeID() == nodeNumber) {
                row = i;
                col = j;
            }
        }
    }
}


void BE_NodeMatrix::movePlayer(char direction, int newRow, int newCol, BE_Node* targetNode, BE_CellPlayer* cellPlayer) { // APPLY POWERS
    int oldRowN;
    int oldColN;
    getRowColFromNode(oldRowN, oldColN, cellPlayer->getActualNode());
    BE_Node* oldNode = getNode(oldRowN, oldColN);

    oldNode->getMatrix()[cellPlayer->getRow()][cellPlayer->getCol()] = new BE_CellNormal();
    targetNode->getMatrix()[newRow][newCol] = cellPlayer;
    cellPlayer->setRow(newRow);
    cellPlayer->setCol(newCol);
    cellPlayer->setActualNode(targetNode->getNodeID()); // Moves cellPlayer and modifies its values.
}

bool BE_NodeMatrix::tryMove(char direction, BE_CellPlayer* cellPlayer) {
    bool movePossible = false;
    int nodeRow;
    int nodeCol;
    int newRow = cellPlayer->getRow();
    int newCol = cellPlayer->getCol();
    int newNode = cellPlayer->getActualNode();
    getRowColFromNode(nodeRow, nodeCol, newNode);

    if (direction == 'w') { // Up
        newRow--;
    }
    else if (direction == 's') { // Down
        newRow++;
    }
    else if (direction == 'a') { // Left
        newCol--;
    }
    else if (direction == 'd') { // Right
        newCol++;
    }
    else { // If the direction is not valid
        return false;
    }

    if (newRow < 0) { // Modifies values if out of bounds
        newRow = NODE_SIZE-1;
        nodeRow--;
    }
    else if (newRow > NODE_SIZE-1) {
        newRow = 0;
        nodeRow++;
    }
    if (newCol < 0) {
        newCol = NODE_SIZE-1;
        nodeCol--;
    }
    else if (newCol > NODE_SIZE-1) {
        newCol = 0;
        nodeCol++;
    }

    BE_Node* targetNode = getNode(nodeRow, nodeCol);
    if(targetNode != nullptr) { // Checks if the node to access exists
        char symbol = targetNode->getMatrix()[newRow][newCol]->getSymbol();
        if(symbol != 'X' && symbol != '2' && symbol != '1') { // Checks if the position to access is NOT an unaccessible cell
            movePlayer(direction, newRow, newCol, targetNode, cellPlayer);
            movePossible = true;                      
        }
    }
    return movePossible;
}