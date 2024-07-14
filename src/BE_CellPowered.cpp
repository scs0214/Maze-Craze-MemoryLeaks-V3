#include "BE_CellPowered.h"

BE_CellPowered::BE_CellPowered(BE_Power* p) : power(p) {}

char BE_CellPowered::getSymbol() const {
    return power->getSymbol();
}