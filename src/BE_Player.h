#ifndef PLAYERBE_H
#define PLAYERBE_H

using namespace std;

class BE_Player {
    public:
        BE_Player(int p);
        int getPlayerID();
        int getJumpWallAmount();
        void getJumpWall();
        void useJumpWall();

    private:
        int playerID;
        int jumpWallAmount;
};

#endif