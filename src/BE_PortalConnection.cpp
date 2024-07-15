#include "BE_PortalConnection.h"

BE_PortalConnection::BE_PortalConnection(pair<BE_CellPortal*, BE_CellPortal*> p) : portalPair(p) {}

BE_CellPortal* BE_PortalConnection::getFirst() {
    return portalPair.first;
}
        
BE_CellPortal* BE_PortalConnection::getSecond() {
    return portalPair.second;
}