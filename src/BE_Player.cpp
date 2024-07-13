#include "BE_Player.h"
#include <iostream>

BE_Player::BE_Player(int p) : playerID(p), jumpWallAmount(0) {}

int BE_Player::getPlayerID() {
    return playerID;
}


int BE_Player::getJumpWallAmount() {
    return jumpWallAmount;
}

void BE_Player::getJumpWall() {
    jumpWallAmount++;
}

void BE_Player::useJumpWall() {
    jumpWallAmount--;
}