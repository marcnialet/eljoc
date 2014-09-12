#ifndef __MAINMENULAYER_SCENE_H__
#define __MAINMENULAYER_SCENE_H__

#include "cocos2d.h"

class MainMenuLayer : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void onMenuPlayButton(cocos2d::Ref* pSender);
    void onMenuTutorialButton(Ref* pSender);
    void onMenuMenuButton(Ref* pSender);
    CREATE_FUNC(MainMenuLayer);
};

#endif // __MAINMENULAYER_SCENE_H__
