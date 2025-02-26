#ifndef UIMAIN_H
#define UIMAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "VALUES.h"
using namespace std;

class UI_MAIN {
public:
    UI_MAIN();
    ~UI_MAIN();
    bool initialize();
    SDL_Renderer* getRenderer() const;
    bool checkIfMazeFits();
    void runMainProgram(SDL_Renderer* renderer, vector<vector<int>> playerBoard);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif