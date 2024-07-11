#ifndef CELLBE_H
#define CELLBE_H

#include <iostream>
using namespace std;

class BE_CellBase {
    public:
        virtual char getSymbol() const = 0;
};

#endif