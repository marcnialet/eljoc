//
//  Piece.h
//  eljoc
//
//  Created by marc on 14/08/14.
//
//

#ifndef __eljoc__Piece__
#define __eljoc__Piece__

#define LOCATION_ACCURACY 100

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Piece: public Sprite
{
    bool _actived;
    Vec2 _targetPosition;
    
    void setActived(bool active);    
    
    
    std::string filename;
    int tileType;
    int indexPosition;
    int row;
    int column;
    
public:
    
    // Constructor
    static Piece* create(const int tileType, int indexPosition, int row, int column);
    static Piece* create(const std::string &filename);
    virtual bool init(const std::string &filename);
    
    void setRowColumn(int r, int c) { this->row=r; this->column=c; }
    int getRow() { return this->row; }
    int getColumn() { return this->column; }
};

#endif /* defined(__eljoc__Piece__) */
