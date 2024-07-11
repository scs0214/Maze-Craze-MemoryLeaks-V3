#include "BE_Node.h"
#include <iostream>

BE_Node::BE_Node(int id, int r, int c) : ID(id), rowAmount(r), colAmount(c), matrix(r, vector<BE_CellBase*>(c, nullptr)), visited(false) {}

BE_Node::~BE_Node() {
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            delete matrix[i][j];
        }
    }
}

void BE_Node::fillMatrix() {
    cout << "Filling..." << endl;
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            matrix[i][j] = new BE_CellNormal(i, j);
        }
    }
}

void BE_Node::printMatrix() {
    cout << "Printing matrix..." << endl;
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            if (matrix[i][j] != nullptr) {
                cout << matrix[i][j]->getSymbol() << ' ';
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
}