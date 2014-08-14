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
    
    EventListenerTouchOneByOne *listener;
    
public:
    
    // Constructor
    static Piece* create(const std::string &filename);
    virtual bool init(const std::string &filename);
    
    void setTargetPosition(Vec2 targetPosition);
    bool currentLocationSuccess();
    
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    //void onTouchCancel(Touch*, Event*);

};

#endif /* defined(__eljoc__Piece__) */
