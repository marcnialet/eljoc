//
//  PieceData.cpp
//  eljoc
//
//  Created by marc on 18/08/14.
//
//

#include "PieceData.h"

PieceData::PieceData(int indexPosition, GameBoard* gameBoard)
{
    this->gameBoard = gameBoard;
    this->setIndexPosition(indexPosition);
}

void PieceData::setRowColumn(int r, int c)
{
    this->column = c;
    this->row = r;
    this->indexPosition = (c * this->gameBoard->Columns()) + r;
    this->position = this->CalculatePositionFromRowColumn();
}

void PieceData::setIndexPosition(int i)
{
    this->indexPosition = i;
    
    this->column = this->indexPosition / this->gameBoard->Columns();
    this->row = this->indexPosition - (this->column * this->gameBoard->Columns());
    
    this->position = this->CalculatePositionFromRowColumn();
}

Point PieceData::CalculatePositionFromRowColumn()
{
    float x0 = this->gameBoard->Origin().x;
    float y0 = this->gameBoard->Origin().y;
    
    float x = x0 + this->column * this->gameBoard->BoxSize().width;
    float y = y0 + this->row * this->gameBoard->BoxSize().height;
    
    return Vec2(x,y);
}