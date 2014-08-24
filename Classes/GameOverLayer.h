#ifndef __GAMEOVERLAYER_SCENE_H__
#define __GAMEOVERLAYER_SCENE_H__

#include "cocos2d.h"

class GameOverLayer : public cocos2d::Layer
{
private:
    cocos2d::Label* gameOverLevel;
    
    cocos2d::Label* addLabel(const std::string fontname, const float fontSize, const char *text, const cocos2d::Vec2 anchor, const cocos2d::Vec2 position);

public:
    virtual bool init();
    
    CREATE_FUNC(GameOverLayer);
};

#endif // __GAMEOVERLAYER_SCENE_H__
