#ifndef CELLUI_H
#define CELLUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "VALUES.h"

using namespace std;

class UI_Cell {
public:
    UI_Cell();
    ~UI_Cell();
    void renderCell(SDL_Renderer* renderer, int row, int col);

private:
    SDL_Texture* texture;
    int positionX;
    int positionY;
};

#endif