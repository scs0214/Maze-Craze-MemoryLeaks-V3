#include "BE_NodeMatrix.h"
#include <iostream>

char BE_NodeMatrix::generateRandomDirection() {
    int randomDir = rand()%4;
    char charValue = '-';
    switch(randomDir) {
        case 0:
            charValue = 'U';
        case 1:
            charValue = 'D';
        case 2:
            charValue = 'L';
        case 3:
            charValue = 'R';
    }
    return charValue;
}

BE_NodeMatrix::BE_NodeMatrix() : rowAmount(NODE_MATRIX_SIZE), colAmount(NODE_MATRIX_SIZE), 
                                 matrix(NODE_MATRIX_SIZE, vector<BE_Node*>(NODE_MATRIX_SIZE, nullptr)) {}

BE_NodeMatrix::~BE_NodeMatrix() {
    for (int i = 0; i < rowAmount; ++i) {
        for (int j = 0; j < colAmount; ++j) {
            delete matrix[i][j];
        }
    }
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

void BE_NodeMatrix::printNodeMatrix() {
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            printf("NODE %i: \n", matrix[i][j]->getNodeID());
            matrix[i][j]->printMatrix();
            printf("\n");
        }
    }
}
