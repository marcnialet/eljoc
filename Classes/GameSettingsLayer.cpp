#include "GameSettingsLayer.h"
#include "GamePlayScene.h"
#include "Defines.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameSettingsLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "Cancel.png",
                                           "Cancel.png",
                                           CC_CALLBACK_1(GameSettingsLayer::menuPlayCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/2 - closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto label = LabelTTF::create("Main Menu", "Arial", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    return true;
}


void GameSettingsLayer::menuPlayCallback(Ref* pSender)
{
    this->getGamePlayLayer();
    if(this->layerGamePlay!=NULL)
    {
        this->layerGamePlay->closeSettings();
    }
}

GamePlay* GameSettingsLayer::getGamePlayLayer()
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
