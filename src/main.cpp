#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "BE_Main.h"
#include "BE_Player.h"
#include "BE_NodeMatrix.h"
#include "BE_Translator.h"
#include "UI_MAIN.h"
#include "UI_TitleScreen.h"
#include "UI_Player.h"
#include "UI_Treasure.h"

#include <thread>
#include <chrono>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    enum GameState {
        TITLE_SCREEN, MAIN_PROGRAM, WIN_SCREEN
    };

    {
        BE_Translator beTranslator;
        UI_MAIN uiMain;
        UI_TitleScreen uiTitleScreen;
        UI_Treasure uiWinScreen;
        UI_Player uiPlayer;
        BE_NodeMatrix* nodeMatrix = new BE_NodeMatrix;
        BE_Main beMain(nodeMatrix);

        if (!uiMain.initialize()) {
            cerr << "Failed to initialize UI_MAIN." << endl;
            return -1;
        }
        if (!uiMain.checkIfMazeFits()) { // Closes program if the maze doesn't fit in the window created
            cerr << "The maze's size for the UI is bigger than the window generated." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            return -1;
        }

        GameState currentGameState = TITLE_SCREEN; // Declares variables needed by the main program to create loops and render the different game stages
        SDL_Renderer* renderer = uiMain.getRenderer();
        SDL_Event event;
        bool running = true;
        bool getDoubleTurn = false;
        bool getMindControl = false;
        bool mindControlUsed = false;
        char direction = 'x'; 
        int playerInput = 1;
        int playerToMove = 1;
        int turnManager = 1;
        int winnerPlayer = 0;

        int maxVNP = NODE_SIZE-1; // Max value for Node Pos
        int maxVN = NODE_MATRIX_SIZE*NODE_MATRIX_SIZE; // Max value for Node
        BE_Player* p1 = new BE_Player(1);
        BE_Player* p2 = new BE_Player(2);
        BE_CellPlayer* player1 = new BE_CellPlayer(0, 0, 1, p1);
        BE_CellPlayer* player2 = new BE_CellPlayer(maxVNP, maxVNP, maxVN, p2);
        BE_CellTreasure* treasure;
        beMain.initializeNodeMatrix(player1, player2);
        treasure = nodeMatrix->initializeTreasure();

        while (running) {
            // Renderer Section (renders the different GameStates)
            if (currentGameState == TITLE_SCREEN) {
                uiTitleScreen.runTitleScreen(renderer);
            } 
            if (currentGameState == MAIN_PROGRAM) {
                uiMain.runMainProgram(renderer, beTranslator.generateMatrixForUI(beMain.getNodeMatrix()->getMatrix()));
                SDL_Delay(1000);

                winnerPlayer = treasure->getWinnerPlayer(player1, player2);
                if (winnerPlayer != 0) {
                    currentGameState = WIN_SCREEN;
                }
            }
            if (currentGameState == WIN_SCREEN) {
                uiWinScreen.runWinScreen(renderer, winnerPlayer);
            }
        
            // Event Handler Section (handles different events to switch between GameStates excepting WIN_SCREEN)
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }

                if (currentGameState == TITLE_SCREEN) {
                    if (uiTitleScreen.buttonClick(event)) {
                        currentGameState = MAIN_PROGRAM;
                    }
                } 
                
                else if (currentGameState == MAIN_PROGRAM) { // Manages which player makes the input, which player is moved and the use of Double Turn and Mind Control powers
                    bool moveCompleted = false;
                    while(!moveCompleted) {
                        if (playerInput == 1) {
                            uiPlayer.processInputP1(direction);
                        }
                        else if (playerInput == 2) {
                            uiPlayer.processInputP2(direction);
                        }

                        if(playerToMove == 1) {
                            moveCompleted = beMain.movePlayer(player1, direction, getDoubleTurn, getMindControl);
                        }
                        else if(playerToMove == 2) {
                            moveCompleted = beMain.movePlayer(player2, direction, getDoubleTurn, getMindControl);
                        }
                        direction = 'x';
                    }

                    if (getDoubleTurn) {
                        getDoubleTurn = false; 
                    }
                    else if(getMindControl) {
                        turnManager = beMain.turnChange(turnManager);
                        if (playerToMove == 1) {
                            playerToMove = 2;
                        }
                        else {
                            playerToMove = 1;
                        }
                        getMindControl = false;
                    }
                    else {
                        turnManager = beMain.turnChange(turnManager);
                        playerInput = turnManager;
                        playerToMove = turnManager;  
                    }
                }

                else if (currentGameState == WIN_SCREEN) {
                    SDL_Delay(3000);
                    running = false;
                }
            }
        }
        // All SDL processes are closed
    }

    return 0;
}
