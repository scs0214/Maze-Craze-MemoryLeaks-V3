#ifndef CELLTREASURE_H
#define CELLTREASURE_H

#include <iostream>
#include "BE_CellBase.h"
#include "BE_CellPlayer.h"
#include "VALUES.h"

using namespace std;

class BE_CellTreasure : public BE_CellBase {
    private:
        int rowT;
        int colT;
        int actualNodeT;
        
    public:
        BE_CellTreasure(int r, int c, int an);
        char getSymbol() const override;
        int getWinnerPlayer(BE_CellPlayer* p1, BE_CellPlayer* p2);
        int getRow();
        int getCol();
        int getActualNode();
};

#endif