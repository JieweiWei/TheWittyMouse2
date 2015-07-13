//
//  Prop.cpp
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#include "Prop.h"
#include "Util.h"
#include "AnimationUtils.h"

bool Prop::init() {
	if (!Sprite::init())
		return true;
	this->setScale(0.8);
	size = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Vec2(0, 2 * size.height / 3));
	this->setTag(PROPTAG);
	attribute = FERTILIZER;
	isTouch = false;

	return true;
}

bool Fertilizer::init() {
	if (!Prop::init())
		return false;
	this->setSpriteFrame("chemical-fertilizer-in-air-bladder.png");
	attribute = FERTILIZER;

	return true;
}

bool Block::init() {
	if (!Prop::init())
		return false;
	this->setSpriteFrame("shovel-in-air-bladder.png");
	attribute = BLOCK;

	return true;
}

bool Magent::init() {
	if (!Prop::init())
		return false;
	this->setSpriteFrame("magnet-in-air-bladder.png");
	attribute = MAGNET;
	return true;
}


Attribute Prop::getAttribute() {
	return attribute;
}

void Prop::run() {
	this->stopAllActions();

	ccBezierConfig bezier2;

	bezier2.controlPoint_1 = Vec2((rand() % 5) * (size.width / 8), (rand() % 2 + 1) * size.height / 3);
	bezier2.controlPoint_2 = Vec2((rand() % 5) * size.width / 4, (rand() % 2 + 1) * size.height / 4);
	bezier2.endPosition = Vec2(size.width + this->getContentSize().width + 25, size.height / 2);
	auto bezierTo1 = BezierTo::create(2, bezier2);

	auto rotate = RotateTo::create(2, 720);

	auto actions = Spawn::create(bezierTo1, rotate, NULL);
	this->runAction(actions);
}

void Prop::burst(Vec2 containerPosition, Size containerSize) {
	this->stopAllActions();
	auto moveTo2 = MoveTo::create(0.5, Vec2(containerPosition.x + containerSize.width / 2,
		containerPosition.y + containerSize.height / 2));
	auto scaleTo2 = ScaleTo::create(0.5, 0.1);
	auto actions2 = Spawn::create(moveTo2, scaleTo2, NULL);
	auto cf = CallFunc::create(CC_CALLBACK_0(Prop::removeSelf, this, this));
	auto seq = Sequence::create(actions2, cf, NULL);
	this->runAction(seq);
}

void Fertilizer::burst(Vec2 containerPosition, Size containerSize) {
	this->setSpriteFrame("chemical-fertilizer.png");
	Prop::burst(containerPosition, containerSize);
}

void Block::burst(Vec2 containerPosition, Size containerSize) {
	this->setSpriteFrame("shovel.png");
	Prop::burst(containerPosition, containerSize);
}

void Magent::burst(Vec2 containerPosition, Size containerSize) {
	this->setSpriteFrame("magnet.png");
	Prop::burst(containerPosition, containerSize);
}


void Prop::removeSelf(Prop *p) {
	p->removeFromParentAndCleanup(true);
}