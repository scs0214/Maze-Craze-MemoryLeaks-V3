#ifndef BOARDUI_H
#define BOARDUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
using namespace std;

class UI_Board {
public:
    void renderBoard(SDL_Renderer* renderer, vector<vector<int>> playerBoard);
};

#endif