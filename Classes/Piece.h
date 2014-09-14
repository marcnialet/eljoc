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
#include "Defines.h"

#include "PieceData.h"
#include "GameBoard.h"

using namespace std;

USING_NS_CC;

class Piece: public Sprite
{
    std::string filename;
    PieceData* data;
    vector<Piece *> neighbours;
    GameBoard* gameBoard;
    
    EventListenerTouchOneByOne *listener;
    bool _actived;
    static std::string getFileNameFromType(PieceType pieceType, int pieceColor, int rows);
    void setActived(bool active);
    
public:
    void clearNeighbours();
    void addNeighbour(Piece* piece);
    bool hasNeighbours();
    vector<Piece *> getNeighbours() { return this->neighbours; }
    
    void setRowColumn(int r, int c) { this->data->setRowColumn(r,c); this->setPosition(this->data->getPosition());}
    void setIndexPosition(int i) { this->data->setIndexPosition(i); }
    
    int getRow() { return this->data->getRow(); }
    int getColumn() { return this->data->getColumn(); }
    PieceType getPieceType() { return this->data->getPieceType(); }
    int getPieceColor() { return this->data->getPieceColor(); }
    int getIndexPosition() { return this->data->getIndexPosition(); }
    
    bool isStone() { return this->data->getPieceType() == PieceType::Stone; }
    bool isGlass() { return this->data->getPieceType() == PieceType::Glass; }
    bool isNormal() { return this->data->getPieceType() == PieceType::Normal; }
    
    int getStrong() { return this->data->getStrong(); }
    void setStrong(int s);
    void decreaseStrong();
    
    
    // Constructor
    static Piece* create(PieceType pieceType, int pieceColor, int indexPosition, GameBoard* gameBoard);
    static Piece* create(PieceType pieceType, int pieceColor, int row, int column, GameBoard* gameBoard);
    static Piece* createWithTexture(const std::string &filename);
    static Piece* create(const std::string &filename);
    virtual bool init(const std::string &filename);
    
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    void onTouchCancelled(Touch*, Event*);

};

bool sort_byrow (Piece* piece1, Piece* piece2);
bool sort_byrow_rev (Piece* piece1, Piece* piece2);
bool sort_bycolumn (Piece* piece1, Piece* piece2);
bool sort_bycolumn_rev (Piece* piece1, Piece* piece2);

#endif /* defined(__eljoc__Piece__) */
