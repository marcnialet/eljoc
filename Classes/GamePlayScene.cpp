#include "GamePlayScene.h"


USING_NS_CC;

Scene* GamePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlay::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    // Size visibleSize = Director::getInstance()->getVisibleSize();
    // Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamePlay::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GamePlay::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    
    this->start = 0;
    this->end = 0;
    
    for (int i=0; i<100; ++i) this->vectorOfPositions.push_back(i);
    
    this->scheduleUpdate();
    
    return true;
}
bool GamePlay::onTouchBegan(Touch *touch, Event *event)
{
    log("onTouchBegan");
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    
    return true;
}

void GamePlay::onTouchMoved(Touch *touch, Event *event)
{
    log("onTouchMoved");
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
}

void GamePlay::onTouchEnded(Touch *touch, Event *event)
{
    log("onTouchEnded");
    isTouchDown = false;
}

void GamePlay::onTouchCancelled(Touch *touch, Event *event)
{
    log("onTouchCancelled");
    onTouchEnded(touch, event);
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

void GamePlay::update(float dt)
{
    if(this->start==0 && this->end==0)
    {
        this->start = this->getTimeTick();
    }
    this->end = this->getTimeTick();
    double delay = this->end - this->start;
    if(delay>2500)
    {
        start = 0;
        end = 0;
        if(this->vectorOfPositions.size()>0)
        {
            int index = getRandomIndexPosition();
            
            int type = getRandomTileType();
            
            int column = index / 10;
            int row = index - (column * 10);
            
            
            Piece * piece = Piece::create(type, index, row, column);
            
            float x0 = 50;
            float y0 = 180;
            
            float x = x0 + column * 60.0;
            float y = y0 + row * 60.0;
            
            auto position = Vec2(x,y);
            
            piece->setPosition(position);
            
            this->mapOfPieces.insert(std::pair<int,Piece *>(index, piece));
            
            std::vector<int>::iterator it = this->vectorOfPositions.begin();
            this->vectorOfPositions.erase(it);
            
            this->addChild(piece);
        }
        else
        {
            //this->removeAllChildren();
            //for (int i=0; i<100; ++i) this->vectorOfPositions.push_back(i);
        }
    }
    
    if (true == isTouchDown)
    {
        if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05)
        {
            int initY = initialTouchPos[1];
            if(initY>150&&initY<750)
            {
                int row = (initY - 150) / 60;
                log("SWIPED LEFT in row: %d", row);
                std::vector<Piece*> rowpieces;
                for (std::map<int, Piece *>::iterator it = this->mapOfPieces.begin(); it != this->mapOfPieces.end(); ++it)
                {
                    Piece* piece = it->second;
                    if(piece->getRow() == row)
                    {
                        rowpieces.push_back(piece);
                    }
                }
                
                std::sort (rowpieces.begin(), rowpieces.end(), sort_bycolumn);
                int newcol = 0;
                for (auto &row_piece: rowpieces)
                {
                    row_piece->setRowColumn(row_piece->getRow(), newcol);
                    newcol++;
                    
                    float x0 = 50;
                    float y0 = 180;
                    
                    float x = x0 + row_piece->getColumn() * 60.0;
                    float y = y0 + row_piece->getRow() * 60.0;
                    
                    auto position = Vec2(x,y);
                    
                    row_piece->setPosition(position);
                }
            }
            isTouchDown = false;
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - visibleSize.width * 0.05)
        {
            int initY = initialTouchPos[1];
            if(initY>150&&initY<750)
            {
                int row = (initY - 150) / 60;
                log("SWIPED RIGHT in row: %d", row);
                
                std::vector<Piece*> rowpieces;
                for (std::map<int, Piece *>::iterator it = this->mapOfPieces.begin(); it != this->mapOfPieces.end(); ++it)
                {
                    Piece* piece = it->second;
                    if(piece->getRow() == row)
                    {
                        rowpieces.push_back(piece);
                    }
                }
                
                std::sort (rowpieces.begin(), rowpieces.end(), sort_bycolumn_rev);
                int newcol = 9;
                for (auto &row_piece: rowpieces)
                {
                    row_piece->setRowColumn(row_piece->getRow(), newcol);
                    newcol--;
                    
                    float x0 = 50;
                    float y0 = 180;
                    
                    float x = x0 + row_piece->getColumn() * 60.0;
                    float y = y0 + row_piece->getRow() * 60.0;
                    
                    auto position = Vec2(x,y);
                    
                    row_piece->setPosition(position);
                }
            }
            isTouchDown = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
        {
            int initX = initialTouchPos[0];
            if(initX>20&&initX<620)
            {
                int col = (initX - 20) / 60;
                log("SWIPED DOWN in col: %d", col);
                
                std::vector<Piece*> colpieces;
                for (std::map<int, Piece *>::iterator it = this->mapOfPieces.begin(); it != this->mapOfPieces.end(); ++it)
                {
                    Piece* piece = it->second;
                    if(piece->getColumn() == col)
                    {
                        colpieces.push_back(piece);
                    }
                }
                
                std::sort (colpieces.begin(), colpieces.end(), sort_byrow);
                int newcol = 0;
                for (auto &col_piece: colpieces)
                {
                    col_piece->setRowColumn(newcol, col_piece->getColumn());
                    newcol++;
                    
                    float x0 = 50;
                    float y0 = 180;
                    
                    float x = x0 + col_piece->getColumn() * 60.0;
                    float y = y0 + col_piece->getRow() * 60.0;
                    
                    auto position = Vec2(x,y);
                    
                    col_piece->setPosition(position);
                }
               
            }
            isTouchDown = false;
        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05)
        {
            int initX = initialTouchPos[0];
            if(initX>20&&initX<620)
            {
                int col = (initX - 20) / 60;
                log("SWIPED UP in col: %d", col);
                
                std::vector<Piece*> colpieces;
                for (std::map<int, Piece *>::iterator it = this->mapOfPieces.begin(); it != this->mapOfPieces.end(); ++it)
                {
                    Piece* piece = it->second;
                    if(piece->getColumn() == col)
                    {
                        colpieces.push_back(piece);
                    }
                }
                
                std::sort (colpieces.begin(), colpieces.end(), sort_byrow_rev);
                int newcol = 9;
                for (auto &col_piece: colpieces)
                {
                    col_piece->setRowColumn(newcol, col_piece->getColumn());
                    newcol--;
                    
                    float x0 = 50;
                    float y0 = 180;
                    
                    float x = x0 + col_piece->getColumn() * 60.0;
                    float y = y0 + col_piece->getRow() * 60.0;
                    
                    auto position = Vec2(x,y);
                    
                    col_piece->setPosition(position);
                }
            }
            isTouchDown = false;
        }
        
    }
}

int myrandom (int i) { return std::rand()%i;}

int GamePlay::getRandomTileType()
{
    int tileType = rand() % 4;
    // log("Next tile type: %d",tileType);
    return tileType;
}

int GamePlay::getRandomIndexPosition ()
{
    std::random_shuffle ( this->vectorOfPositions.begin(), this->vectorOfPositions.end(), myrandom);
    int number = this->vectorOfPositions.front();
    
    // log("Next item: %d", number);
    return number;
}

double GamePlay::getTimeTick()
{
    timeval time;
    gettimeofday(&time, NULL);
    double millisecs = ((double)time.tv_sec * (double)1000.0) + ((double)time.tv_usec/(double)1000.0);
    return millisecs;
}

