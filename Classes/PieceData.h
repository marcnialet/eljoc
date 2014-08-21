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
    Point position;
    GameBoard* gameBoard;
    
    Point CalculatePositionFromRowColumn();
    
public:
    PieceData(int indexPosition, GameBoard* gameBoard);
    
    int getRow() { return this->row; }
    int getColumn() { return this->column; }
    int getTileType() { return this->tileType; }
    int getIndexPosition() { return this->indexPosition; }
    Point getPosition() { return this->position; }

    
    void setTileType(int t) { this->tileType = t; }

    
    void setRowColumn(int r, int c);
    void setIndexPosition(int i);
    
    
    
};
#endif /* defined(__eljoc__PieceData__) */

