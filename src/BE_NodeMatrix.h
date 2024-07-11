#ifndef NODEMATRIXBE_H
#define NODEMATRIXBE_H

#include "BE_Node.h"

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
        BE_NodeMatrix(int r, int c);
        ~BE_NodeMatrix();
};

#endif