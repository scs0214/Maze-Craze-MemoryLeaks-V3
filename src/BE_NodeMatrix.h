#ifndef NODEMATRIXBE_H
#define NODEMATRIXBE_H

#include "BE_Node.h"
#include "BE_CellNotAvailable.h"
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
        
    public:
        BE_NodeMatrix();
        ~BE_NodeMatrix();
        vector<vector<BE_Node*>>& getMatrix();
        void initializeNodeMatrix();
        void addEdgesToCorners();
        void fillHorizontalEdges(int rowNM, int colNM, int rowValue);
        void fillVerticalEdges(int rowNM, int colNM, int columnValue);
        void addLinearEdges();
        void printNodeMatrix();
        BE_Node* getNode(int idSearch);
        void movePlayer(char direction, int newRow, int newCol, BE_Node* targetNode, BE_CellPlayer* cellPlayer);
        bool checkMovePossible(char direction, BE_CellPlayer* cellPlayer);
};

#endif