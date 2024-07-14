#include "UI_Cell.h"
#include "UI_ImageLoader.h"
#include "UI_Treasure.h"
#include <iostream>
using namespace std;

void UI_Treasure::runWinScreen(SDL_Renderer* renderer, int winnerPlayer) {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, imageLoader.textures[10], nullptr, nullptr);

    SDL_RenderPresent(renderer);
}