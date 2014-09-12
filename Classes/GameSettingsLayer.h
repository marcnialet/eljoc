#ifndef __GAMESETTINGSLAYER_SCENE_H__
#define __GAMESETTINGSLAYER_SCENE_H__

#include "cocos2d.h"

class GamePlay;

class GameSettingsLayer : public cocos2d::Layer
{
private:
    GamePlay* layerGamePlay;

public:
    virtual bool init();
    
    void menuPlayCallback(Ref* pSender);
    GamePlay* getGamePlayLayer();
    
    CREATE_FUNC(GameSettingsLayer);
};

#endif // __GAMESETTINGSLAYER_SCENE_H__
