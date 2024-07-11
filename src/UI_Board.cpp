#include "UI_ImageLoader.h"
#include "UI_Board.h"
#include "UI_Cell.h"
#include "UI_Power.h"
#include "UI_Player.h"
#include <iostream>
using namespace std;

UI_Cell uiCell;
UI_Power uiPower;
UI_Player uiPlayer;

void UI_Board::renderBoard(SDL_Renderer* renderer, int** playerBoard, int rowAmount, int colAmount) {
    for (int i = 0; i < rowAmount; i++) {
       for (int j = 0; j < colAmount; j++) {
            uiCell.renderCell(renderer, i, j);
            if (playerBoard[i][j] > 3) { // Render powers
                uiPower.renderPower(renderer, i, j, playerBoard[i][j]);
            }
            else if (playerBoard[i][j] == 1 || playerBoard[i][j] == 2) {
                uiPlayer.renderPlayer(renderer, i, j, playerBoard[i][j]);
            }
        } 
    }

    SDL_RenderPresent(renderer);
}