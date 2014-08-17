//
//  Piece.cpp
//  eljoc
//
//  Created by marc on 14/08/14.
//
//

#include "Piece.h"

Piece* Piece::create(const int tileType, int indexPosition, int row, int column)
{
    std::string filename;
    switch (tileType)
    {
        case 0:
            filename="blue_tile.png";
            break;
        case 1:
            filename="green_tile.png";
            break;
        case 2:
            filename="red_tile.png";
            break;
        case 3:
            filename="yellow_tile.png";
            break;
            
        default:
            break;
    }    
    
    Piece * piece = Piece::create(filename);
    if(piece!= NULL)
    {
        piece->tileType =tileType;
        piece->indexPosition =indexPosition;
        piece->row = row;
        piece->column = column;
    }
    return piece;
}

Piece* Piece::create(const std::string &filename)
{
    Piece *piece = new Piece();
    if (piece && piece->init(filename))
    {
        piece->filename = filename;
        piece->autorelease();
    }
    else
    {
        delete piece;
        piece = NULL;
    }
    return piece;
    
}

bool Piece::init(const std::string &filename)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    return true;
}