#ifndef BEMAIN_H
#define BEMAIN_H

#include <iostream>
#include <vector>
#include <random>
#include "BE_Player.h"
#include "BE_Graph.h"
#include "BE_NodeMatrix.h"
#include "BE_PortalConnection.h"
#include "BE_CellTreasure.h"
#include "VALUES.h"
using namespace std;

class BE_Main {
    private:
        vector<BE_PortalConnection*> portals;
        BE_NodeMatrix* nodeMatrix;
        BE_CellPlayer* player1;
        BE_CellPlayer* player2;

    public:
        BE_Main(BE_NodeMatrix* nm);
        vector<BE_PortalConnection*>& getPortalVector();
        BE_NodeMatrix* getNodeMatrix();
        void initializeNodeMatrix(BE_CellPlayer* p1, BE_CellPlayer* p2);
        bool movePlayer(BE_CellPlayer* player, char direction, bool& getDoubleTurn, bool& getMindControl);
        int turnChange(int lastTurn);
};

#endif