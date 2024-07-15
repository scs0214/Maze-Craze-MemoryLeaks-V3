#ifndef NODEMATRIXBE_H
#define NODEMATRIXBE_H

#include "BE_Node.h"
#include "BE_CellNotAvailable.h"
#include "BE_PortalConnection.h"
#include "BE_CellTreasure.h"
#include "VALUES.h"

#include <stack>
#include <cstdlib>
#include <ctime> 
#include <vector>
#include <utility>
using namespace std;

class BE_NodeMatrix {
    private:
        int rowAmount;
        int colAmount;
        vector<vector<BE_Node*>> matrix;
        
    public:
        BE_NodeMatrix();
        ~BE_NodeMatrix();
        vector<vector<BE_Node*>>& getMatrix();
        void initializeNodeMatrix();
        void placePowers();
        BE_CellPortal* placeFirstPortal(int row, int col);
        BE_CellPortal* generateRandomPortal();
        vector<BE_PortalConnection*> returnPortalConnections();
        BE_CellTreasure* initializeTreasure();
        void addEdgesToCorners();
        void fillHorizontalEdges(int rowNM, int colNM, int rowValue);
        void fillVerticalEdges(int rowNM, int colNM, int columnValue);
        void addLinearEdges();
        BE_Node* getNode(int rowSearch, int colSearch);
        void getRowColFromNode(int& row, int& col, int nodeNumber);
        void rcModifier(char direction, int& newRow, int& newCol, int& nodeRow, int& nodeCol);
        void modifierForPortals(int& newRow, int& newCol, BE_Node* targetNode, vector<BE_PortalConnection*>& portalVector);
        void movePlayer(char direction, int newRow, int newCol, BE_Node* targetNode, BE_CellPlayer* cellPlayer, bool& getDoubleTurn, bool& getMindControl, vector<BE_PortalConnection*>& portalVector);
        void getValuesForJW(char direction, int& newRow, int& newCol, int nodeRow, int nodeCol, BE_Node*& targetNode);
        bool tryMove(char direction, BE_CellPlayer* cellPlayer, bool& getDoubleTurn, bool& getMindControl, vector<BE_PortalConnection*>& portalVector);
};

#endif