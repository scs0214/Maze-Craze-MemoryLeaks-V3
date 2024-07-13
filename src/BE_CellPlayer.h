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
        char getSymbol() const override;
};

#endif