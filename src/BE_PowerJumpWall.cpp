#include "BE_PowerJumpWall.h"

char BE_PowerJumpWall::getSymbol() {
    return 'J';
}

void BE_PowerJumpWall::immediateEffect(BE_Player* player) {
    player->getJumpWall();
}