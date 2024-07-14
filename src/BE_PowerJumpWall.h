#ifndef POWERJUMPWALL_H
#define POWERJUMPWALL_H

#include "BE_Power.h"
#include "BE_Player.h"
using namespace std;

class BE_PowerJumpWall : public BE_Power {
    public:
        char getSymbol();
        void immediateEffect(BE_Player* player);
};

#endif