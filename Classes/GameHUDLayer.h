#ifndef __ENDLEVELLAYER_SCENE_H__
#define __ENDLEVELLAYER_SCENE_H__

#include <iostream>

#include "Defines.h"
#include "cocos2d.h"
#include <UIWidget.h>

using namespace cocos2d;
using namespace std;

class GamePlay;

class GameHUDLayer : public cocos2d::Layer
{
private:
    GamePlay* layerGamePlay;
    
    Label* gameScoreLabel;
    Label* levelLabel;
    Label* levelScoreLabel;
    Label* levelElapsedTimeLabel;
    Label* levelPiecesLabel;
    Label* levelCombosLabel;
    Label* levelChainsLabel;
    
    cocos2d::Label* addLabel(const std::string fontname, const float fontSize, const char *text, const cocos2d::Vec2 anchor, const cocos2d::Vec2 position);
    void touchEvent(Ref *pSender, ui::Widget::TouchEventType type);
    GamePlay* getGamePlayLayer();
    void showSettings();
public:
    virtual bool init();
    
    void setGameScore(int score);
    void setLevelScore(int score);
    void setLevel(int level);
    void setLevelElapsedTime(int elapsedtimeMs);
    void setLevelPieces(int pieces);
    void setLevelCombos(int combos);
    void setLevelChains(int chains);
    
    CREATE_FUNC(GameHUDLayer);
};

#endif // __ENDLEVELLAYER_SCENE_H__
