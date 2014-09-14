//
//  Statistics.cpp
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#include "Statistics.h"
#include "Level.h"
#include "GameHUDLayer.h"
#include "Utils.h"

Statistics::Statistics()
{
    this->init();
}

Statistics::Statistics(GameHUDLayer* parentlayer)
{
    this->init();
    this->layer = parentlayer;
}

void Statistics::init()
{
    this->level = NULL;
    this->layer = NULL;
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

void Statistics::setLevel(Level* l)
{
    this->level = l;
    this->updateLevel();
}

void Statistics::startTime()
{
    this->starttime = Utils::getTimeTick();
    this->endtime = Utils::getTimeTick();
    
    if(this->level!=NULL && this->level->getStats()!=NULL)
    {
        this->level->getStats()->startTime();
    }
}
void Statistics::resetTime()
{
    this->endtime = Utils::getTimeTick();
    
    if(this->level!=NULL && this->level->getStats()!=NULL)
    {
        this->level->getStats()->updateTime();
    }
}

void Statistics::stopTime()
{
    this->endtime = Utils::getTimeTick();
    
    if(this->level!=NULL && this->level->getStats()!=NULL)
    {
        this->level->getStats()->stopTime();
    }
}

void Statistics::addChain(int chainsize)
{
    if(this->level!=NULL && this->level->getStats()!=NULL)
    {
        this->level->getStats()->addChain(chainsize);
    }
    
    if(chainsize>=0 && chainsize<this->chainsCounter.size())
    {
        int counter = this->chainsCounter[chainsize];
        this->chainsCounter[chainsize] = counter + 1;
        this->numberOfChains++;
        
        this->points += chainsize * 5;
        this->updateScore();
        this->updateChains();
    }
}

void Statistics::addCombo(int combosize)
{
    if(this->level!=NULL && this->level->getStats()!=NULL)
    {
        this->level->getStats()->addCombo(combosize);
    }
    
    if(combosize>=0 && combosize<this->combosCounter.size())
    {
        int counter = this->combosCounter[combosize];
        this->combosCounter[combosize] = counter + 1;
        this->numberOfCombos++;
        
        this->points += combosize * 100;
        this->updateScore();
        this->updateCombos();
    }
}

void Statistics::addPiece(int piecetype)
{
    if(this->level!=NULL && this->level->getStats()!=NULL)
    {
        this->level->getStats()->addPiece(piecetype);
    }
    
    if(piecetype>=0 && piecetype<this->piecesCounter.size())
    {
        int counter = this->piecesCounter[piecetype];
        this->piecesCounter[piecetype] = counter + 1;
        this->numberOfPieces++;
        
        this->points += 10;
        this->updateScore();
        this->updatePieces();
    }
}

void Statistics::addPieces(vector<int> piecetypes)
{
    for(int piecetype:piecetypes)
    {
        this->addPiece(piecetype);
    }
    
    if(this->level!=NULL && this->level->getStats()!=NULL)
    {
        this->level->getStats()->addPieces(piecetypes);
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

void Statistics::updateElapsedTime()
{
    if(this->layer!=NULL && this->level!=NULL)
    {
        Statistics* levelstats = this->level->getStats();
        if(levelstats!=NULL)
        {
            this->layer->setLevelElapsedTime(levelstats->getElapsedTime());
        }
    }
}

void Statistics::updatePieces()
{
    if(this->layer!=NULL && this->level!=NULL)
    {
        Statistics* levelstats = this->level->getStats();
        if(levelstats!=NULL)
        {
            this->layer->setLevelPieces(levelstats->getNumberOfPieces());
        }
    }
}

void Statistics::updateCombos()
{
    if(this->layer!=NULL && this->level!=NULL)
    {
        Statistics* levelstats = this->level->getStats();
        if(levelstats!=NULL)
        {
            this->layer->setLevelCombos(levelstats->getNumberOfCombos());
        }
    }
}

void Statistics::updateChains()
{
    if(this->layer!=NULL && this->level!=NULL)
    {
        Statistics* levelstats = this->level->getStats();
        if(levelstats!=NULL)
        {
            this->layer->setLevelChains(levelstats->getNumberOfChains());
        }
    }
}

void Statistics::updateLevel()
{
    if(this->layer!=NULL && this->level!=NULL)
    {
        this->layer->setLevel(this->level->getLevelNumber());
    }
}
void Statistics::updateScore()
{
    if(this->layer!=NULL && this->level!=NULL)
    {
        this->layer->setGameScore(this->getPoints());
        Statistics* levelstats = this->level->getStats();
        if(levelstats!=NULL)
        {
            unsigned int levelpoints = levelstats->getPoints();
            this->layer->setLevelScore(levelpoints);
        }
    }
}