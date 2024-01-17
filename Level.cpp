#include "Level.h"

Level::Level(int *dataArray, bool lastLevel)
{
    colNums = dataArray[1];
    rowNums = dataArray[1];

    levelGrid = new char *[dataArray[1]]; // build cols

    for (int i = 0; i < dataArray[1]; i++)
    {
        levelGrid[i] = new char[dataArray[1]]; // build rows
    }

    for (int i = 0; i < dataArray[1]; i++)
    {
        for (int k = 0; k < dataArray[1]; k++)
        {
            int randNum = rand() % 100 + 1;
            if (randNum < dataArray[3])
            { // 1-20 - coins
                levelGrid[i][k] = 'C';
            }
            else if (randNum < (dataArray[3] + dataArray[4]))
            { // 20 < 20 + 20 - nothing
                levelGrid[i][k] = 'X';
            }
            else if (randNum < (dataArray[3] + dataArray[4] + dataArray[5]))
            { // 40 < 60 - goombas
                levelGrid[i][k] = 'G';
            }
            else if (randNum < (dataArray[3] + dataArray[4] + dataArray[5] + dataArray[6]))
            { // 60 < 80 - koopas
                levelGrid[i][k] = 'K';
            }
            else
            { // mushrooms
                levelGrid[i][k] = 'M';
            }
        }
    }
    // places hero, boss, and warp
    placeSpecial('H');
    placeSpecial('B');
    if(!(lastLevel)){
        placeSpecial('W');
    }
}


void Level::placeSpecial(char specialChar){
    int randCol = rand() % colNums;
    int randRow = rand() % rowNums;
    char randChar = levelGrid[randRow][randCol];
    std::cout << printLevel() << std::endl;

    int numLoops = 0;
    while (randChar != 'B' && randChar != 'W' && numLoops < 10000) //numloops is a patch for an infinite loop problem.
    {
        randCol = rand() % colNums;
        randRow = rand() % rowNums;
        randChar = levelGrid[randRow][randCol];
        numLoops++;
    }
    
    levelGrid[randRow][randCol] = specialChar;


    if('H' == specialChar){
        marioCoordinate = new Coordinate();
        marioCoordinate->rowCoord = randRow;
        marioCoordinate->colCoord = randCol;
    }
}

Level::~Level()
{
    for(int i = 0; i < sizeof(levelGrid[0]); i++){
        delete[] levelGrid[i];
    }
    delete[] levelGrid;
    delete marioCoordinate;
}

char Level::getValueAtCoordinate(int rowCoord, int colCoord)
{
    return levelGrid[rowCoord][colCoord];
}

char Level::setValueAtCoordinate(int rowCoord, int colCoord, char value)
{
    levelGrid[rowCoord][colCoord] = value;
}

Coordinate* Level::getMarioCoordinate(){
    return marioCoordinate;
}

void Level::setMarioCoordinate(Coordinate coord){
    marioCoordinate->rowCoord = coord.rowCoord;
    marioCoordinate->colCoord = coord.colCoord;
    levelGrid[marioCoordinate->rowCoord][marioCoordinate->colCoord] = 'H';
}

std::string Level::printLevel(){
    std::string levelText;
    for(int i = 0; i < rowNums; i++){
        for(int j = 0; j < colNums; j++){
            levelText += levelGrid[i][j];
        }
        levelText += "\n";
    }
    return levelText;
}

int Level::getMaxCoordinate(){
    return rowNums;
}
