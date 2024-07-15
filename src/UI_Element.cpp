#include "UI_ImageLoader.h"
#include "UI_Element.h"
#include <iostream>
using namespace std;

void UI_Element::renderElement(SDL_Renderer* renderer, int row, int col, int num) { // 'num' represents the value of the image in the textures vector
    int sumX = (WINDOW_WIDTH - (NODE_MATRIX_SIZE*NODE_SIZE*CELL_SIZE)) / 2;
    int sumY = (WINDOW_HEIGHT - (NODE_MATRIX_SIZE*NODE_SIZE*CELL_SIZE)) / 2;;
    int positionX = sumX + (col * CELL_SIZE);
    int positionY = sumY + (row * CELL_SIZE);

    SDL_Rect innerCell = {positionX + BORDER_WIDTH, positionY + BORDER_WIDTH, 
                          CELL_SIZE - 2 * BORDER_WIDTH, CELL_SIZE - 2 * BORDER_WIDTH};  
    if (!imageLoader.textures.empty()) { 
        SDL_RenderCopy(renderer, imageLoader.textures[num], nullptr, &innerCell);
    }

    SDL_RenderPresent(renderer);
}