#include "UI_Cell.h"
#include "UI_ImageLoader.h"
#include "UI_Treasure.h"
#include <iostream>
using namespace std;

void UI_Treasure::runWinScreen(SDL_Renderer* renderer, int winnerPlayer) {
    SDL_RenderClear(renderer);

    int imgWidth = 550;
    int imgHeight = 125;
    SDL_Rect winPlayer;
    winPlayer.x = (WINDOW_WIDTH - imgWidth) / 2;
    winPlayer.y = ((WINDOW_HEIGHT - imgHeight) / 2) - 125;
    winPlayer.w = imgWidth;
    winPlayer.h = imgHeight;

    SDL_RenderCopy(renderer, imageLoader.textures[10], nullptr, nullptr);
    if(winnerPlayer == 1) {
        SDL_RenderCopy(renderer, imageLoader.textures[13], nullptr, &winPlayer);
    }
    else {
        SDL_RenderCopy(renderer, imageLoader.textures[14], nullptr, &winPlayer);
    }
    

    SDL_RenderPresent(renderer);
}