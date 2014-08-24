#include "GamePlayScene.h"
#include "Utils.h"
#include "Defines.h"

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
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->scoreLabel = this->addLabel(48, "Score 0", Vec2(0.0, 1.0), Vec2(10, Director::getInstance()->getVisibleSize().height - 10));
    
    
    this->listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GamePlay::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GamePlay::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GamePlay::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GamePlay::onTouchesCancelled, this);
    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    this->swipeThreshold = Director::getInstance()->getVisibleSize().width * 0.05;
    this->currentLevel = 1;
    this->gameMode = GameMode::NotLoaded;
    this->isTouchDown = false;
    this->start = 0;
    this->end = 0;
    this->statistics = new Statistics();
    
    this->scheduleUpdate();
    
    return true;
}
Label* GamePlay::addLabel(const float fontSize, const char *text,
							const cocos2d::Vec2 anchor, const cocos2d::Vec2 position)
{
    TTFConfig config("fonts/Marker Felt.ttf", 25);
   
    
	Label *theLabel = Label::createWithTTF(config, text);
    //LabelTTF *theLabel = LabelTTF::create(text, "Arial", 24);
    
	theLabel->setAnchorPoint(anchor);
	theLabel->setPosition(position);
	theLabel->setColor(Color3B::RED);
	this->addChild(theLabel, 100);
	return theLabel;
}
void GamePlay::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesBegan");
    this->initialTouchPos.clear();
    this->currentTouchPos.clear();
    
    for (auto &touch: touches)
    {
        isTouchDown = true;
        this->initialTouchPos.push_back(touch->getLocation());
        this->currentTouchPos.push_back(touch->getLocation());
    }
}
void GamePlay::onTouchesMoved(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesMoved");
    this->currentTouchPos.clear();    
    for (auto &touch: touches)
    {
        this->currentTouchPos.push_back(touch->getLocation());
    }
}
void GamePlay::onTouchesEnded(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesEnded");
    isTouchDown = false;
    this->initialTouchPos.clear();
}
void GamePlay::onTouchesCancelled(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesCancelled");
}

GestureType GamePlay::GetGestureType(vector<int>& rowcols)
{
    GestureType gesture = GestureType::None;
    
    bool single = currentTouchPos.size()==1 && currentTouchPos.size()==1;
    bool multiple = currentTouchPos.size()>1 && currentTouchPos.size()>1;
    if(single||multiple)
    {
        if (initialTouchPos[0].x - currentTouchPos[0].x > this->swipeThreshold)
        {
            int initY = initialTouchPos[0].y;
            if(this->gameBoard->isYInBoard(initY))
            {
                if(multiple)
                {
                    gesture = GestureType::Swipe_Left_Multi;
                    for(int i=0; i<this->gameBoard->Rows(); i++) rowcols.push_back(i);
                    // log("SWIPED LEFT MULTIPLE");
                }
                else
                {
                    int rowcol = this->gameBoard->convertYtoRow(initY);
                    rowcols.push_back(rowcol);
                    gesture = GestureType::Swipe_Left;
                    // log("SWIPED LEFT in row: %d", rowcol);
                }
            }
        }
        else if (initialTouchPos[0].x - currentTouchPos[0].x < - this->swipeThreshold)
        {
            int initY = initialTouchPos[0].y;
            if(this->gameBoard->isYInBoard(initY))
            {
                
                if(multiple)
                {
                    gesture = GestureType::Swipe_Right_Multi;
                    for(int i=0; i<this->gameBoard->Rows(); i++) rowcols.push_back(i);
                    // log("SWIPED RIGHT MULTIPLE");
                }
                else
                {
                    int rowcol = this->gameBoard->convertYtoRow(initY);
                    rowcols.push_back(rowcol);
                    gesture = GestureType::Swipe_Right;
                    // log("SWIPED RIGHT in row: %d", rowcol);
                }
            }
        }
        
        else if (initialTouchPos[0].y - currentTouchPos[0].y > this->swipeThreshold)
        {
            int initX = initialTouchPos[0].x;
            if(this->gameBoard->isXInBoard(initX))
            {
                
                if(multiple)
                {
                    gesture = GestureType::Swipe_Down_Multi;
                    for(int i=0; i<this->gameBoard->Columns(); i++) rowcols.push_back(i);
                    // log("SWIPED DOWN MULTIPLE");
                }
                else
                {
                    int rowcol = this->gameBoard->convertXtoColumn(initX);
                    rowcols.push_back(rowcol);
                    gesture = GestureType::Swipe_Down;
                    // log("SWIPED DOWN in col: %d", rowcol);
                }
            }
        }
        else if (initialTouchPos[0].y - currentTouchPos[0].y < - this->swipeThreshold)
        {
            int initX = initialTouchPos[0].x;
            if(this->gameBoard->isXInBoard(initX))
            {
                
                if(multiple)
                {
                    gesture = GestureType::Swipe_Up_Multi;
                    for(int i=0; i<this->gameBoard->Columns(); i++) rowcols.push_back(i);
                    // log("SWIPED UP MULTIPLE");
                }
                else
                {
                    int rowcol = this->gameBoard->convertXtoColumn(initX);
                    rowcols.push_back(rowcol);
                    gesture = GestureType::Swipe_Up;
                    // log("SWIPED UP in col: %d", rowcol);
                }
            }
        }
    }
    
    return gesture;
    
}

void GamePlay::update(float dt)
{
    
    switch(this->gameMode)
    {
        case GameMode::NotLoaded:
            this->gameMode = GameMode::LoadingLevel;
            break;
        case GameMode::LoadingLevel:
            this->startCurrentLevel();
            this->gameMode = GameMode::LevelLoaded;
            break;
        case GameMode::LevelLoaded:
            this->gameMode = GameMode::Running;
            break;
        case GameMode::Running:
            this->runGameLoop();
            break;
        case GameMode::LevelDone:
            break;
        case GameMode::GameOver:
            break;
        case GameMode::Paused:
            break;
    }
}

void GamePlay::startCurrentLevel()
{
    this->level = loadLevel(this->currentLevel);
    srand ( time(NULL) );
    
    this->gameBoard = new GameBoard(this->level->getBoardSize().width, this->level->getBoardSize().height);
    
    this->isTouchDown = false;
    this->start = 0;
    this->end = 0;
    for (int i=0; i<this->gameBoard->NumberOfBoxes(); ++i)
    {
        this->vectorOfPositions.push_back(i);
    }
}

Level* GamePlay::loadLevel(int levelnumber)
{
    string filename = "Levels/Level_"+to_string(levelnumber)+".plist";
    auto l = Level::createFromFile(filename);
    return l;
}

void GamePlay::runGameLoop()
{
    if(this->start==0 && this->end==0)
    {
        this->start = Utils::getTimeTick();
    }
    this->end = Utils::getTimeTick();
    double delay = this->end - this->start;
    if(delay>2500)
    {
        start = 0;
        end = 0;
        if(this->vectorOfPositions.size()>0)
        {
            int index = getRandomIndexPosition();
            int pieceType = getRandomTileType();
            Piece * piece = Piece::create(pieceType, index, this->gameBoard);
            this->mapOfPieces.push_back(piece);
            std::vector<int>::iterator it = this->vectorOfPositions.begin();
            this->vectorOfPositions.erase(it);
            this->addChild(piece);
            
            this->statistics->addPiece(pieceType);
            this->level->getStats()->addPiece(pieceType);
            
            this->setPieceNeighbours(piece, this->mapOfPieces);
        }
    }
    
    if (true == isTouchDown)
    {
        vector<int> rowcols;
        GestureType gesture = GetGestureType(rowcols);
        
        if (gesture==GestureType::Swipe_Left || gesture==GestureType::Swipe_Left_Multi)
        {
            for (auto &rowcol: rowcols)
            {
                std::vector<Piece*> pieces = this->getPiecesByRow(rowcol);
                if(pieces.size()>0)
                {
                    std::sort (pieces.begin(), pieces.end(), sort_bycolumn);
                    int newcol = 0;
                    for (auto &row_piece: pieces)
                    {
                        int oldindex = row_piece->getIndexPosition();
                        row_piece->setRowColumn(row_piece->getRow(), newcol);
                        int newindex = row_piece->getIndexPosition();
                        this->swapPositions(oldindex, newindex);
                        newcol++;
                    }
                }
            }
            this->setNeighbours();
            this->initialTouchPos.clear();
            this->currentTouchPos.clear();
            isTouchDown = false;
        }
        else if (gesture==GestureType::Swipe_Right || gesture==GestureType::Swipe_Right_Multi)
        {
            for (auto &rowcol: rowcols)
            {
                std::vector<Piece*> pieces = this->getPiecesByRow(rowcol);
                if(pieces.size()>0)
                {
                    std::sort (pieces.begin(), pieces.end(), sort_bycolumn_rev);
                    int newcol = this->gameBoard->Columns()-1;
                    for (auto &row_piece: pieces)
                    {
                        int oldindex = row_piece->getIndexPosition();
                        row_piece->setRowColumn(row_piece->getRow(), newcol);
                        int newindex = row_piece->getIndexPosition();
                        this->swapPositions(oldindex, newindex);
                        newcol--;
                    }
                }
            }
            this->setNeighbours();
            this->initialTouchPos.clear();
            this->currentTouchPos.clear();
            isTouchDown = false;
        }
        else if (gesture==GestureType::Swipe_Down || gesture==GestureType::Swipe_Down_Multi)
        {
            for (auto &rowcol: rowcols)
            {
                std::vector<Piece*> pieces = this->getPiecesByColumn(rowcol);
                if(pieces.size()>0)
                {
                    std::sort (pieces.begin(), pieces.end(), sort_byrow);
                    int newcol = 0;
                    for (auto &col_piece: pieces)
                    {
                        int oldindex = col_piece->getIndexPosition();
                        col_piece->setRowColumn(newcol, col_piece->getColumn());
                        int newindex = col_piece->getIndexPosition();
                        this->swapPositions(oldindex, newindex);
                        newcol++;
                    }
                }
            }
            this->setNeighbours();
            this->initialTouchPos.clear();
            this->currentTouchPos.clear();
            isTouchDown = false;
        }
        else if (gesture==GestureType::Swipe_Up || gesture==GestureType::Swipe_Up_Multi)
        {
            for (auto &rowcol: rowcols)
            {
                std::vector<Piece*> pieces = this->getPiecesByColumn(rowcol);
                if(pieces.size()>0)
                {
                    std::sort (pieces.begin(), pieces.end(), sort_byrow_rev);
                    int newcol = this->gameBoard->Rows()-1;
                    for (auto &col_piece: pieces)
                    {
                        int oldindex = col_piece->getIndexPosition();
                        col_piece->setRowColumn(newcol, col_piece->getColumn());
                        int newindex = col_piece->getIndexPosition();
                        this->swapPositions(oldindex, newindex);
                        newcol--;
                    }
                }
            }
            this->setNeighbours();
            this->initialTouchPos.clear();
            this->currentTouchPos.clear();
            isTouchDown = false;
        }
    }
    this->findChains();
    
    if(this->level->IsLevelDone())
    {
        this->gameMode = GameMode::LevelDone;
    }
    else
    {
        char ScoreString[64];
        sprintf(ScoreString, "Score %d", this->statistics->getPoints());
        this->scoreLabel->setString(ScoreString);
    }
}

void GamePlay::setNeighbours()
{
    if(this->mapOfPieces.size()<=0) return;
    
    for (auto &p: this->mapOfPieces)
    {
        p->clearNeighbours();
    }
    
    vector<Piece *> pieces(this->mapOfPieces);
    while (!pieces.empty())
    {
        auto piece = pieces.back();
        pieces.pop_back();
        this->setPieceNeighbours(piece, pieces);
    }
}

void GamePlay::setPieceNeighbours(Piece* piece, vector<Piece *> pieces)
{
    int row = piece->getRow();
    int col = piece->getColumn();
    
    Piece* p1 = this->getPieceByRowColumn(pieces, row-1,col);
    if(p1!=NULL && p1->getTileType()==piece->getTileType())
    {
        piece->addNeighbour(p1);
        p1->addNeighbour(piece);
    }
    
    Piece* p2 = this->getPieceByRowColumn(pieces, row+1,col);
    if(p2!=NULL && p2->getTileType()==piece->getTileType())
    {
        piece->addNeighbour(p2);
        p2->addNeighbour(piece);
    }
    
    Piece* p3 = this->getPieceByRowColumn(pieces, row,col-1);
    if(p3!=NULL && p3->getTileType()==piece->getTileType())
    {
        piece->addNeighbour(p3);
        p3->addNeighbour(piece);
    }
    
    Piece* p4 = this->getPieceByRowColumn(pieces, row,col+1);
    if(p4!=NULL && p4->getTileType()==piece->getTileType())
    {
        piece->addNeighbour(p4);
        p4->addNeighbour(piece);
    }
}

void GamePlay::findChains()
{
    vector<vector<Piece *>> chains;
    
    vector<Piece *> pieces(this->mapOfPieces);
    
    while (!pieces.empty())
    {
        auto piece = pieces.back();
        pieces.pop_back();
        if(piece->hasNeighbours())
        {
            vector<Piece *> list;
            list.push_back(piece);
            
            this->findChildChain(list, piece, pieces);
            
            chains.push_back(list);
        }
    }
    if(chains.size()>0)
    {
        // log("Chain in found: %d", (int)chains.size());
        if(chains.size()>0)
        {
            for (auto &chain: chains)
            {
                int combosize = 0;
                if(chain.size()>=3)
                {
                    this->statistics->addChain(chain.size());
                    this->level->getStats()->addChain(chain.size());
                    combosize++;
                    for (auto &piece: chain)
                    {
                        for( vector<Piece*>::iterator iter = this->mapOfPieces.begin(); iter != this->mapOfPieces.end(); ++iter )
                        {
                            if( *iter == piece )
                            {
                                this->vectorOfPositions.push_back(piece->getIndexPosition());
                                this->removeChild(piece);
                                this->mapOfPieces.erase( iter );
                                break;
                            }
                        }
                    }
                }
                if(combosize>1)
                {
                    this->statistics->addCombo(combosize);
                    this->level->getStats()->addCombo(combosize);
                }
            }
        }
    }
}
void GamePlay::findChildChain(vector<Piece *>& list, Piece* piece, vector<Piece *>& pieces)
{
    if(piece->hasNeighbours())
    {
        for (auto &next_piece: piece->getNeighbours())
        {
            bool exist = false;
            for (auto &l: list)
            {
                if(l==next_piece) {
                    exist = true;
                    break;
                }
            }
            if(exist==false)
            {
                list.push_back(next_piece);
                for (int i=0; i<pieces.size();i++)
                {
                    auto ps = pieces[i];
                    if(ps==next_piece)
                    {
                        pieces.erase (pieces.begin()+i);
                        break;
                    }
                }
                this->findChildChain(list, next_piece, pieces);
            }
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



Piece* GamePlay::getPieceByRowColumn(vector<Piece *> pieces, int row, int column)
{
    if(row<0) return NULL;
    if(row>this->gameBoard->Rows()-1) return NULL;
    if(column<0) return NULL;
    if(column>this->gameBoard->Columns()-1) return NULL;
    
    for (auto &piece: pieces)
    {
        if(piece->getRow() == row && piece->getColumn() == column)
        {
            return piece;
        }
    }
    return NULL;
}

std::vector<Piece*> GamePlay::getPiecesByRow(int row)
{
    std::vector<Piece*> rowpieces;
    
    if(row<0) return rowpieces;
    if(row>this->gameBoard->Rows()-1) return rowpieces;
    for (auto &piece: this->mapOfPieces)
    {
        if(piece->getRow() == row)
        {
            rowpieces.push_back(piece);
        }
    }
    return rowpieces;
}

std::vector<Piece*> GamePlay::getPiecesByColumn(int column)
{
    std::vector<Piece*> colpieces;
    
    if(column<0) return colpieces;
    if(column>this->gameBoard->Columns()-1) return colpieces;
    
    for (auto &piece: this->mapOfPieces)
    {
        if(piece->getColumn() == column)
        {
            colpieces.push_back(piece);
        }
    }
    return colpieces;
}

void GamePlay::swapPositions(int oldindex, int newindex)
{
    for (int i=0; i<vectorOfPositions.size();i++)
    {
        if(vectorOfPositions[i]==newindex)
        {
            // log("swap position %d - %d",oldindex,newindex);
            vectorOfPositions[i]=oldindex;
            return;
        }
    }
    // log("CANNOT swap position %d - %d",oldindex,newindex);
}
