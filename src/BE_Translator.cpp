#include "BE_Translator.h"

int BE_Translator::symbolTranslator(char symbol) {
    int returnValue;
    if(symbol == 'N') {
        returnValue = 0;
    }
    else if(symbol == '1') {
        returnValue = 1;
    }
    if(symbol == '2') {
        returnValue = 2;
    }
    if(symbol == 'X') {
        returnValue = 4;
    }
    if(symbol == 'D') {
        returnValue = 5;
    }
    if(symbol == 'M') {
        returnValue = 6;
    }
    if(symbol == 'J') {
        returnValue = 7;
    }
    if(symbol == 'P') {
        returnValue = 8;
    }
    if(symbol == 'T') {
        returnValue = 9;
    }
    return returnValue;
}

void BE_Translator::saveMatrix(vector<vector<int>>& uiMatrix, BE_Node* node, int rowNM, int colNM) {
    int rowVB = rowNM*NODE_SIZE;
    int colVB = colNM*NODE_SIZE;
    for(int i = 0; i < NODE_SIZE; i++) {
        for(int j = 0; j < NODE_SIZE; j++) {
            char symbolBE = node->getMatrix()[i][j]->getSymbol();
            uiMatrix[rowVB+i][colVB+j] = symbolTranslator(symbolBE);
        }
    }
}

vector<vector<int>> BE_Translator::generateMatrixForUI(vector<vector<BE_Node*>> nodeMatrix) {
    vector<vector<int>> matrixForUI(NODE_MATRIX_SIZE*NODE_SIZE, vector<int>(NODE_MATRIX_SIZE*NODE_SIZE, 0));
    for(int i = 0; i < NODE_MATRIX_SIZE; i++) {
        for(int j = 0; j < NODE_MATRIX_SIZE; j++) {
            BE_Node* node = nodeMatrix[i][j];
            saveMatrix(matrixForUI, node, i, j);
        }
    }
    return matrixForUI;
}
