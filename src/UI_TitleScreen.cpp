#include "UI_ImageLoader.h"
#include "UI_TitleScreen.h"
#include <iostream>
using namespace std;

int buttonWidth = 400;
int buttonHeight = 75;
int posX = (WINDOW_WIDTH-buttonWidth)/2;
int posY = WINDOW_HEIGHT-150;

void UI_TitleScreen::runTitleScreen(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, imageLoader.textures[0], nullptr, nullptr);

    SDL_Rect playButton = {posX, posY, buttonWidth, buttonHeight};
    SDL_RenderCopy(renderer, imageLoader.textures[12], nullptr, &playButton);

    SDL_RenderPresent(renderer);
}

bool isPointInRect(int x, int y, SDL_Rect rect) {
    return x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h;
}

bool UI_TitleScreen::buttonClick(SDL_Event& event) {
    bool returnValue = false;

    SDL_Rect playButton = {posX, posY, buttonWidth, buttonHeight};

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (isPointInRect(x, y, playButton)) {
            returnValue = true;
        }
    }
    return returnValue;
}


