#include "BE_Main.h"

BE_Main::BE_Main(BE_NodeMatrix* nm) : nodeMatrix(nm) {}

BE_NodeMatrix* BE_Main::getNodeMatrix() {
    return nodeMatrix;
}

void BE_Main::initializeNodeMatrix() {
    BE_Graph graph;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> graphOptions(1, 2);
    uniform_int_distribution<> rows(0, NODE_SIZE-1);
    uniform_int_distribution<> cols(0, NODE_SIZE-1);
    int process = graphOptions(gen);
    int startRow = rows(gen);
    int startCol = cols(gen);
    
    nodeMatrix->initializeNodeMatrix();
    nodeMatrix->addEdgesToCorners();
    if(process == 1) {
        graph.BFS(nodeMatrix->getMatrix(), 0, 0);
    }
    else {
        graph.DFS(nodeMatrix->getMatrix(), 0, 0);
    }
    graph.addExtraConnections(nodeMatrix->getMatrix());
    nodeMatrix->addLinearEdges();
}