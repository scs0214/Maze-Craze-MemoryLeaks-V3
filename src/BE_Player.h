#ifndef PLAYERBE_H
#define PLAYERBE_H

using namespace std;

class BE_Player {
    public:
        BE_Player(char p, int n);
        int getJumpWallAmount();
        void getJumpWall();
        void useJumpWall();

    private:
        char playerID;
        int nodeID;
        int jumpWallAmount;
};

#endif