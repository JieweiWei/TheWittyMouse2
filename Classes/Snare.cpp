//
//  Snare.cpp
//  WriteMouseTest
//
//  Created by wc on 15/3/10.
//
//

#include "Snare.h"

bool Snare::init() {
	if (!Sprite::init())
		return false;

	this->setAnchorPoint(Vec2(0, 1));
	this->setSpriteFrame("hole.png");
	this->setScale(0.5);
	this->setZOrder(0);
	return true;
}

Snare* Snare::createSnare(Vec2 position) {
	auto snare = new Snare();
	if (snare && snare->init()) {
		snare->setPosition(position);
		snare->autorelease();
		return snare;
	}
	CC_SAFE_DELETE(snare);
	return nullptr;
}