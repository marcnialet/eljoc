//
//  GameBoard.cpp
//  eljoc
//
//  Created by marc on 21/08/14.
//
//

#include "GameBoard.h"

GameBoard::GameBoard(int rows, int cols)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->num_rows = rows;
    this->num_columns = cols;
    this->numberOfBoxes = rows * cols;
    this->margin = Size(20,20);
    this->boardSize =  Size(visibleSize.width-(margin.width*2),visibleSize.width-(margin.height*2));
    this->boxSize = Size(this->boardSize.width/this->num_columns,this->boardSize.height/this->num_rows);
    this->origin =  Point( ((visibleSize.width-this->boardSize.width) /2) + (this->boxSize.width/2),  ((visibleSize.height-this->boardSize.height) /2)-(this->boxSize.height/2));
    
    
    this->bounding_x0 = this->origin.x - this->boxSize.width/2;
    this->bounding_x1 = this->bounding_x0 + this->boardSize.width;
    this->bounding_y0 = this->origin.y - this->boxSize.height/2;
    this->bounding_y1 = this->bounding_y0 + this->boardSize.height;
    
    /*
    this->origin =  Point(50,180);
    this->boardSize =  Size(600,600);
    this->boxSize = Size(60,60);
     */
}

bool GameBoard::isYInBoard(int y)
{
    if( y > bounding_y0 && y < bounding_y1)
    {
        return true;
    }
    return false;
}

bool GameBoard::isXInBoard(int x)
{
    if( x > bounding_x0 && x < bounding_x1)
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