#ifndef NODEMATRIXBE_H
#define NODEMATRIXBE_H

#include "BE_Node.h"
#include "VALUES.h"

#include <stack>
#include <cstdlib>
#include <ctime> 
#include <vector>
using namespace std;

class BE_NodeMatrix {
    private:
        int rowAmount;
        int colAmount;
        vector<vector<BE_Node*>> matrix;
        char generateRandomDirection();
        
    public:
        BE_NodeMatrix();
        ~BE_NodeMatrix();
        void initializeNodeMatrix();
        vector<vector<BE_Node*>>& getMatrix();
        void printNodeMatrix();
};

#endif