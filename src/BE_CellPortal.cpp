#include "BE_CellPortal.h"

BE_CellPortal::BE_CellPortal(int r, int c, int nv) : row(r), col(c) , nodeValue(nv){}

char BE_CellPortal::getSymbol() const {
    return 'P';
}

int BE_CellPortal::getRow() {
    return row;
}

int BE_CellPortal::getCol() {
    return col;
}

int BE_CellPortal::getNodeValue() {
    return nodeValue;
}