//
//  HUDLayer.cpp
//  WittedMouse
//
//  Created by wc on 15/2/14.
//
//

#include "HUDLayer.h"
#include "Mouse.h"
#include "Util.h"

bool HUDLayer::init(){
    if (!Layer::init())
        return false;
    
    initIQLabel();
    return true;
}

void HUDLayer::initIQLabel() {
    String *IQv = String::createWithFormat("IQ%d",  Mouse::getIQ());
    IQLabel = Label::createWithBMFont("fonts/font-issue1343.fnt", IQv->getCString());
    IQLabel->setAnchorPoint(Vec2(0, 0));
    auto size = Director::getInstance()->getVisibleSize();
    IQLabel->setPosition(Vec2(Util::getInstance()->getPauseMenuWidth() + 30, size.height / 14));
    this->addChild(IQLabel);
}

void HUDLayer::initRouteLabel(){
}

void HUDLayer::updateIQ(){
    String *IQv = String::createWithFormat("IQ%d",  Mouse::getIQ());
    IQLabel->setString(IQv->getCString());
}

void HUDLayer::updateRoute(){
}