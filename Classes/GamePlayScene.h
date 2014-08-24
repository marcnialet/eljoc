#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include <iostream>

#include "Defines.h"
#include "cocos2d.h"
#include "Piece.h"
#include "GameBoard.h"
#include "Level.h"
#include "Statistics.h"

using namespace std;



class GamePlay : public cocos2d::Layer
{
private:
    Label* scoreLabel;
    
    GameMode gameMode;
    int currentLevel;
    Level * level;
    Statistics* statistics;
    vector<Piece *> mapOfPieces;
    vector<int> vectorOfPositions;
    GameBoard* gameBoard;
    
    int getRandomIndexPosition ();
    int getRandomTileType ();
    
    void update(float dt);
    
    int swipeThreshold;
    
    double start;
    double end;
    
    EventListenerTouchAllAtOnce *listener;    
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
    Level* loadLevel(int levelnumber);
    void startCurrentLevel();
    void runGameLoop();
    
    Label* addLabel(const float fontSize, const char *text, const cocos2d::Vec2 anchor, const cocos2d::Vec2 position);
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
