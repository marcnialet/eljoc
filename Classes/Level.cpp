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
}

Level* Level::createFromFile(const std::string &filename)
{
    ValueMap map = FileUtils::getInstance()->getValueMapFromFile(filename);
    if(map.size()>0)
    {
        Level* level = new Level();
        if(level!=nullptr)
        {
            level->boardSize = Size(map["Board_Width"].asInt(), map["Board_Height"].asInt());
            level->points = map["Points"].asInt();
            level->delayMs = map["DelayMs"].asDouble();
            level->delayDecrement = map["DelayDecrement"].asDouble();
            
            return level;
        }
    }
    return nullptr;
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