//
//  GameBoard.h
//  eljoc
//
//  Created by marc on 21/08/14.
//
//

#ifndef __eljoc__GameBoard__
#define __eljoc__GameBoard__

#include <iostream>

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameBoard
{
private:
    int num_rows = 8;
    int num_columns = 8;
    int numberOfBoxes;
    
    Point origin;
    Size boardSize;
    Size boxSize;
    Size margin;
    Rect boundingBox;
    
    Sprite* boardSprite;
    Layer* layer;
    
    Sprite* loadSprite(int size);
public:
    
    GameBoard(Layer* parentlayer, int rows, int cols);
    
    bool isXInBoard(int x);
    bool isYInBoard(int y);
    
    int convertXtoColumn(int x);
    int convertYtoRow(int y);
    
    int Rows() { return this->num_rows; }
    int Columns() { return this->num_columns; }
    Point Origin() { return this->origin; }
    Size BoardSize() { return this->boardSize; }
    Size BoxSize() { return this->boxSize; }
    int NumberOfBoxes() { return numberOfBoxes; }
    Rect BoundingBox() { return this->boundingBox; }
    Sprite* BoardSprite() { return this->boardSprite; }
    
};

#endif /* defined(__eljoc__GameBoard__) */
