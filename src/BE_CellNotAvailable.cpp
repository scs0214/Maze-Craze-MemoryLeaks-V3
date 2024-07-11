#include "BE_CellNotAvailable.h"

BE_CellNotAvailable::BE_CellNotAvailable(int r, int c) : row(r), col(c) {}

char BE_CellNotAvailable::getSymbol() const {
    return 'X';
}