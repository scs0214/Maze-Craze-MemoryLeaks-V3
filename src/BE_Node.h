#ifndef NODEBE_H
#define NODEBE_H

#include "BE_CellBase.h"
#include "BE_CellNormal.h"
#include "BE_CellPowered.h"
#include "BE_CellPlayer.h"

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
        vector<vector<BE_CellBase*>>& getMatrix();
        int getNodeID();
        BE_Node* getUp();
        BE_Node* getDown();
        BE_Node* getLeft();
        BE_Node* getRight();
        void setUp(BE_Node* neighbor);
        void setDown(BE_Node* neighbor);
        void setLeft(BE_Node* neighbor);
        void setRight(BE_Node* neighbor);
        void printConnections();
        bool checkVisited();
        void setVisited();
        void movePlayer(char direction);
};

#endif