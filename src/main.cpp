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

        GameState currentGameState = TITLE_SCREEN; // Declares variables needed by the main program to create loops and render the different game stages
        SDL_Renderer* renderer = uiMain.getRenderer();
        SDL_Event event;
        bool running = true;
        char direction = 'x'; 
        int turnManager = 1;
        int maxVNP = NODE_SIZE-1; // Max value for Node Pos
        int maxVN = NODE_MATRIX_SIZE*NODE_MATRIX_SIZE; // Max value for Node
        BE_Player* p1 = new BE_Player(1);
        BE_Player* p2 = new BE_Player(2);
        BE_CellPlayer* player1 = new BE_CellPlayer(0, 0, 1, p1);
        BE_CellPlayer* player2 = new BE_CellPlayer(maxVNP, maxVNP, maxVN, p2);
        beMain.initializeNodeMatrix(player1, player2);

        while (running) {
            // Renderer Section (renders the different GameStates)
            if (currentGameState == TITLE_SCREEN) {
                uiTitleScreen.runTitleScreen(renderer);
            } else if (currentGameState == MAIN_PROGRAM) {
                // Initialize Backend
                uiMain.runMainProgram(renderer, beTranslator.generateMatrixForUI(beMain.getNodeMatrix()->getMatrix()));
            }
            else if (currentGameState == WIN_SCREEN) {
                uiWinScreen.runWinScreen(renderer, 1);
            }
        
            // Event Handler Section (handles different events to switch between GameStates)
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }

                if (currentGameState == TITLE_SCREEN) {
                    if (uiTitleScreen.buttonClick(event)) {
                        currentGameState = MAIN_PROGRAM;
                    }
                } 
                
                else if (currentGameState == MAIN_PROGRAM) {
                    bool moveCompleted = false;
                    while(!moveCompleted) {
                        if (turnManager == 1) {
                            direction = uiPlayer.processInputP1(direction);
                            moveCompleted = beMain.movePlayer(player1, direction);
                        }
                        else if (turnManager == 2) {
                            direction = uiPlayer.processInputP2(direction);
                            moveCompleted = beMain.movePlayer(player2, direction);
                        }
                        direction = 'x';
                        // Backend changes
                    }
                    turnManager = beMain.turnChange(turnManager);          
                }

                else if (currentGameState == WIN_SCREEN) {
                    SDL_Delay(5000);
                    running = false;
                }
            }
        }
        // All SDL processes are closed
    }

    return 0;
}
