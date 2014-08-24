#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include <iostream>

#include "cocos2d.h"
#include "Piece.h"
#include "GameBoard.h"

using namespace std;

enum GestureType
{
    None = 0,
    Swipe_Left = 1,
    Swipe_Right = 2,
    Swipe_Up = 3,
    Swipe_Down = 4,
    
    Swipe_Left_Multi = 5,
    Swipe_Right_Multi = 6,
    Swipe_Up_Multi = 7,
    Swipe_Down_Multi = 8
};

class GamePlay : public cocos2d::Layer
{
private:
    vector<Piece *> mapOfPieces;
    vector<int> vectorOfPositions;
    GameBoard* gameBoard;
    
    int getRandomIndexPosition ();
    int getRandomTileType ();
    
    void update(float dt);
    
    double start;
    double end;
    
    EventListenerTouchAllAtOnce *listener;
    
    cocos2d::Size visibleSize;
    
    bool isTouchDown;
    vector<Point> initialTouchPos;
    vector<Point> currentTouchPos;
    
    std::vector<Piece*> getPiecesByRow(int row);
    std::vector<Piece*> getPiecesByColumn(int column);
    void swapPositions(int oldindex, int newindex);
    void setNeighbours();
    void setPieceNeighbours(Piece* piece, vector<Piece *> );
    void findChains();
    void findChildChain(vector<Piece *>& list, Piece* piece, vector<Piece *>& pieces);
    
    Piece* getPieceByRowColumn(vector<Piece *> pieces, int row, int column);
    
    GestureType GetGestureType(vector<int>& rowcols);

    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void onTouchesBegan(const vector<Touch*>& touches, Event* event);
    void onTouchesMoved(const vector<Touch*>& touches, Event* event);
    void onTouchesEnded(const vector<Touch*>& touches, Event* event);
    void onTouchesCancelled(const vector<Touch*>& touches, Event* event);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);   
};

#endif // __GAMEPLAY_SCENE_H__
