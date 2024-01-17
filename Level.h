#ifndef LEVEL
#define LEVEL
/*
Constructor that takes in the array from the file processor that contains all the inputFile data and a boolean for the last level warp pipe
Simple destructor
getValueAtCoordinate and setValueAtCoordinate both do what their names suggest. 
getMarioCoordinate and setMarioCoordinate both do what their names suggest.
printLevel returns a string with the current level layout properly formatted.
getMaxCoordinate() returns the largest value mario can be at.
*/
#include <iostream>
#include <random>
#include <string>
#include "Coordinate.h"

class Level
{
    private:
        char** levelGrid; //2D array of characters
        int rowNums;
        int colNums;
        Coordinate* marioCoordinate;
        void placeSpecial(char specialChar); //handles placing boss, warp, and Mario

    public:
        Level(int* dataArray, bool lastLevel); //used to fill the field
        ~Level();
        char getValueAtCoordinate(int rowCoord, int colCoord);
        char setValueAtCoordinate(int rowCoord, int colCoord, char value);
        Coordinate* getMarioCoordinate();
        void setMarioCoordinate(Coordinate coord);
        std::string printLevel();
        int getMaxCoordinate();
};

#endif