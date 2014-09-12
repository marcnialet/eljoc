#include "GameHUDLayer.h"
#include "GamePlayScene.h"
#include "Defines.h"
#include <UIButton.h>

USING_NS_CC;

bool GameHUDLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    this->layerGamePlay = NULL;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    this->levelLabel = this->addLabel(kFontName, 48, "Level 0", Vec2(0.0, 1.0), Vec2(100, visibleSize.height - 10));
    this->gameScoreLabel = this->addLabel(kFontName, 48, "Score 0", Vec2(0.0, 1.0), Vec2(100, visibleSize.height - 60));
    this->levelScoreLabel = this->addLabel(kFontName, 32, "Score 0", Vec2(0.0, 1.0), Vec2(20, 160));
    
    auto settingsButton = ui::Button::create("Settings.png");
    settingsButton->setPosition(Vec2(42, visibleSize.height - 42));
    settingsButton->addTouchEventListener(CC_CALLBACK_2(GameHUDLayer::touchEvent, this));
    
    this->addChild(settingsButton);
    
    return true;
}

void GameHUDLayer::touchEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::MOVED:
            break;
        case ui::Widget::TouchEventType::ENDED:
            this->showSettings();
            break;
        case ui::Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
}
void GameHUDLayer::showSettings()
{
    this->getGamePlayLayer();
    if(this->layerGamePlay!=NULL)
    {
        this->layerGamePlay->showSettings();
    }
}

GamePlay* GameHUDLayer::getGamePlayLayer()
{
    if(this->layerGamePlay==NULL)
    {
        auto parentscene = Director::getInstance()->getRunningScene();
        if(parentscene!=nullptr)
        {
            this->layerGamePlay = (GamePlay*)parentscene->getChildByTag(LAYER_TAG_GAMEPLAY);
        }
    }
    return this->layerGamePlay;
}

void GameHUDLayer::setLevelScore(int score)
{
    char scoreString[64];
    sprintf(scoreString, "Score %d", score);
    this->levelScoreLabel->setString(scoreString);
}

void GameHUDLayer::setGameScore(int score)
{
    char scoreString[64];
    sprintf(scoreString, "Score %d", score);
    this->gameScoreLabel->setString(scoreString);
}

void GameHUDLayer::setLevel(int level)
{
    char levelString[64];
    sprintf(levelString, "Level %d", level);
    this->levelLabel->setString(levelString);
}

Label* GameHUDLayer::addLabel(const std::string fontname, const float fontSize, const char *text, const cocos2d::Vec2 anchor, const cocos2d::Vec2 position)
{
    TTFConfig config(kFontName, fontSize);
	Label *theLabel = Label::createWithTTF(config, text);
	theLabel->setAnchorPoint(anchor);
	theLabel->setPosition(position);
	theLabel->setColor(Color3B::RED);
	this->addChild(theLabel, 100);
	return theLabel;
}
