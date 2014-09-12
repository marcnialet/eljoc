#include "SwipeLayer.h"
#include "Defines.h"
#include "Utils.h"

USING_NS_CC;

bool SwipeLayer::init()
{
    if( !CCLayerColor::initWithColor(COLOR_RED) )
    {
        return false;
    }
    
    this->swipeThreshold = Director::getInstance()->getVisibleSize().width * 0.05;
    
    this->listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(SwipeLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(SwipeLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(SwipeLayer::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(SwipeLayer::onTouchesCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    return true;
}

void SwipeLayer::onGesture(GestureType gesture)
{
    log("onGesture");
}

void SwipeLayer::update(float dt)
{
    this->processGesture();
}

void SwipeLayer::onTouchesBegan(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesBegan");
    this->initialTouchPos.clear();
    this->currentTouchPos.clear();
    
    this->isTouchClicked = false;
    this->isTouchDown = true;
    for (auto &touch: touches)
    {
        this->initialTouchPos.push_back(touch->getLocation());
        this->currentTouchPos.push_back(touch->getLocation());
    }
}

void SwipeLayer::onTouchesMoved(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesMoved");
    this->currentTouchPos.clear();
    for (auto &touch: touches)
    {
        this->currentTouchPos.push_back(touch->getLocation());
    }
}

void SwipeLayer::onTouchesEnded(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesEnded");
    if(this->isTouchDown)
    {
        this->isTouchClicked = true;
    }
    this->isTouchDown = false;
    this->initialTouchPos.clear();
}

void SwipeLayer::onTouchesCancelled(const vector<Touch*>& touches, Event* event)
{
    // log("onTouchesCancelled");
}

GestureType SwipeLayer::getGestureType()
{
    GestureType gesture = GestureType::None;
    if(initialTouchPos.size()<=0 || currentTouchPos.size()<=0) return gesture;
        
    bool single = currentTouchPos.size()==1 && currentTouchPos.size()==1;
    bool multiple = currentTouchPos.size()>1 && currentTouchPos.size()>1;
    if(single||multiple)
    {
        if (initialTouchPos[0].x - currentTouchPos[0].x > this->swipeThreshold)
        {
            if(multiple)
            {
                gesture = GestureType::Swipe_Left_Multi;
                // log("SWIPED LEFT MULTIPLE");
            }
            else
            {
                gesture = GestureType::Swipe_Left;
                // log("SWIPED LEFT");
            }
        }
        else if (initialTouchPos[0].x - currentTouchPos[0].x < - this->swipeThreshold)
        {
            if(multiple)
            {
                gesture = GestureType::Swipe_Right_Multi;
                // log("SWIPED RIGHT MULTIPLE");
            }
            else
            {
                gesture = GestureType::Swipe_Right;
                // log("SWIPED RIGHT");
            }
        }
        
        else if (initialTouchPos[0].y - currentTouchPos[0].y > this->swipeThreshold)
        {
            if(multiple)
            {
                gesture = GestureType::Swipe_Down_Multi;
                // log("SWIPED DOWN MULTIPLE");
            }
            else
            {
                gesture = GestureType::Swipe_Down;
                // log("SWIPED DOWN");
            }
        }
        else if (initialTouchPos[0].y - currentTouchPos[0].y < - this->swipeThreshold)
        {
            if(multiple)
            {
                gesture = GestureType::Swipe_Up_Multi;
                // log("SWIPED UP MULTIPLE");
            }
            else
            {
                gesture = GestureType::Swipe_Up;
                // log("SWIPED UP");
            }
        }
        else if(this->isTouchClicked)
        {
            this->isTouchClicked = false;
            gesture = GestureType::Single_Click;
            // log("Single Click");
        }
    }
    return gesture;
}

void SwipeLayer::processGesture()
{
    if (true == isTouchDown)
    {
        GestureType gesture = this->getGestureType();
        if (gesture!=GestureType::None)
        {
            this->onGesture(gesture);
            
            this->initialTouchPos.clear();
            this->currentTouchPos.clear();
            isTouchDown = false;
        }
    }
    else
    {
        GestureType gesture = this->getGestureType();
        if(gesture == GestureType::Single_Click)
        {
            this->onGesture(gesture);
        }
    }
}