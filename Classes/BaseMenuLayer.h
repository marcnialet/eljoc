#ifndef __BASEMENU_SCENE_H__
#define __BASEMENU_SCENE_H__

#include <iostream>

#include "cocos2d.h"
#include "Defines.h"
#include "SwipeLayer.h"

using namespace std;
using namespace cocos2d;

class BaseMenuLayer : public SwipeLayer
{
private:
    void onMainMenuButton(Ref* pSender);

protected:
    virtual void onGesture(GestureType gesture);
    
    virtual void onNextMenu();
    virtual void onPreviousMenu();
public:
    virtual bool init();
    
    
    CREATE_FUNC(BaseMenuLayer);
};

#endif // __BASEMENU_SCENE_H__
