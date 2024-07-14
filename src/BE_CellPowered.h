#ifndef CELLPOWERED_H
#define CELLPOWERED_H

#include <iostream>
#include "BE_CellBase.h"
#include "BE_Power.h"

using namespace std;

class BE_CellPowered : public BE_CellBase {
    private:
        BE_Power* power;
        
    public:
        BE_CellPowered(BE_Power* power);
        char getSymbol() const override;
};

#endif