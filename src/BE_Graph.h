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
        void DFS(vector<vector<BE_Node*>>& matrix, int startRow, int startCol);
        void BFS(vector<vector<BE_Node*>>& matrix, int startRow, int startCol);
};

#endif