#include "UI_Cell.h"
#include "UI_ImageLoader.h"
#include "UI_Player.h"
#include <iostream>
using namespace std;

UI_Player::UI_Player() :  jumpWallAmount(0) {}

char UI_Player::processInputP1(char& direction) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_w: direction = 'w'; break;
                case SDLK_s: direction = 's'; break;
                case SDLK_a: direction = 'a'; break;
                case SDLK_d: direction = 'd'; break;
                default: direction = 'x'; break;
            }
        }
    }
    return direction;
}

char UI_Player::processInputP2(char& direction) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: direction = 'w'; break;
                case SDLK_DOWN: direction = 's'; break;
                case SDLK_LEFT: direction = 'a'; break;
                case SDLK_RIGHT: direction = 'd'; break;
                default: direction = 'x'; break;
            }
        }
    }
    return direction;
}

void UI_Player::setJumpWallAmount(int jwAmountBackend) {
    this->jumpWallAmount = jwAmountBackend;
}

int UI_Player::getJumpWallAmount() const{
    return jumpWallAmount;
}