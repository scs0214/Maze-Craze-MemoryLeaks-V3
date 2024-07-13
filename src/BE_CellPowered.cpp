#include "BE_CellPowered.h"

BE_CellPowered::BE_CellPowered(int r, int c, BE_Power* p) : row(r), col(c), power(p) {}

char BE_CellPowered::getSymbol() const {
    return power->getSymbol();
}