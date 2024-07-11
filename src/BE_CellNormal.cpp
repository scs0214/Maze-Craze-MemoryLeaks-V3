#include "BE_CellNormal.h"

BE_CellNormal::BE_CellNormal(int r, int c) : row(r), col(c) {}

char BE_CellNormal::getSymbol() const {
    return 'N';
}