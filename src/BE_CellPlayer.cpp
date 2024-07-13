#include "BE_CellPlayer.h"

BE_CellPlayer::BE_CellPlayer(int r, int c, int an, BE_Player* p) : row(r), col(c) , actualNode(an), player(p) {}

char BE_CellPlayer::getSymbol() const {
    char symbol = '0' + player->getPlayerID();
    return symbol;
}