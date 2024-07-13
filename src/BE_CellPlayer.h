#ifndef CELLPLAYER_H
#define CELLPLAYER_H

#include <iostream>
#include "BE_CellBase.h"
#include "BE_Player.h"

using namespace std;

class BE_CellPlayer : public BE_CellBase {
    private:
        int row;
        int col;
        int actualNode;
        BE_Player* player;
        
    public:
        BE_CellPlayer(int r, int c, int an, BE_Player* player);
        int getRow();
        int getCol();
        int getActualNode();
        BE_Player* getPlayer();
        void setRow(int newValue);
        void setCol(int newValue);
        void setActualNode(int newValue);
        char getSymbol() const override;
};

#endif