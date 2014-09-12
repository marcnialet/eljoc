
#include "BaseMenuLayer.h"
#include "Defines.h"
#include "Utils.h"

USING_NS_CC;

bool BaseMenuLayer::init()
{
    if( !SwipeLayer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto mainmenubuttonItem = MenuItemImage::create("button_mainmenu.png", "button_mainmenu.png", CC_CALLBACK_1(BaseMenuLayer::onMainMenuButton, this));
    auto menu = Menu::create(mainmenubuttonItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width/2, 100));
    this->addChild(menu, 1);
    
    return true;
}

void BaseMenuLayer::onMainMenuButton(Ref* pSender)
{
    Director::getInstance()->popScene();
}

void BaseMenuLayer::onGesture(GestureType gesture)
{
    if(gesture == GestureType::Swipe_Right)
    {
        this->onPreviousMenu();
    }
    else if(gesture == GestureType::Swipe_Left)
    {
        this->onNextMenu();        
    }
}

void BaseMenuLayer::onNextMenu()
{
    log("onNextMenu");
}
void BaseMenuLayer::onPreviousMenu()
{
    log("onPreviousMenu");
}