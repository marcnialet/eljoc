//
//  GameBoard.cpp
//  eljoc
//
//  Created by marc on 21/08/14.
//
//

#include "GameBoard.h"

GameBoard::GameBoard(Layer* parentlayer, int rows, int cols)
{
    this->layer = parentlayer;
    this->boardSprite = this->loadSprite(rows);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size spriteSize = this->boardSprite->getContentSize();
    
    this->num_rows = rows;
    this->num_columns = cols;
    this->numberOfBoxes = rows * cols;
    this->margin = Size((visibleSize.width - spriteSize.width) / 2.0f, (visibleSize.width - spriteSize.width) / 2.0f);
    this->boardSize =  Size(visibleSize.width-(margin.width*2),visibleSize.width-(margin.height*2));
    this->boxSize = Size(this->boardSize.width/this->num_columns,this->boardSize.height/this->num_rows);
    this->boundingBox = Rect((visibleSize.width-this->boardSize.width) /2, (visibleSize.height-this->boardSize.height) /2, this->boardSize.width, this->boardSize.height);
    this->origin = Point(this->boundingBox.origin.x+ (this->boxSize.width/2), this->boundingBox.origin.y+ (this->boxSize.height/2));
    
    this->boardSprite->setAnchorPoint(Point(0, 0));
    this->boardSprite->setPosition(this->boundingBox.origin);
    
    this->layer->addChild(this->boardSprite);
    
}

Sprite* GameBoard::loadSprite(int size)
{
    string filename = "8x8/board8x8.png";
    switch (size) {
        case 8:
            filename = "8x8/board8x8.png";
            break;
        default:
            break;
    }
    return Sprite::create(filename);
}

bool GameBoard::isYInBoard(int y)
{
    if( y > this->boundingBox.getMinY() && y < this->boundingBox.getMaxY())
    {
        return true;
    }
    return false;
}

bool GameBoard::isXInBoard(int x)
{
    if( x > this->boundingBox.getMinX() && x < this->boundingBox.getMaxX())
    {
        return true;
    }
    return false;
}

int GameBoard::convertXtoColumn(int x)
{
    int column = (x - this->origin.x + (this->boxSize.width/2)) / this->boxSize.width;
    return column;
}

int GameBoard::convertYtoRow(int y)
{
    int row = (y - this->origin.y + (this->boxSize.height/2)) / this->boxSize.height;
    return row;
}