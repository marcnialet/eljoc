//
//  Piece.cpp
//  eljoc
//
//  Created by marc on 14/08/14.
//
//

#include "Piece.h"

Piece* Piece::create(const int tileType, int row, int column, GameBoard* gameBoard)
{
    Piece * piece = Piece::create(getFileNameFromType(tileType, gameBoard->Rows()));
    if(piece!= NULL)
    {
        piece->data = new PieceData(row, column, gameBoard);
        piece->data->setTileType(tileType);
        piece->setPosition(piece->data->getPosition());
    }
    return piece;
}

Piece* Piece::create(const int tileType, int indexPosition, GameBoard* gameBoard)
{
    Piece * piece = Piece::create(getFileNameFromType(tileType, gameBoard->Rows()));
    if(piece!= NULL)
    {
        piece->data = new PieceData(indexPosition, gameBoard);
        piece->data->setTileType(tileType);
        piece->setPosition(piece->data->getPosition());
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
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(Piece::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Piece::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Piece::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(Piece::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool Piece::onTouchBegan(Touch *touch, Event *event)
{
    // log("onTouchBegan piece: %d", this->data->getIndexPosition());
    if (this->getBoundingBox().containsPoint(touch->getLocation()))
    {
        // this->listener->setSwallowTouches(true);
        this->setActived(true);
    }
    return true;
}

void Piece::onTouchMoved(Touch *touch, Event *event)
{
    // log("onTouchMoved piece: %d", this->data->getIndexPosition());
    
}
void Piece::onTouchEnded(Touch *touch, Event *event)
{
    this->setActived(false);
    // log("onTouchEnded piece: %d", this->data->getIndexPosition());
}
void Piece::onTouchCancelled(Touch *touch, Event *event)
{
    // log("onTouchCancelled");
}
void Piece::setActived(bool active)
{
    _actived = active;
    Action *scale;
    if (_actived)
    {
        scale = ScaleTo::create(0.2, 1.1);
    }
    else
    {
        scale = ScaleTo::create(0.2, 1);
    }
    this->runAction(scale);
}

void Piece::clearNeighbours()
{
    this->neighbours.clear();
}
void Piece::addNeighbour(Piece* piece)
{
    for (auto &p: this->neighbours)
    {
        if(p==piece)
        {
            return;
        }
    }
    this->neighbours.push_back(piece);
}
bool Piece::hasNeighbours()
{
    if(this->neighbours.size()>0) return true;
    
    return false;
    
}
std::string Piece::getFileNameFromType(int tileType, int rows)
{
    string tilename;
    string folder;
    if(tileType == -1)
    {
        tilename = "stone";
    }
    else
    {
       tilename = "tile_" + to_string(tileType+1);
    }
    
    if( rows == 8 )
    {
        folder = "8x8/";
    }
    else
    {
        folder = "10x10/";
    }
    
    string filename = folder+tilename+".png";
    return filename;
}

bool sort_byrow (Piece* piece1, Piece* piece2)
{
    if(piece1!=NULL && piece2!=NULL)
    {
        return (piece1->getRow()<piece2->getRow());
    }
    if(piece1==NULL && piece2!=NULL)
    {
        return true;
    }
    if(piece1!=NULL && piece2==NULL)
    {
        return false;
    }
    return false;
}

bool sort_byrow_rev(Piece* piece1, Piece* piece2)
{
    if(piece2!=NULL && piece1!=NULL)
    {
        return (piece2->getRow()<piece1->getRow());
    }
    if(piece2==NULL && piece1!=NULL)
    {
        return true;
    }
    if(piece2!=NULL && piece1==NULL)
    {
        return false;
    }
    return false;
}

bool sort_bycolumn (Piece* piece1, Piece* piece2)
{
    if(piece1!=NULL && piece2!=NULL)
    {
        return (piece1->getColumn()<piece2->getColumn());
    }
    if(piece1==NULL && piece2!=NULL)
    {
        return true;
    }
    if(piece1!=NULL && piece2==NULL)
    {
        return false;
    }
    return false;
}

bool sort_bycolumn_rev(Piece* piece1, Piece* piece2)
{
    if(piece2!=NULL && piece1!=NULL)
    {
        return (piece2->getColumn()<piece1->getColumn());
    }
    if(piece2==NULL && piece1!=NULL)
    {
        return true;
    }
    if(piece2!=NULL && piece1==NULL)
    {
        return false;
    }
    return false;
}