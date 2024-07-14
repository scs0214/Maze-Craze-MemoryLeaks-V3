#include "BE_CellTreasure.h"

BE_CellTreasure::BE_CellTreasure(int r, int c, int an) : rowT(r), colT(c) , actualNodeT(an) {}

char BE_CellTreasure::getSymbol() const {
    return 'T';
}

int BE_CellTreasure::getWinnerPlayer(BE_CellPlayer* p1, BE_CellPlayer* p2) {
    int returnValue = 0;
    if(rowT == p1->getRow() && colT == p1->getCol() && actualNodeT == p1->getActualNode()) {
        returnValue = 1;
    }
    else if(rowT == p2->getRow() && colT == p2->getCol() && actualNodeT == p2->getActualNode()) {
        returnValue = 2;
    }
    return returnValue;
}

int BE_CellTreasure::getRow() {
    return rowT;
}

int BE_CellTreasure::getCol() {
    return colT;
}

int BE_CellTreasure::getActualNode() {
    return actualNodeT;
}