//
//  Level.h
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#ifndef __eljoc__Level__
#define __eljoc__Level__

#include <iostream>

#include "cocos2d.h"


using namespace std;
using namespace cocos2d;

class Statistics;

class Level
{
private:
    Statistics* statistics;
    
    int levelNumber;            // level number
    Size boardSize;             // size of the board (8x8 10x10 etc.)
    int numberOfPiecesToAdd;    // number of pieces to add to the board each delay
    int numberOfColorsToAdd;    // number of piece's types.
    double delayMs;             // delay in ms to add a new piece in the board.
    double delayDecrement;      // delay decrement slope -> delay becomes shortes pieces are added faster -> increase difficulty
    vector<Point> stones;       // List of the stones' positions in the board
    vector<Point> glasses;      // List of the glasses' positions in the board
    
    // Level goals
    
    unsigned int points;            // Number of point to do.
    double elapsedTimeMs;           // Ms seconds to play
    unsigned int numberOfPieces;    // Number of pieces to add in the board.
    unsigned int numberOfCombos;    // Number of combos of any type to do.
    unsigned int numberOfChains;    // Number of chains of any type to do.
    vector<unsigned int> piecesCounter; // Number of piece to add by color
    vector<unsigned int> combosCounter; // Number of combos by length
    vector<unsigned int> chainsCounter; // Number of chains by length
    
    
    void setDefaultValues();
    static bool ConfigKeyExists(ValueMap map, string key);
    static Point getPiecePosition(Value stone, Size boardSize);
public:
    static Level* createFromFile(const std::string &filename);
    static Level* createFromLevelNumber(const int levelnumber);
    
    Level();
    bool IsLevelDone();
    
    int getLevelNumber() { return this->levelNumber; }
    vector<Point> getStones() { return this->stones; }
    vector<Point> getGlasses() { return this->glasses; }
    Statistics* getStats() { return this->statistics; }
    Size getBoardSize() { return this->boardSize; }
    int getNumberOfPiecesToAdd() { return this->numberOfPiecesToAdd; }
    int getNumberOfColorsToAdd() { return this->numberOfColorsToAdd; }
    double getPieceDelay();
    
};
#endif /* defined(__eljoc__Level__) */
