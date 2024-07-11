#include "BE_Player.h"
#include <iostream>

BE_Player::BE_Player(char p, int n) : playerID(p), nodeID(n), jumpWallAmount(0) {}

int BE_Player::getJumpWallAmount() {
    return jumpWallAmount;
}

void BE_Player::getJumpWall() {
    jumpWallAmount++;
}

void BE_Player::useJumpWall() {
    jumpWallAmount--;
}