#include "GameRunner.h"

GameRunner::GameRunner(FileProcessor* inputProcessor){
    processor = inputProcessor;
    int numLevels = processor->getValueAtPos(0);
    numLives = processor->getValueAtPos(2);
    int currLevel = 0;
    numEnemiesKilled = 0;
    bossDead = false;
    gameOver = false;
    levels = new Level*[numLevels];
    for(int i = 0; i < processor->getValueAtPos(0); i++){ //grabs the number of levels and loops until then
        if(i == processor->getValueAtPos(0) - 1){
            levels[i] = new Level(processor->getValueArray(), true);
        }else{
            levels[i] = new Level(processor->getValueArray(), false); //infinite loop here.
        }
    }
}

GameRunner::~GameRunner(){
    delete[] levels;
}


void GameRunner::makeMove(){
    // gameOver = false; //why is this here?
    int moveDir = rand() % 4; //0 is up, 1 is down, 2 is right, 3 is left
    int marioCurrCol = levels[currLevel]->getMarioCoordinate()->colCoord;
    int marioCurrRow = levels[currLevel]->getMarioCoordinate()->rowCoord;

    Coordinate tempCoord; //represents his new position
    if(moveDir == 0){ //move up
        outputString += "Mario will move up. \n";
        if(marioCurrRow < 1) {
            tempCoord.rowCoord = levels[currLevel]->getMaxCoordinate() - 1;
        } else {
            tempCoord.rowCoord = marioCurrRow - 1;
        }
        tempCoord.colCoord = marioCurrCol;
    } else if(moveDir == 1){ //move down
        outputString += "Mario will move down. \n";
        if(marioCurrRow == levels[currLevel]->getMaxCoordinate() - 1){
            tempCoord.rowCoord = 0;
        } else{
            tempCoord.rowCoord = marioCurrRow + 1;
        }
        tempCoord.colCoord = marioCurrCol;

    } else if(moveDir == 2){ //right
        outputString += "Mario will move right. \n";
        if(marioCurrCol == levels[currLevel]->getMaxCoordinate() - 1){
            tempCoord.colCoord = 0;
        } else{
            tempCoord.colCoord = marioCurrCol + 1;
        }
        tempCoord.rowCoord = marioCurrRow;

    }else if(moveDir == 3){ //left
        outputString += "Mario will move left. \n"; 
        if(marioCurrCol < 1){
            tempCoord.colCoord = levels[currLevel]->getMaxCoordinate() - 1; 
        } else{
            tempCoord.colCoord = marioCurrCol - 1;
        }
        tempCoord.rowCoord = marioCurrRow;

    } else {
        std::cout << "error occured in moving mario. Line 98 in GameRunner" << std::endl;
        exit;
    }

    //deals with the return of mario
    int resetSquare = moveToCoord(tempCoord); //adds his interaction to the output string. tempCoord represents his new position
    if(1 == resetSquare){
        levels[currLevel]->setValueAtCoordinate(marioCurrRow, marioCurrCol, 'X'); 
    }

    if((numCoins % 20 == 0) && (numCoins > 0)){
        numLives++;
    }
}

// returns 1 if it should reset the old coordinate, 0 if it should not, and -1 if it errors
int GameRunner::moveToCoord(Coordinate coord){ 
    //coord is mario's new position
    char atPos = levels[currLevel]->getValueAtCoordinate(coord.rowCoord, coord.colCoord);
    if ('X' == atPos)
    { // if nothing is there, set old position to X and new position to H
        levels[currLevel]->setMarioCoordinate(coord);
        outputString += "Mario has moved to an empty square. ";
        return 1;
    } else if('G' == atPos){ //Goomba - 80% chance to win
        return fightEnemy(80, coord);

    } else if('K' == atPos){ //Koopa - 65% chance to win
        return fightEnemy(65, coord);

    } else if('C' == atPos){ //adds coin to wallet
        numCoins++;
        levels[currLevel]->setMarioCoordinate(coord);
        outputString += "Mario has collected a coin. ";
        return 1;
    } else if('M' == atPos){ //power level increases by 1 or stays at 2 if he is already at 2
        if(powerLevel < 2){
            powerLevel++;
        }
        levels[currLevel]->setMarioCoordinate(coord);
        outputString += "Mario has collected a mushroom. Power Level Up! ";
        return 1;
    } else if('W' == atPos){ //warp to next level
        if(currLevel < processor->getValueAtPos(0) - 1){ 
            currLevel++;
            bossDead = false;
            outputString += "Mario has warped. ";
        }
        return 1;
    } else if('B' == atPos){ //Boss - 50% chance to win, moves to next level or wins game. Loss is pl - 2, pl1 or 0 makes mario lose a life
        return fightBoss(coord); 

    } else {
        std::cout << "an error has occured in moving mario to the desired coordinates." << std::endl;
        return -1;
    }
}

int GameRunner::fightEnemy(int percentWin, Coordinate coord)
{ // fight a regular enemy
    int randNum = rand() % 100 + 1;
    if (randNum <= percentWin)
    {
        levels[currLevel]->setMarioCoordinate(coord);
        outputString += "Mario has fought a regular enemy and won. ";
        numEnemiesKilled++;
        return 1;
    }
    else
    {
        if (powerLevel > 0)
        {
            powerLevel--;
        }
        else
        {
            if (numLives == 0)
            {
                outputString += "Mario has fought a regular enemy, lost, and is out of lives. Game Over.";
                gameOver = true;
            }
            else
            {
                numLives--;
                outputString += "Mario has fought a regular enemy and lost. ";
                numEnemiesKilled = 0;
            }
        }
        return 0;
    }
}

int GameRunner::fightBoss(Coordinate coord){
    int numLoops = 0;
    while(true && numLoops < 10000){ //again another mediocre patch. I am stunned by this infinite loop
        numLoops++;
        int randNum = rand() % 100 + 1;
        if (randNum <= 50) //if he wins
        {
            levels[currLevel]->setMarioCoordinate(coord); //move him to the boss' position
            if (currLevel < processor->getValueAtPos(0) - 1) //if its not the last level
            {
                currLevel++; //increment level
                outputString += "Mario has fought a boss and won. Onto the next level. ";
                numEnemiesKilled++;
            }
            else //it is the last level
            {
                gameOver = true; //ends loop/game I hope
                outputString += "Mario has fought a boss and saved the princess! Good Game! "; //ONLY WORKS IF HE FIGHTS THE BOSS ONCE
            }
            break;
        }
        else
        {
            if (powerLevel > 1) //if he has enough power to subtract
            {
                powerLevel = powerLevel - 2;
            }
            else //if he doesnt
            {
                if (numLives == 0) //if he has no lives left
                {
                    outputString += "Mario has died to a Boss and is out of lives. Game Over.";
                    gameOver = true; //ends the loop
                    break;
                }
                else
                {
                    numLives--; //decrements lives
                    outputString += "Mario has fought a boss and lost. Mario will fight the boss again;. ";
                    numEnemiesKilled = 0; //should make it repeat
                }
            }
        }
    }

    // returns 1 if it should reset the old coordinate, 0 if it should not, and -1 if it errors
    return 1;
}

void GameRunner::runGame(){
    std::cout << "Starting Game:" << std::endl;
    outputString += "Levels are zero indexed. The level above each paragraph of text is before he does the move outlined in the text. \nLevel 0 Layout: \n";
    outputString += levels[0]->printLevel();
    outputString += "=============\n";

    while ((currLevel < processor->getValueAtPos(0)) && !(gameOver))
    {
        std::cout << currLevel << "   " << gameOver << std::endl;
        outputString += "\n" + levels[currLevel]->printLevel();
        outputString += "Mario is at: " + std::to_string(levels[currLevel]->getMarioCoordinate()->colCoord) + ", " + 
            std::to_string(levels[currLevel]->getMarioCoordinate()->rowCoord) + ".";
        outputString += "   Current Level: " + std::to_string(currLevel) + ".   Current Lives: " + std::to_string(numLives) +
        ".   Current Coins: " + std::to_string(numCoins) + ".   Current Power Level: " + std::to_string(powerLevel);
        makeMove(); //infinite loops somewhere in here but it doesnt make sense 
        outputString += "\n=============\n";
    }
    outputString += "Final Board Layout: \n" + levels[currLevel]->printLevel();

    //std::cout << outputString << std::endl; // Uncomment if you want to print the game

    processor->outputToText(outputString);
    std::cout << "Game is done." << std::endl;
}

std::string GameRunner::printLevels(){ 
    std::string levelString = std::to_string(processor->getValueAtPos(0));
    for(int i = 0; i < processor->getValueAtPos(0); i++){ 
        levelString += levels[i]->printLevel() + "\n";
    }
    return levelString;
}
