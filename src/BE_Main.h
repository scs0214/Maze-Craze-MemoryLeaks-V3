#ifndef BEMAIN_H
#define BEMAIN_H

#include <iostream>
#include <vector>
#include <random>
#include "BE_Graph.h"
#include "BE_NodeMatrix.h"
#include "VALUES.h"
using namespace std;

class BE_Main {
    private:
        BE_NodeMatrix* nodeMatrix;

    public:
        BE_Main(BE_NodeMatrix* nm);
        BE_NodeMatrix* getNodeMatrix();
        void initializeNodeMatrix();
};

#endif