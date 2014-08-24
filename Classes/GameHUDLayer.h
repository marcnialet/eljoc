#ifndef __ENDLEVELLAYER_SCENE_H__
#define __ENDLEVELLAYER_SCENE_H__

#include <iostream>

#include "Defines.h"
#include "cocos2d.h"

using namespace std;

class GameHUDLayer : public cocos2d::Layer
{
private:
    cocos2d::Label* scoreLabel;
    
    cocos2d::Label* addLabel(const std::string fontname, const float fontSize, const char *text, const cocos2d::Vec2 anchor, const cocos2d::Vec2 position);
public:
    virtual bool init();
    void setScore(int score);
    
    CREATE_FUNC(GameHUDLayer);
};

#endif // __ENDLEVELLAYER_SCENE_H__
