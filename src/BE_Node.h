#ifndef NODEBE_H
#define NODEBE_H

#include "BE_CellBase.h"
#include "BE_CellNormal.h"
#include "BE_CellPowered.h"

#include <vector>
using namespace std;

class BE_Node {
    private:
        int ID;
        int rowAmount;
        int colAmount;
        vector<vector<BE_CellBase*>> matrix;
        BE_Node* up;
        BE_Node* down;
        BE_Node* left;
        BE_Node* right;
        bool visited;
        
    public:
        BE_Node(int id, int r, int c);
        ~BE_Node();
        void fillMatrix();
        void printMatrix();
        void movePlayer(char direction);
};

#endif