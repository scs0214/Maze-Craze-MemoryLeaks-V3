#ifndef GRAPHBE_H
#define GRAPHBE_H

#include "BE_NodeMatrix.h"
#include "VALUES.h"

#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime> 
#include <random>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class BE_Graph {
    private:
        bool isValid(int row, int col, const vector<vector<BE_Node*>>& matrix);

    public:
        void connectionUD(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol);
        void connectionDU(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol);
        void connectionLR(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol);
        void connectionRL(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol, int newRow, int newCol);
        void DFS(vector<vector<BE_Node*>>& matrix, int startRow, int startCol);
        void BFS(vector<vector<BE_Node*>>& matrix, int startRow, int startCol);
        int findMissingConnections(vector<vector<BE_Node*>>& matrix, int currentRow, int currentCol);
        bool isValidForExtra(int oldRow, int oldCol, int newRow, int newCol, const vector<vector<BE_Node*>>& matrix);
        void connectNodeForExtra(vector<vector<BE_Node*>>& matrix, int currentRow, int currentColumn);
        void addExtraConnections(vector<vector<BE_Node*>>& matrix);
};

#endif