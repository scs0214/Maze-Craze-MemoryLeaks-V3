#include "BE_Node.h"
#include <iostream>

BE_Node::BE_Node(int id, int r, int c) : ID(id), rowAmount(r), colAmount(c), matrix(r, vector<BE_CellBase*>(c, nullptr)), up(nullptr), down(nullptr), left(nullptr), right(nullptr), visited(false) {}

BE_Node::~BE_Node() {
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            delete matrix[i][j];
        }
    }
}

void BE_Node::fillMatrix() {
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            matrix[i][j] = new BE_CellNormal;
        }
    }
}

void BE_Node::placePowers() {
    BE_Power* power;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> valuesPS(0, 99); // Probabilities for Power Spawn
    uniform_int_distribution<> valuesPT(1, 3); // Values for Power Types
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            if(matrix[i][j] != nullptr && matrix[i][j]->getSymbol() == 'N' && valuesPS(gen) < POWER_SPAWN_RATE) {
                if (valuesPT(gen) == 1) {
                    power = new BE_PowerJumpWall;
                }
                else if (valuesPT(gen) == 2) {
                    power = new BE_PowerDoubleTurn;
                }
                else if (valuesPT(gen) == 3) {
                    power = new BE_PowerMindControl;
                }
                else {
                    power = nullptr;
                }
                
                if (power != nullptr) {
                    delete matrix[i][j];
                    matrix[i][j] = new BE_CellPowered(power);
                }
            }
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

vector<vector<BE_CellBase*>>& BE_Node::getMatrix() {
    return matrix;
}

int BE_Node::getNodeID() {
    return ID;
}

BE_Node* BE_Node::getUp() {
    return up;
}

BE_Node* BE_Node::getDown() {
    return down;
}

BE_Node* BE_Node::getLeft() {
    return left;
}

BE_Node* BE_Node::getRight() {
    return right;
}

void BE_Node::setUp(BE_Node* neighbor) {
    up = neighbor;
}

void BE_Node::setDown(BE_Node* neighbor) {
    down = neighbor;
}

void BE_Node::setLeft(BE_Node* neighbor) {
    left = neighbor;
}

void BE_Node::setRight(BE_Node* neighbor) {
    right = neighbor;
}

bool BE_Node::checkVisited() {
    return visited;
}

void BE_Node::setVisited() {
    visited = true;
}