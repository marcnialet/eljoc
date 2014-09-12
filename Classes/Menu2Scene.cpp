#include "SwipeLayer.h"
#include "Menu1Scene.h"
#include "Menu2Scene.h"
#include "Menu3Scene.h"
#include "Defines.h"
#include "Utils.h"

USING_NS_CC;

Scene* Menu2Scene::createScene()
{
    auto scene = Scene::create();
    auto layer = Menu2Scene::create();
    scene->addChild(layer);
    return scene;
}

bool Menu2Scene::init()
{
    if( !BaseMenuLayer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto breadcrumb = Sprite::create("breadcrumb_2_3.png");
    breadcrumb->setPosition(Vec2(origin.x + visibleSize.width/2, 170));
    this->addChild(breadcrumb, 1);
    
    return true;
}

void Menu2Scene::onNextMenu()
{
    auto newScene = Menu3Scene::createScene();
    auto transition = TransitionMoveInR::create(0.5, newScene);
    Director::getInstance()->replaceScene(transition);

}

void Menu2Scene::onPreviousMenu()
{
    auto newScene = Menu1Scene::createScene();
    auto transition = TransitionMoveInL::create(0.5, newScene);
    Director::getInstance()->replaceScene(transition);

}