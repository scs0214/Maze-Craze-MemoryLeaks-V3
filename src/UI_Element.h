#ifndef ELEMENTUI_H
#define ELEMENTUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "VALUES.h"

using namespace std;

class UI_Element {
public:
    void renderElement(SDL_Renderer* renderer, int row, int col, int num);
};

#endif