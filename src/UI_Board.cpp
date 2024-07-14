#include "UI_Board.h"
#include "UI_Cell.h"
#include "UI_Element.h"
#include <iostream>
using namespace std;

UI_Cell uiCell;
UI_Element uiElement;

void UI_Board::renderBoard(SDL_Renderer* renderer, vector<vector<int>> playerBoard) {
    for (int i = 0; i < NODE_MATRIX_SIZE*NODE_SIZE; i++) {
       for (int j = 0; j < NODE_MATRIX_SIZE*NODE_SIZE; j++) {
            uiCell.renderCell(renderer, i, j);
            if (playerBoard[i][j] != 0) { // Render elements
                uiElement.renderElement(renderer, i, j, playerBoard[i][j]);
            }
        } 
    }

    SDL_RenderPresent(renderer);
}