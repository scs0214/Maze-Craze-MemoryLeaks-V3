#ifndef CELLNOTAVAILABLE_H
#define CELLNOTAVAILABLE_H

#include <iostream>
#include "BE_CellBase.h"

using namespace std;

class BE_CellNotAvailable : public BE_CellBase {
    private:
        int row;
        int col;
        
    public:
        BE_CellNotAvailable(int r, int c);
        char getSymbol() const override;
};

#endif