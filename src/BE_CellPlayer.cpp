#include "BE_CellPlayer.h"

BE_CellPlayer::BE_CellPlayer(int r, int c, int an, BE_Player* p) : row(r), col(c) , actualNode(an), player(p) {}

int BE_CellPlayer::getRow() {
    return row;
}

int BE_CellPlayer::getCol() {
    return col;
}

int BE_CellPlayer::getActualNode() {
    return actualNode;
}

BE_Player* BE_CellPlayer::getPlayer() {
    return player;
}

void BE_CellPlayer::setRow(int newValue) {
    row = newValue;
}

void BE_CellPlayer::setCol(int newValue) {
    col = newValue;
}

void BE_CellPlayer::setActualNode(int newValue) {
    actualNode = newValue;
}

char BE_CellPlayer::getSymbol() const {
    char symbol = '0' + player->getPlayerID();
    return symbol;
}