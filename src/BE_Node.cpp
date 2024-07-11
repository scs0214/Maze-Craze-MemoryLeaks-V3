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

void BE_Node::removeUp() {
    if (up != nullptr && up->down != this) {
        up = nullptr;
    }
}

void BE_Node::removeDown() {
    if (down != nullptr && down->up != this) {
        down = nullptr;
    }
}

void BE_Node::removeLeft() {
    if (left != nullptr && left->right != this) {
        left = nullptr;
    }
}

void BE_Node::removeRight() {
    if (right != nullptr && right->left != this) {
        right = nullptr;
    }
}

void BE_Node::printConnections() { // FOR TESTS
    cout << "Node ID: " << ID << endl;
    cout << "Connections:" << endl;
    if (up != nullptr) {
        cout << "  Up: Node " << up->getNodeID() << endl;
    } else {
        cout << "  Up: None" << endl;
    }
    if (down != nullptr) {
        cout << "  Down: Node " << down->getNodeID() << endl;
    } else {
        cout << "  Down: None" << endl;
    }
    if (left != nullptr) {
        cout << "  Left: Node " << left->getNodeID() << endl;
    } else {
        cout << "  Left: None" << endl;
    }
    if (right != nullptr) {
        cout << "  Right: Node " << right->getNodeID() << endl;
    } else {
        cout << "  Right: None" << endl;
    }
}

bool BE_Node::checkVisited() {
    return visited;
}

void BE_Node::setVisited() {
    visited = true;
}

