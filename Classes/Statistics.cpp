//
//  Statistics.cpp
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#include "Statistics.h"
#include "Utils.h"

Statistics::Statistics()
{
    this->Reset();
}

void Statistics::Reset()
{
    log("RESET STAD");
    this->levelStatistics = NULL;
    this->points = 0;
    this->elapsedTimeMs = 0.0;
    
    this->numberOfPieces = 0;
    this->numberOfCombos = 0;
    this->numberOfChains = 0;

    
    this->piecesCounter.clear();
    this->combosCounter.clear();
    this->chainsCounter.clear();
    
    for(int i=0; i<100; i++)
    {
        this->piecesCounter.push_back(0);
        this->combosCounter.push_back(0);
        this->chainsCounter.push_back(0);
    }
    this->starttime = 0;
    this->endtime = 0;
}

void Statistics::startTime()
{
    this->starttime = Utils::getTimeTick();
    this->endtime = Utils::getTimeTick();
    
    if(this->levelStatistics!=NULL)
    {
        this->levelStatistics->startTime();
    }
}

void Statistics::stopTime()
{
    log("stopTime STAD");
    this->endtime = Utils::getTimeTick();
    
    if(this->levelStatistics!=NULL)
    {
        this->levelStatistics->stopTime();
    }
}

void Statistics::addChain(int chainsize)
{
    if(chainsize>=0 && chainsize<this->chainsCounter.size())
    {
        int counter = this->chainsCounter[chainsize];
        this->chainsCounter[chainsize] = counter + 1;
        this->numberOfChains++;
        
        this->points += chainsize * 5;
    }
    
    if(this->levelStatistics!=NULL)
    {
        this->levelStatistics->addChain(chainsize);
    }
}

void Statistics::addCombo(int combosize)
{
    if(combosize>=0 && combosize<this->combosCounter.size())
    {
        int counter = this->combosCounter[combosize];
        this->combosCounter[combosize] = counter + 1;
        this->numberOfCombos++;
        
        this->points += combosize * 100;
    }
    
    if(this->levelStatistics!=NULL)
    {
        this->levelStatistics->addCombo(combosize);
    }
}

void Statistics::addPiece(int piecetype)
{
    if(piecetype>=0 && piecetype<this->piecesCounter.size())
    {
        int counter = this->piecesCounter[piecetype];
        this->piecesCounter[piecetype] = counter + 1;
        this->numberOfPieces++;
        
        this->points += 10;
    }
    
    if(this->levelStatistics!=NULL)
    {
        this->levelStatistics->addPiece(piecetype);
    }
}

void Statistics::addPieces(vector<int> piecetypes)
{
    for(int piecetype:piecetypes)
    {
        this->addPiece(piecetype);
    }
    
    if(this->levelStatistics!=NULL)
    {
        this->levelStatistics->addPieces(piecetypes);
    }
}

double Statistics::getElapsedTime()
{
    double elapsedtime = this->endtime - this->starttime;
    return elapsedtime;
}

unsigned int Statistics::getPoints()
{
    return this->points;
}

unsigned int Statistics::getNumberOfPieces()
{
    return this->numberOfPieces;
}

unsigned int Statistics::getNumberOfCombos()
{
    return this->numberOfCombos;
}

unsigned int Statistics::getNumberOfChains()
{
    return this->numberOfChains;
}

unsigned int Statistics::getNumberOfPiecesOfType(int piecetype)
{
    if(piecetype>=0 && piecetype<this->piecesCounter.size())
    {
        return this->piecesCounter[piecetype];
    }
    return 0;
}

unsigned int Statistics::getNumberOfCombosOfType(int combosize)
{
    if(combosize>=0 && combosize<this->combosCounter.size())
    {
        return this->combosCounter[combosize];
    }
    return 0;
}

unsigned int Statistics::getNumberOfChainsOfType(int chainsize)
{
    if(chainsize>=0 && chainsize<this->chainsCounter.size())
    {
        return this->chainsCounter[chainsize];
    }
    return 0;
}