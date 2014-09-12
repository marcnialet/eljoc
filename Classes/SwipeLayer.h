#ifndef __SWIPELAYER_SCENE_H__
#define __SWIPELAYER_SCENE_H__

#include <iostream>

#include "cocos2d.h"
#include "Defines.h"

using namespace std;
using namespace cocos2d;

class SwipeLayer : public cocos2d::LayerColor
{
private:
    EventListenerTouchAllAtOnce *listener;
    bool isTouchDown;
    vector<Point> initialTouchPos;
    vector<Point> currentTouchPos;
    bool isTouchClicked;
    int swipeThreshold;
    
    void processGesture();
    GestureType getGestureType();
protected:
    virtual void update(float dt);
    
    virtual void onTouchesBegan(const vector<Touch*>& touches, Event* event);
    virtual void onTouchesMoved(const vector<Touch*>& touches, Event* event);
    virtual void onTouchesEnded(const vector<Touch*>& touches, Event* event);
    virtual void onTouchesCancelled(const vector<Touch*>& touches, Event* event);
    
    virtual void onGesture(GestureType gesture);
public:
  
    virtual bool init();
    
    CREATE_FUNC(SwipeLayer);
};

#endif // __SWIPELAYER_SCENE_H__
