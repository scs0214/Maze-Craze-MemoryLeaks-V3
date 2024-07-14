#include "UI_ImageLoader.h"
#include "UI_Cell.h"
#include <iostream>
using namespace std;

UI_Cell::UI_Cell() : texture(nullptr), positionX(0), positionY(0) {}

UI_Cell::~UI_Cell() {
    if (texture) SDL_DestroyTexture(texture);
    SDL_Quit();
}

void UI_Cell::renderCell(SDL_Renderer* renderer, int row, int col) { // Añadir 'int num' a los argumentos si existe una imagen para la celda
    int sumX = (WINDOW_WIDTH - (NODE_MATRIX_SIZE*NODE_SIZE*CELL_SIZE)) / 2;
    int sumY = (WINDOW_HEIGHT - (NODE_MATRIX_SIZE*NODE_SIZE*CELL_SIZE)) / 2;;
    int positionX = sumX + (col * CELL_SIZE);
    int positionY = sumY + (row * CELL_SIZE);
    SDL_Color borderColor = {0, 0, 0, 255};
    SDL_Color fillColor = {255, 255, 255, 255};

    SDL_Rect cell = {positionX, positionY, CELL_SIZE, CELL_SIZE};
            
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderFillRect(renderer, &cell);
            
    SDL_Rect innerCell = {positionX + BORDER_WIDTH, positionY + BORDER_WIDTH, 
                          CELL_SIZE - 2 * BORDER_WIDTH, CELL_SIZE - 2 * BORDER_WIDTH};
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &innerCell);
            
    if (!imageLoader.textures.empty()) { 
        SDL_RenderCopy(renderer, imageLoader.textures[3], nullptr, &innerCell);
    }

    SDL_RenderPresent(renderer);
}