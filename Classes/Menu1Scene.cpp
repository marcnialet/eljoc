#include "SwipeLayer.h"
#include "Menu1Scene.h"
#include "Menu2Scene.h"
#include "Defines.h"
#include "Utils.h"

USING_NS_CC;

Scene* Menu1Scene::createScene()
{
    auto scene = Scene::create();
    auto layer = Menu1Scene::create();
    scene->addChild(layer);
    return scene;
}

bool Menu1Scene::init()
{
    if( !BaseMenuLayer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto breadcrumb = Sprite::create("breadcrumb_1_3.png");
    breadcrumb->setPosition(Vec2(origin.x + visibleSize.width/2, 170));
    this->addChild(breadcrumb, 1);
    
    return true;
}

void Menu1Scene::onNextMenu()
{
    auto newScene = Menu2Scene::createScene();
    auto transition = TransitionMoveInR::create(0.5, newScene);
    Director::getInstance()->replaceScene(transition);
}

void Menu1Scene::onPreviousMenu()
{
}