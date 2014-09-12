#ifndef __MENU3LAYER_SCENE_H__
#define __MENU3LAYER_SCENE_H__

#include <iostream>

#include "cocos2d.h"
#include "Defines.h"
#include "BaseMenuLayer.h"

using namespace std;
using namespace cocos2d;

class Menu3Scene : public BaseMenuLayer
{
private:

protected:    
    virtual void onNextMenu();
    virtual void onPreviousMenu();
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    CREATE_FUNC(Menu3Scene);
};

#endif // __MENU3LAYER_SCENE_H__
