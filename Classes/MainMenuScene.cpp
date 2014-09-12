#include "MainMenuScene.h"
#include "GamePlayScene.h"
#include "SwipeLayer.h"
#include "Menu1Scene.h"

USING_NS_CC;

Scene* MainMenuLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuLayer::init()
{
    if( !CCLayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto playbuttonItem = MenuItemImage::create("button_play.png", "button_play.png", CC_CALLBACK_1(MainMenuLayer::onMenuPlayButton, this));
    auto tutorialbuttonItem = MenuItemImage::create("button_tutorial.png", "button_tutorial.png", CC_CALLBACK_1(MainMenuLayer::onMenuTutorialButton, this));
    auto menubuttonItem = MenuItemImage::create("button_menu.png", "button_menu.png", CC_CALLBACK_1(MainMenuLayer::onMenuMenuButton, this));
	

    auto menu = Menu::create(playbuttonItem, tutorialbuttonItem, menubuttonItem, NULL);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/2 - playbuttonItem->getContentSize().height/2));
    this->addChild(menu, 1);
    
    return true;
}


void MainMenuLayer::onMenuPlayButton(Ref* pSender)
{
     auto scene = GamePlay::createScene();
    
    Director::getInstance()->pushScene(scene);

}

void MainMenuLayer::onMenuTutorialButton(Ref* pSender)
{
    
    
}

void MainMenuLayer::onMenuMenuButton(Ref* pSender)
{
    auto scene = Menu1Scene::createScene();
    
    Director::getInstance()->pushScene(scene);
    
}
