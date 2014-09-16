#include "GameHUDLayer.h"
#include "GamePlayScene.h"
#include "Defines.h"
#include "Utils.h"

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
    
    this->gameElapsedTimeLabel = this->addLabel(kFontName, 18, "Time 0", Vec2(0.0, 1.0), Vec2(visibleSize.width-150, visibleSize.height - 10));
    this->gameScoreLabel = this->addLabel(kFontName, 48, "Score 0", Vec2(0.0, 1.0), Vec2(100, visibleSize.height - 60));
    this->levelLabel = this->addLabel(kFontName, 48, "Level 0", Vec2(0.0, 1.0), Vec2(100, visibleSize.height - 10));
    
    this->levelScoreLabel = this->addLabel(kFontName, 24, "Score 0", Vec2(0.0, 1.0), Vec2(20, 180));
    this->levelElapsedTimeLabel = this->addLabel(kFontName, 24, "Time 0", Vec2(0.0, 1.0), Vec2(220, 180));
    
    this->levelPiecesLabel = this->addLabel(kFontName, 24, "Pieces 0", Vec2(0.0, 1.0), Vec2(20, 95));
    this->levelCombosLabel = this->addLabel(kFontName, 24, "Combos 0", Vec2(0.0, 1.0), Vec2(160, 95));
    this->levelChainsLabel = this->addLabel(kFontName, 24, "Chains 0", Vec2(0.0, 1.0), Vec2(300, 95));
    
    
    this->levelPiecesByTypeLabel = this->addLabel(kFontName, 18, "Pieces 0", Vec2(0.0, 1.0), Vec2(40, 120));
    this->levelCombosByTypeLabel = this->addLabel(kFontName, 18, "Combos 0", Vec2(0.0, 1.0), Vec2(40, 140));
    this->levelChainsByTypeLabel = this->addLabel(kFontName, 18, "Chains 0", Vec2(0.0, 1.0), Vec2(40, 160));
    
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

void GameHUDLayer::setGameScore(int score)
{
    char label[64];
    sprintf(label, "Score %d", score);
    this->gameScoreLabel->setString(label);
}

void GameHUDLayer::setLevel(int level)
{
    char label[64];
    sprintf(label, "Level %d", level);
    this->levelLabel->setString(label);
}

void GameHUDLayer::setLevelScore(int score)
{
    char label[64];
    sprintf(label, "Score %d", score);
    this->levelScoreLabel->setString(label);
}

void GameHUDLayer::setGameElapsedTime(double elapsedtimeMs)
{
    this->gameElapsedTimeLabel->setString("Time: "+  Utils::formatMilliseconds(elapsedtimeMs));
}

void GameHUDLayer::setLevelElapsedTime(double elapsedtimeMs)
{
    this->levelElapsedTimeLabel->setString("Time: "+  Utils::formatMilliseconds(elapsedtimeMs));
}

void GameHUDLayer::setLevelPieces(int pieces)
{
    char label[64];
    sprintf(label, "Pieces %d", pieces);
    this->levelPiecesLabel->setString(label);
}

void GameHUDLayer::setLevelCombos(int combos)
{
    char label[64];
    sprintf(label, "Combos %d", combos);
    this->levelCombosLabel->setString(label);
}

void GameHUDLayer::setLevelChains(int chains)
{
    char label[64];
    sprintf(label, "Chains %d", chains);
    this->levelChainsLabel->setString(label);
    
}

void GameHUDLayer::setLevelPiecesByType(vector<unsigned int> piecesCounter)
{
    string buffer = "Pieces: ";
    for(int i=0; i<piecesCounter.size(); i++)
    {
        int count = piecesCounter[i];
        if(count==0) continue;
        
        char textcount[64];
        sprintf(textcount, "(%d): %d - ", i, count);
        buffer.append(textcount);
    }
        
    this->levelPiecesByTypeLabel->setString(buffer);
}

void GameHUDLayer::setLevelCombosByType(vector<unsigned int> combosCounter)
{
    string buffer = "Combos: ";
    for(int i=0; i<combosCounter.size(); i++)
    {
        int count = combosCounter[i];
        if(count==0) continue;
        
        char textcount[64];
        sprintf(textcount, "(%d): %d - ", i, count);
        buffer.append(textcount);
    }
    
    this->levelCombosByTypeLabel->setString(buffer);
}

void GameHUDLayer::setLevelChainsByType(vector<unsigned int> chainsCounter)
{
    string buffer = "Chains: ";
    for(int i=0; i<chainsCounter.size(); i++)
    {
        int count = chainsCounter[i];
        if(count==0) continue;
        
        char textcount[64];
        sprintf(textcount, "(%d): %d - ", i, count);
        buffer.append(textcount);
    }
    
    this->levelChainsByTypeLabel->setString(buffer);
    
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
