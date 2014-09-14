//
//  Piece.cpp
//  eljoc
//
//  Created by marc on 14/08/14.
//
//

#include "Piece.h"

Piece* Piece::create(PieceType pieceType, int pieceColor, int row, int column, GameBoard* gameBoard)
{
    string filename = getFileNameFromType(pieceType, pieceColor, gameBoard->Rows());
    Piece * piece;
    if(pieceType==PieceType::Glass)
    {
        piece = Piece::createWithTexture(filename);
    }
    else{
        piece = Piece::create(filename);
    }
    
    if(piece!= NULL)
    {
        piece->data = new PieceData(row, column, gameBoard);
        piece->data->setPieceType(pieceType);
        piece->data->setPieceColor(pieceColor);
        piece->data->setStrong(pieceType==PieceType::Glass ? 3:0);
        piece->setPosition(piece->data->getPosition());
    }
    return piece;
}

Piece* Piece::create(PieceType pieceType, int pieceColor, int indexPosition, GameBoard* gameBoard)
{
    string filename = getFileNameFromType(pieceType, pieceColor, gameBoard->Rows());
    Piece * piece;
    if(pieceType==PieceType::Glass)
    {
        piece = Piece::createWithTexture(filename);
    }
    else{
        piece = Piece::create(filename);
    }
    if(piece!= NULL)
    {
        piece->data = new PieceData(indexPosition, gameBoard);
        piece->data->setPieceType(pieceType);
        piece->data->setPieceColor(pieceColor);
        piece->data->setStrong(pieceType==PieceType::Glass ? 3:0);
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

Piece* Piece::createWithTexture(const std::string &filename)
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("8x8/glasspieceframes.plist", "8x8/glasspieceframes.png");
    
    Piece *piece = new Piece();
    if (piece && piece->initWithSpriteFrame(cache->getSpriteFrameByName("ice_100.png")) )
    {
        piece->setOpacity(150);
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

void Piece::setStrong(int s)
{
    this->data->setStrong(s);
}

void Piece::decreaseStrong()
{
    this->data->decreaseStrong();
    if( this->getStrong() == 2)
    {
        this->setOpacity(100);
        this->setSpriteFrame("ice_66.png");
    }
    else if( this->getStrong() == 1)
    {
        this->setOpacity(50);
        this->setSpriteFrame("ice_33.png");
    }
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
std::string Piece::getFileNameFromType(PieceType pieceType, int pieceColor, int rows)
{
    string tilename;
    string folder;
    if(pieceType == PieceType::Stone)
    {
        tilename = "stone";
    }
    else if(pieceType == PieceType::Glass)
    {
        tilename = "glasspieceframes";
    }
    else
    {
       tilename = "tile_" + to_string(pieceColor+1);
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