#ifndef CELLNORMAL_H
#define CELLNORMAL_H

#include <iostream>
#include "BE_CellBase.h"

using namespace std;

class BE_CellNormal : public BE_CellBase {
    public:
        char getSymbol() const override;
};

#endif