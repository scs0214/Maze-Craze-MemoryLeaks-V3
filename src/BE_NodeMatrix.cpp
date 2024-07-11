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

BE_NodeMatrix::BE_NodeMatrix(int r, int c) : rowAmount(r), colAmount(c), matrix(r, vector<BE_Node*>(c, nullptr)) {}

BE_NodeMatrix::~BE_NodeMatrix() {
    for (int i = 0; i < rowAmount; ++i) {
        for (int j = 0; j < colAmount; ++j) {
            delete matrix[i][j];
        }
    }
}
