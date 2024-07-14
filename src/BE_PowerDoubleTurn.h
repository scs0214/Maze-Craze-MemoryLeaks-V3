#ifndef POWERDOUBLETURN_H
#define POWERDOUBLETURN_H

#include "BE_Power.h"
using namespace std;

class BE_PowerDoubleTurn : public BE_Power {
    public:
        char getSymbol();
        void immediateEffect();
};

#endif