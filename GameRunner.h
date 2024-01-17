#ifndef GAME_RUNNER
#define GAME_RUNNER
/*
Basic constructor and destructor
runGame() runs the game and the calls the fileProcessor to output to text
makeMove() controls mario's direction, and resetting the position where mario was
moveToCoord() moves mario to a given location and determines the action that should be taken at that position
fightEnemy is a basic combat with a Goomba or Koopa
fightBoss loops until Mario is out of lives or beats the boss. Determines boss behavior
printLevels() returns a string with all the levels
*/
#include <iostream>
#include <random>
#include <string>
#include "FileProcessor.h"
#include "Level.h"
#include "Coordinate.h"

class GameRunner{
    private:
        FileProcessor* processor;
        Level** levels; //pointer to an array of levels, each of which is a 2D array
        int currLevel; 
        int powerLevel;
        int numCoins; 
        int numLives;
        bool gameOver;
        bool bossDead;
        int numEnemiesKilled; //used for tracking if mario should gain a life or not
        std::string outputString;
        int moveToCoord(Coordinate coord);
        int fightEnemy(int percentWin, Coordinate coord);
        int fightBoss(Coordinate coord);

    public:
        GameRunner(FileProcessor* processor);
        ~GameRunner();
        void makeMove();
        void runGame();
        std::string printLevels();
            
};

#endif