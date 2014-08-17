#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include <iostream>

#include "cocos2d.h"
#include "Piece.h"

using namespace std;


class GamePlay : public cocos2d::LayerColor
{
private:
    map<int, Piece *> mapOfPieces;
    vector<int> vectorOfPositions;
    
    int getRandomIndexPosition ();
    int getRandomTileType ();
    
    double getTimeTick();
    void update(float dt);
    
    double start;
    double end;
    
    EventListenerTouchOneByOne *listener;
    
    cocos2d::Size visibleSize;
    
    bool isTouchDown;
    
    float initialTouchPos[2];
    float currentTouchPos[2];

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    void onTouchCancelled(Touch*, Event*);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);

    
};

#endif // __GAMEPLAY_SCENE_H__
