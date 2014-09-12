#include "SwipeLayer.h"
#include "Menu2Scene.h"
#include "Menu3Scene.h"
#include "Defines.h"
#include "Utils.h"

USING_NS_CC;

Scene* Menu3Scene::createScene()
{
    auto scene = Scene::create();
    auto layer = Menu3Scene::create();
    scene->addChild(layer);
    return scene;
}

bool Menu3Scene::init()
{
    if( !BaseMenuLayer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto breadcrumb = Sprite::create("breadcrumb_3_3.png");
    breadcrumb->setPosition(Vec2(origin.x + visibleSize.width/2, 170));
    this->addChild(breadcrumb, 1);
    
    return true;
}

void Menu3Scene::onNextMenu()
{
}

void Menu3Scene::onPreviousMenu()
{
    auto newScene = Menu2Scene::createScene();
    auto transition = TransitionMoveInL::create(0.5, newScene);
    Director::getInstance()->replaceScene(transition);
}