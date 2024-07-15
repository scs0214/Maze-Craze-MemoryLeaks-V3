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

void BE_NodeMatrix::placePowers() {
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            matrix[i][j]->placePowers();
        }
    }
}

BE_CellPortal* BE_NodeMatrix::placeFirstPortal(int row, int col) {
    BE_CellPortal* portal = nullptr;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> valuesPS(0, 99);
    for (int i = 0; i < NODE_SIZE; i++) {
        for (int j = 0; j < NODE_SIZE; j++) {
            if(matrix[row][col]->getMatrix()[i][j]->getSymbol() == 'N' && valuesPS(gen) < PORTAL_SPAWN_RATE) {
                BE_Node* currentNode = getNode(row, col);
                portal = new BE_CellPortal(i, j, currentNode->getNodeID());
                return portal;
            }
        }
    }
    return portal;
}

BE_CellPortal* BE_NodeMatrix::generateRandomPortal() {
    BE_CellPortal* portal;
    bool portalPlaced = false;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> valuesNM(0, NODE_MATRIX_SIZE-1);
    uniform_int_distribution<> valuesN(0, NODE_SIZE-1);
    
    while(!portalPlaced) {
        int rowS = valuesNM(gen);
        int colS = valuesNM(gen);
        BE_Node* targetNode = getNode(rowS, colS);

        int rowForP = valuesN(gen);
        int colForP = valuesN(gen);
        if(targetNode->getMatrix()[rowForP][colForP]->getSymbol() == 'N') {
            portal = new BE_CellPortal(rowForP, colForP, targetNode->getNodeID());
            targetNode->getMatrix()[rowForP][colForP] = portal;
            portalPlaced = true;
        }
    }
    return portal;
}

vector<BE_PortalConnection*> BE_NodeMatrix::returnPortalConnections() { // Saves all the portals created and links them
    vector<BE_PortalConnection*> portalsVector;
    BE_PortalConnection* portalConnection = nullptr;
    BE_CellPortal* portal1 = nullptr;
    BE_CellPortal* portal2 = nullptr;
    for (int i = 0; i < rowAmount; i++) {
        for (int j = 0; j < colAmount; j++) {
            portalConnection = nullptr;
            portal1 = nullptr;
            portal2 = nullptr;

            portal1 = placeFirstPortal(i, j);
            if(portal1 != nullptr) {
                portal2 = generateRandomPortal();
                pair<BE_CellPortal*, BE_CellPortal*> pair = make_pair(portal1, portal2);
                portalConnection = new BE_PortalConnection(pair);
                portalsVector.push_back(portalConnection);
            }
        }
    }
    return portalsVector;
}

BE_CellTreasure* BE_NodeMatrix::initializeTreasure() {
    BE_CellTreasure* treasure;
    bool treasurePlaced = false;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> valuesNM(0, NODE_MATRIX_SIZE-1);
    uniform_int_distribution<> valuesN(0, NODE_SIZE-1);
    
    while(!treasurePlaced) {
        int rowS = valuesNM(gen);
        int colS = valuesNM(gen);
        BE_Node* node = getNode(rowS, colS);

        int rowForTreasure = valuesN(gen);
        int colForTreasure = valuesN(gen);

        if(node->getMatrix()[rowForTreasure][colForTreasure]->getSymbol() == 'N') {
            treasure = new BE_CellTreasure(rowForTreasure, colForTreasure, node->getNodeID());
            node->getMatrix()[rowForTreasure][colForTreasure] = treasure;
            treasurePlaced = true;
        }
    }
    return treasure;
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

void BE_NodeMatrix::rcModifier(char direction, int& newRow, int& newCol, int& nodeRow, int& nodeCol){
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
}

void BE_NodeMatrix::modifierForPortals(int& newRow, int& newCol, BE_Node* targetNode, int& nodeRow, int& nodeCol, vector<BE_PortalConnection*>& portalVector) {
    // Modifies values if a player enters a portal cell
    int pvSize = portalVector.size();

    for(int i = 0; i < pvSize; i++) {
        BE_CellPortal* portal1 = portalVector[i]->getFirst();
        BE_CellPortal* portal2 = portalVector[i]->getSecond();

        if(newRow == portal1->getRow() && newCol == portal1->getCol() && targetNode->getNodeID() == portal1->getNodeValue()) {
            newRow = portal2->getRow();
            newCol = portal2->getCol();
            getRowColFromNode(nodeRow, nodeCol, portal2->getNodeValue());
            portalVector.erase(portalVector.begin() + i);
        }
        else if(newRow == portal2->getRow() && newCol == portal2->getCol() && targetNode->getNodeID() == portal2->getNodeValue()) {
            newRow = portal1->getRow();
            newCol = portal1->getCol();
            getRowColFromNode(nodeRow, nodeCol, portal1->getNodeValue());
            portalVector.erase(portalVector.begin() + i);
        }
    }
}

void BE_NodeMatrix::movePlayer(char direction, int newRow, int newCol, BE_Node* targetNode, BE_CellPlayer* cellPlayer, bool& getDoubleTurn, bool& getMindControl, vector<BE_PortalConnection*>& portalVector) {
    if(targetNode->getMatrix()[newRow][newCol]->getSymbol() == 'D') { // Applies powers if needed
        getDoubleTurn = true;
    }
    else if(targetNode->getMatrix()[newRow][newCol]->getSymbol() == 'M') {
        getMindControl = true;
    }
    else if(targetNode->getMatrix()[newRow][newCol]->getSymbol() == 'J') {
        cellPlayer->getPlayer()->getJumpWall();
    }
    else if(targetNode->getMatrix()[newRow][newCol]->getSymbol() == 'P') {
        int nodeRow;
        int nodeCol;
        targetNode->getMatrix()[newRow][newCol] = new BE_CellNormal();
        modifierForPortals(newRow, newCol, targetNode, nodeRow, nodeCol, portalVector);
        targetNode = getNode(nodeRow, nodeCol);
    }

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

void BE_NodeMatrix::getValuesForJW(char direction, int& newRow, int& newCol, int nodeRow, int nodeCol, BE_Node*& targetNode) {
    bool stop = false;
    while(!stop) {
        rcModifier(direction, newRow, newCol, nodeRow, nodeCol);
        targetNode = getNode(nodeRow, nodeCol);
        if(targetNode == nullptr) {
            stop = true;
        }
        else {
            char symbolCheck = targetNode->getMatrix()[newRow][newCol]->getSymbol();
            if(symbolCheck != 'X' && symbolCheck != '1' && symbolCheck != '2') {
                stop = true;
            }
        }
    }
}

bool BE_NodeMatrix::tryMove(char direction, BE_CellPlayer* cellPlayer, bool& getDoubleTurn, bool& getMindControl, vector<BE_PortalConnection*>& portalVector) {
    bool movePossible = false;
    int nodeRow;
    int nodeCol;
    int newRow = cellPlayer->getRow();
    int newCol = cellPlayer->getCol();
    int newNode = cellPlayer->getActualNode();
    getRowColFromNode(nodeRow, nodeCol, newNode);
    rcModifier(direction, newRow, newCol, nodeRow, nodeCol);

    BE_Node* targetNode = getNode(nodeRow, nodeCol);
    if(targetNode != nullptr) { // Checks if the node to access exists
        char symbol = targetNode->getMatrix()[newRow][newCol]->getSymbol();
        if(symbol != 'X' && symbol != '2' && symbol != '1') { // Checks if the position to access is NOT an unaccessible cell
            movePlayer(direction, newRow, newCol, targetNode, cellPlayer, getDoubleTurn, getMindControl, portalVector);
            movePossible = true;                      
        }
        else if (symbol == 'X' && cellPlayer->getPlayer()->getJumpWallAmount() > 0) {
            getValuesForJW(direction, newRow, newCol, nodeRow, nodeCol, targetNode);
            if(targetNode != nullptr) {
                movePlayer(direction, newRow, newCol, targetNode, cellPlayer, getDoubleTurn, getMindControl, portalVector);
                movePossible = true;  
                cellPlayer->getPlayer()->useJumpWall();
            }
        }
    }
    return movePossible;
}