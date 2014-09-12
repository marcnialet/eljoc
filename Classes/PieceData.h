//
//  PieceData.h
//  eljoc
//
//  Created by marc on 18/08/14.
//
//

#ifndef __eljoc__PieceData__
#define __eljoc__PieceData__

#include <iostream>
#include "cocos2d.h"
#include "GameBoard.h"

USING_NS_CC;

class PieceData
{
private:
    int tileType;
    int indexPosition;
    int row;
    int column;
    int strong;
    Point position;
    GameBoard* gameBoard;
    
    Point CalculatePositionFromRowColumn();
    
public:
    PieceData(int indexPosition, GameBoard* gameBoard);
    PieceData(int row, int column, GameBoard* gameBoard);
    
    void Init();
    
    int getRow() { return this->row; }
    int getColumn() { return this->column; }
    int getTileType() { return this->tileType; }
    int getIndexPosition() { return this->indexPosition; }
    Point getPosition() { return this->position; }
    void setTileType(int t) { this->tileType = t; }    
    int getStrong() { return this->strong; }
    void setStrong(int s) { this->strong = s; }
    void decreaseStrong() {
        if(this->strong>0)
        {
          this->strong = --this->strong;
        }
    }
    
    void setRowColumn(int r, int c);
    void setIndexPosition(int i);
    
    
    
};
#endif /* defined(__eljoc__PieceData__) */

