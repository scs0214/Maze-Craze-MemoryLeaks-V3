#ifndef TRANSLATORBE_H
#define TRANSLATORBE_H

#include "BE_NodeMatrix.h"
#include "BE_NodeMatrix.h"
#include <vector>
using namespace std;

class BE_Translator {
    public:
        int symbolTranslator(char symbol);
        void saveMatrix(vector<vector<int>>& uiMatrix, BE_Node* node, int rowNM, int colNM);
        vector<vector<int>> generateMatrixForUI(vector<vector<BE_Node*>> nodeMatrix);
};

#endif