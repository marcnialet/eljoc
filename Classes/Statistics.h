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

class GameHUDLayer;
class Level;

class Statistics
{
private:
    GameHUDLayer* layer;
    
    unsigned int points;
    double elapsedTimeMs;
    unsigned int numberOfPieces;
    unsigned int numberOfCombos;
    unsigned int numberOfChains;
    vector<unsigned int> piecesCounter;
    vector<unsigned int> combosCounter;
    vector<unsigned int> chainsCounter;
    
    double starttime, endtime;
    Level* level;
    
    void updateScore();
    void updateLevel();
    void updateElapsedTime();
    void updateChains();
    void updatePieces();
    void updateCombos();
public:
    Statistics();
    Statistics(GameHUDLayer* parentlayer);
    
    void init();
    
    void startTime();
    void stopTime();
    void resetTime();
    
    
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
    
    void setLevel(Level* l);
};

#endif /* defined(__eljoc__Statistics__) */
