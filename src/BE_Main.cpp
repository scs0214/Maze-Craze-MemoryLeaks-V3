#include "BE_Main.h"

BE_Main::BE_Main(BE_NodeMatrix* nm) : nodeMatrix(nm), player1(nullptr), player2(nullptr) {}

BE_NodeMatrix* BE_Main::getNodeMatrix() {
    return nodeMatrix;
}

void BE_Main::initializeNodeMatrix(BE_CellPlayer* p1, BE_CellPlayer* p2) {
    BE_Graph graph;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> graphOptions(1, 2);
    uniform_int_distribution<> rows(0, NODE_MATRIX_SIZE-1);
    uniform_int_distribution<> cols(0, NODE_MATRIX_SIZE-1);
    int process = graphOptions(gen);
    int startRow = rows(gen);
    int startCol = cols(gen);
    
    nodeMatrix->initializeNodeMatrix();
    nodeMatrix->addEdgesToCorners();
    if(process == 1) {
        graph.BFS(nodeMatrix->getMatrix(), startRow, startCol);
    }
    else {
        graph.DFS(nodeMatrix->getMatrix(), startRow, startCol);
    }
    graph.addExtraConnections(nodeMatrix->getMatrix());
    nodeMatrix->addLinearEdges();

    int maxVNM = NODE_MATRIX_SIZE-1; // Max value for Node Matrix pos
    int maxVNP = NODE_SIZE-1; // Max value for Node Pos
    nodeMatrix->getMatrix()[0][0]->getMatrix()[0][0] = p1;
    nodeMatrix->getMatrix()[maxVNM][maxVNM]->getMatrix()[maxVNP][maxVNP] = p2;
}

bool BE_Main::movePlayer(BE_CellPlayer* player, char direction) {
    return nodeMatrix->tryMove(direction, player);
}

int BE_Main::turnChange(int lastTurn) {
    int newValue;
    if (lastTurn == 1) {
        newValue = 2;
    }
    else if (lastTurn == 2) {
        newValue = 1;
    }
    return newValue;
}