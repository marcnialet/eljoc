//
//  Level.cpp
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#include "Level.h"

Level::Level()
{
    this->statistics = new Statistics();
    this->setDefaultValues();
}

Level* Level::createFromFile(const std::string &filename)
{
    ValueMap map = FileUtils::getInstance()->getValueMapFromFile(filename);
    if(map.size()>0)
    {
        Level* level = new Level();
        if(level!=nullptr)
        {
            if(ConfigKeyExists(map, "Board_Width") && ConfigKeyExists(map, "Board_Height"))
            {
                level->boardSize = Size(map["Board_Width"].asInt(), map["Board_Height"].asInt());
            }
            
            if(ConfigKeyExists(map, "Points"))
            {
                level->points = map["Points"].asInt();
            }
            
            if(ConfigKeyExists(map, "DelayMs"))
            {
                level->delayMs = map["DelayMs"].asDouble();
            }
            
            if(ConfigKeyExists(map, "DelayDecrement"))
            {
                level->delayDecrement = map["DelayDecrement"].asDouble();
            }
            
            if(ConfigKeyExists(map, "NumberOfPieces"))
            {
                level->numberOfPieces = map["NumberOfPieces"].asInt();
            }
            
            if(ConfigKeyExists(map, "NumberOfTypes"))
            {
                level->numberOfTypes = map["NumberOfTypes"].asInt();
            }
            
            return level;
        }
    }
    return nullptr;
}
void Level::start()
{
    if(this->statistics!=NULL)
    {
        this->statistics->startTime();
    }
}

void Level::stop()
{
    if(this->statistics!=NULL)
    {
        this->statistics->stopTime();
    }
}

double Level::getPieceDelay()
{
    return this->delayMs;
}

bool Level::IsLevelDone()
{
    bool pointsOk = this->statistics->getPoints() >= this->points;
    
    bool levelDone = pointsOk;
    
    return levelDone;
}

void Level::setDefaultValues()
{
    this->boardSize = Size(8,8);
    this->points = 1000;
    this->delayMs = 1000;
    this->delayDecrement = 0;
    this->numberOfPieces = 1;
    this->numberOfTypes = 4;
}

bool Level::ConfigKeyExists(ValueMap map, string key)
{
    auto iter = map.find(key);
    bool exists = true;
    if ( iter == map.end() )
    {
        log("The Configuration value %s has been not found in the Level configuration file.",key.c_str());
        exists = false;
    }
    return exists;
}