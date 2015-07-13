//
//  PropContainer.cpp
//  WittedMouse
//
//  Created by wc on 15/2/26.
//
//

#include "PropContainer.h"
#include "MainScene.h"
#include "Util.h"

bool PropContainer::init() {
    if (!Sprite::init())
        return false;

	this->setAnchorPoint(Vec2(0, 0));
    size = Director::getInstance()->getVisibleSize();
    numLabel = Label::createWithBMFont("fonts/font-issue1343.fnt", "0");
    propNum = 0;
    this->addChild(numLabel);
    return true;
}

bool FertilizerContainer::init() {
	if (!PropContainer::init())
		return false;
	this->setSpriteFrame("chemical-fertilizer.png");
	this->setPosition(2, size.height / 4.5 + this->getContentSize().height / 2);
	numLabel->setPosition(this->getContentSize().width + 20, this->getContentSize().height / 2);
	attribute = FERTILIZER;
	return true;
}

bool MagentContainer::init() {
	if (!PropContainer::init())
		return false;
	this->setSpriteFrame("magnet.png");
	this->setPosition(2, size.height / 4.5 + 4 * this->getContentSize().height / 2);
	numLabel->setPosition(this->getContentSize().width + 20, this->getContentSize().height / 2);
	attribute = MAGNET;
	return true;
}

bool BlockContainer::init() {
	if (!PropContainer::init())
		return false;
	this->setSpriteFrame("shovel.png");
	this->setPosition(2, size.height / 4.5 + 8 * this->getContentSize().height / 2);
	numLabel->setPosition(this->getContentSize().width + 20, this->getContentSize().height / 2);
	attribute = BLOCK;
	return true;
}

void PropContainer::addAProp() {
    propNum++;
}

bool PropContainer::deleteAProp() {
	if (propNum > 0) {
		propNum--;
		return true;
	}
	return false;
}

bool BlockContainer::deleteAProp() {
	if (propNum > 0) {
		propNum--;
		return true;
	}
	return false;
}

bool PropContainer::isEmpty() {
    return propNum == 0;
}

void PropContainer::updateContainer() {
    String *propNumString = String::createWithFormat("%d",  propNum);
    numLabel->setString(propNumString->getCString());
}

void  PropContainer::propEffectAction(CucrbitManage* cucrbitManage) {

}

void FertilizerContainer::propEffectAction(CucrbitManage* cucrbitManage) {
	cucrbitManage->allCucrbitGrowUp();
}

void BlockContainer::propEffectAction(CucrbitManage* cucrbitManage) {
	auto mainScene = (MainScene*)Director::getInstance()->getRunningScene()->getChildByTag(GAMETAG);
	mainScene->setIsSholvePropChose(true);
}

void MagentContainer::propEffectAction(CucrbitManage* cucrbitManage) {
	cucrbitManage->allCucrbitFallDown();
}

int PropContainer::getPropNum() const {
	return propNum;
}