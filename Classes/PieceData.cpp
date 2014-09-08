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
    this->Init();
    this->gameBoard = gameBoard;
    this->setIndexPosition(indexPosition);
}

PieceData::PieceData(int row, int column, GameBoard* gameBoard)
{
    this->Init();
    this->gameBoard = gameBoard;
    this->setRowColumn(row, column);
}

void PieceData::Init()
{
    this->tileType = 0;
    this->indexPosition = 0;
    this->row = 0;
    this->column = 0;
    this->strong = 0;
}

void PieceData::setRowColumn(int r, int c)
{
    this->column = c;
    this->row = r;
    this->indexPosition = (r * this->gameBoard->Columns()) + c;
    this->position = this->CalculatePositionFromRowColumn();
}

void PieceData::setIndexPosition(int i)
{
    this->indexPosition = i;
    if(i==0)
    {
        string s = "";
        
    }
    this->row = this->indexPosition / this->gameBoard->Columns();
    this->column = this->indexPosition - (this->row * this->gameBoard->Columns());
    
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