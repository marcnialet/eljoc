//
//  Statistics.h
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#ifndef __eljoc__Statistics__
#define __eljoc__Statistics__

#include <iostream>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Statistics
{
private:
    unsigned int points;
    double elapsedTimeMs;
    unsigned int numberOfPieces;
    unsigned int numberOfCombos;
    unsigned int numberOfChains;
    vector<unsigned int> piecesCounter;
    vector<unsigned int> combosCounter;
    vector<unsigned int> chainsCounter;
    
    double starttime, endtime;
    Statistics* levelStatistics;
    
public:
    Statistics();
    
    void Reset();
    
    void startTime();
    void stopTime();
    
    double getElapsedTime();
    unsigned int getPoints();
    unsigned int getNumberOfPieces();
    unsigned int getNumberOfCombos();
    unsigned int getNumberOfChains();
    unsigned int getNumberOfPiecesOfType(int piecetype);
    unsigned int getNumberOfCombosOfType(int combosize);
    unsigned int getNumberOfChainsOfType(int chainsize);
    
    void addChain(int chainsize);
    void addCombo(int combosize);
    void addPiece(int piecetype);
    void addPieces(vector<int> types);
    
    void setLevelStatistics(Statistics* stad) { this->levelStatistics = stad; }
    Statistics* getLevelStadistics() { return this->levelStatistics; }
};

#endif /* defined(__eljoc__Statistics__) */
