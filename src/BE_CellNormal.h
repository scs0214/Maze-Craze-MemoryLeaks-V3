#ifndef CELLNORMAL_H
#define CELLNORMAL_H

#include <iostream>
#include "BE_CellBase.h"

using namespace std;

class BE_CellNormal : public BE_CellBase {
    private:
        int row;
        int col;
        
    public:
        BE_CellNormal(int r, int c);
        char getSymbol() const override;
};

#endif