#include "UI_ImageLoader.h"
#include "UI_Element.h"
#include <iostream>
using namespace std;

void UI_Element::renderElement(SDL_Renderer* renderer, int row, int col, int num) { // Añadir 'int num' a los argumentos si existe una imagen para la celda
    SDL_Rect innerCell = {col * CELL_SIZE + BORDER_WIDTH, row * CELL_SIZE + BORDER_WIDTH, 
                          CELL_SIZE - 2 * BORDER_WIDTH, CELL_SIZE - 2 * BORDER_WIDTH};  
    if (!imageLoader.textures.empty()) { 
        SDL_RenderCopy(renderer, imageLoader.textures[num], nullptr, &innerCell);
    }

    SDL_RenderPresent(renderer);
}