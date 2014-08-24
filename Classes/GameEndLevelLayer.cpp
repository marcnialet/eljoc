#include "GameEndLevelLayer.h"
#include "Defines.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameEndLevelLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->endlevelLabel = this->addLabel(kFontName, 48, "Level Completed!", Vec2(0.0, 1.0), Vec2(10, Director::getInstance()->getVisibleSize().height/2));
    
    return true;
}

Label* GameEndLevelLayer::addLabel(const std::string fontname, const float fontSize, const char *text,
                              const cocos2d::Vec2 anchor, const cocos2d::Vec2 position)
{
    TTFConfig config(kFontName, fontSize);
	Label *theLabel = Label::createWithTTF(config, text);
	theLabel->setAnchorPoint(anchor);
	theLabel->setPosition(position);
	theLabel->setColor(Color3B::RED);
	this->addChild(theLabel, 100);
	return theLabel;
}