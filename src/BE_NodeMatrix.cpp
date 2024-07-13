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