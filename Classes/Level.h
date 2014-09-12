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
    
    int levelNumber;
    Size boardSize;         // size of the board
    int numberOfPieces;     // number of pieces to add to the board each delay
    int numberOfTypes;      // number of piece's types.
    double delayMs;         // delay in ms to add a new piece in the board.
    double delayDecrement;
    vector<Point> stones;
    vector<Point> glasses;
    // Level goals
    unsigned int points; // Number of point to do.
    
    int stonePercent;
    int icePercent;
    int firePercent;
    
   /* double elapsedTimeMs;
    unsigned int numberOfPieces;
    unsigned int numberOfCombos;
    unsigned int numberOfChains;
    vector<unsigned int> piecesCounter;
    vector<unsigned int> combosCounter;
    vector<unsigned int> chainsCounter;*/
    
    void setDefaultValues();
    static bool ConfigKeyExists(ValueMap map, string key);
    static Point getPiecePosition(Value stone, Size boardSize);
public:
    static Level* createFromFile(const std::string &filename);
    static Level* createFromLevelNumber(const int levelnumber);
    
    Level();
    void start();
    void stop();
    bool IsLevelDone();
    
    int getLevelNumber() { return this->levelNumber; }
    vector<Point> getStones() { return this->stones; }
    vector<Point> getGlasses() { return this->glasses; }
    Statistics* getStats() { return this->statistics; }
    Size getBoardSize() { return this->boardSize; }
    int getNumberOfPieces() { return this->numberOfPieces; }
    int getNumberOfTypes() { return this->numberOfTypes; }
    double getPieceDelay();
    int getStonePercent() { return this->stonePercent; }
    int getIcePercent() { return this->icePercent; }
    int getFirePercent() { return this->firePercent; }
};
#endif /* defined(__eljoc__Level__) */
