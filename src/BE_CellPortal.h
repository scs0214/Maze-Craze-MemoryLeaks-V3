#ifndef CELLPORTALBE_H
#define CELLPORTALBE_H

#include "BE_CellBase.h"
using namespace std;

class BE_CellPortal : public BE_CellBase {
    private:
        int row;
        int col;
        int nodeValue;

    public:
        BE_CellPortal(int r, int c, int nv);
        char getSymbol() const;
        int getRow();
        int getCol();
        int getNodeValue();
};

#endif