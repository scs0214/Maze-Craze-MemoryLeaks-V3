#ifndef POWERMINDCONTROL_H
#define POWERMINDCONTROL_H

#include "BE_Power.h"
using namespace std;

class BE_PowerMindControl : public BE_Power {
    public:
        char getSymbol();
        void immediateEffect();
};

#endif