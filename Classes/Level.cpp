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
            return level;
        }
    }
    return nullptr;
}

void Start()
{
    
}
void Stop()
{
    
}
bool IsLevelDone()
{
    return false;
}