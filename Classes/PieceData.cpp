//
//  PieceData.cpp
//  eljoc
//
//  Created by marc on 18/08/14.
//
//

#include "PieceData.h"

PieceData::PieceData(int indexPosition)
{
    this->setIndexPosition(indexPosition);
}

void PieceData::setRowColumn(int r, int c)
{
    this->column = c;
    this->row = r;
    this->indexPosition = (c*10) + r;
    this->position = this->CalculatePositionFromRowColumn();
}

void PieceData::setIndexPosition(int i)
{
    this->indexPosition = i;
    
    this->column = this->indexPosition / 10;
    this->row = this->indexPosition - (this->column * 10);
    
    this->position = this->CalculatePositionFromRowColumn();
}

Point PieceData::CalculatePositionFromRowColumn()
{
    float x0 = 50;
    float y0 = 180;
    
    float x = x0 + this->column * 60.0;
    float y = y0 + this->row * 60.0;
    
    return Vec2(x,y);
}