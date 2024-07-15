#ifndef PORTALCONNECTIONBE_H
#define PORTALCONNECTIONBE_H

#include "BE_CellPortal.h"
#include <utility>
using namespace std;

class BE_PortalConnection {
    private:
        pair<BE_CellPortal*, BE_CellPortal*> portalPair;

    public:
        BE_PortalConnection(pair<BE_CellPortal*, BE_CellPortal*> p);
        BE_CellPortal* getFirst();
        BE_CellPortal* getSecond();
};

#endif