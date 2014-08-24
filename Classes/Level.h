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
#include "Statistics.h"

using namespace std;
using namespace cocos2d;

class Level
{
private:
    Statistics* statistics;
    
    Size boardSize;
    unsigned int points;
    double elapsedTimeMs;
    unsigned int numberOfPieces;
    unsigned int numberOfCombos;
    unsigned int numberOfChains;
    vector<unsigned int> piecesCounter;
    vector<unsigned int> combosCounter;
    vector<unsigned int> chainsCounter;
    
public:
    static Level* createFromFile(const std::string &filename);
    
    Level();
    
    void Start();
    void Stop();
    bool IsLevelDone();
    
    Statistics* getStats() { return this->statistics; }
    
    
};
#endif /* defined(__eljoc__Level__) */
