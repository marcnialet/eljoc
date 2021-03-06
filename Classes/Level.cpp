//
//  Level.cpp
//  eljoc
//
//  Created by marc on 23/08/14.
//
//

#include "Level.h"
#include "Statistics.h"

Level::Level()
{
    this->statistics = new Statistics();
    this->setDefaultValues();
}

Level* Level::createFromLevelNumber(const int levelnumber)
{
    string filename = "Levels/Level_"+to_string(levelnumber)+".plist";
    Level* level = createFromFile(filename);
    if(level!=NULL)
    {
        level->levelNumber = levelnumber;
    }
    return level;
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
            
            if(ConfigKeyExists(map, "numberOfPiecesToAdd"))
            {
                level->numberOfPiecesToAdd = map["numberOfPiecesToAdd"].asInt();
            }
            
            if(ConfigKeyExists(map, "numberOfColorsToAdd"))
            {
                level->numberOfColorsToAdd = map["numberOfColorsToAdd"].asInt();
            }
            
            if(ConfigKeyExists(map, "Stones"))
            {
                auto stonesConfig = map["Stones"].asValueVector();
                for(auto stone:stonesConfig)
                {
                    Point position =getPiecePosition(stone, level->boardSize);
                    if(position != Point::ZERO)
                    {
                        level->stones.push_back(position);
                    }
                }
            }
            
            if(ConfigKeyExists(map, "Glasses"))
            {
                auto glassesConfig = map["Glasses"].asValueVector();
                for(auto glass:glassesConfig)
                {
                    Point position =getPiecePosition(glass, level->boardSize);
                    level->glasses.push_back(position);
                }
            }

            
            return level;
        }
    }
    return nullptr;
}

Point Level::getPiecePosition(Value piece, Size boardSize)
{
    Point position = Point::ZERO;
    string s = (string)piece.asString();
    int pos = s.find(";");
    if(pos>0)
    {
        int x = -1;
        try {
            std::string sX = s.substr(0, pos);
            x = std::stoi(sX);
        }
        catch (const std::invalid_argument& ia) {
            log("Invalid argument: %s",ia.what());
        }
        catch (const std::exception& e) {
            log("Exception: %s",e.what());
        }
        int y = -1;
        try {
            std::string sY = s.substr(pos+1, s.size());
            y = std::stoi(sY);
        }
        catch (const std::invalid_argument& ia) {
            log("Invalid argument: %s",ia.what());
        }
        catch (const std::exception& e) {
            log("Exception: %s",e.what());
        }
        
        if(x>=0 && x < boardSize.width && y>=0 && y< boardSize.height)
        {
           position= Point(x,y);
        }
    }
    return position;
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
    this->numberOfPiecesToAdd = 1;
    this->numberOfColorsToAdd = 4;
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