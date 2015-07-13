//
//  Mouse.cpp
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#include "Mouse.h"
#include "Util.h"
#include "AnimationUtils.h"
#include "Snare.h"
#include "MainScene.h"

int Mouse::IQ = 0;
int Mouse::life = 10;
float Mouse::mousePositionY = 0;
float Mouse::mousePositionX = 0;
float Mouse::mouseWidth = 0;

Mouse* Mouse::createMouse() {
	auto mouse = new Mouse();
	if (mouse && mouse->init()) {
		mouse->autorelease();
		return mouse;
	}
	CC_SAFE_DELETE(mouse);
	return nullptr;
}

bool Mouse::init() {
	if (!Sprite::init())
		return false;

	fallIn = false;
	isSpeedUp = false;
	isSlowDown = false;
	isJump = false;
	fallingSnare = nullptr;
	size = Director::getInstance()->getVisibleSize();
	this->createWithSpriteFrameName("run00.png");
	this->setTag(MOUSETAG);
	this->setAnchorPoint(Vec2(1, 0.5));
	mousePositionY = size.height / 4;
	mousePositionX = size.width / 3;
	this->setPosition(Vec2(mousePositionX, mousePositionY));
	this->setScale(0.4);
	this->setZOrder(1);
	mouseWidth = this->getContentSize().width;

	return true;
}

void Mouse::run() {
	this->stopAllActions();
	this->runAction(createRunningSequence());
}

void Mouse::jump() {
	if (isJump)
		return;
	isJump = true;
	auto seq = Sequence::create(
		CallFunc::create(this, callfunc_selector(Mouse::setJump)),
		Spawn::create(JumpTo::create(1, this->getPosition(), this->getContentSize().height / 2.5, 1),
		createAction("jump", 8, 0.05f, 1), NULL),
		CallFunc::create(this, callfunc_selector(Mouse::resetJump)),
		createRunningSequence(), NULL);
	this->runAction(seq);
}

void Mouse::fall(Snare* snare) {
	fallingSnare = snare;
	fallIn = true;
	Vec2 mousePosition = Vec2(mousePositionX, mousePositionY);
	auto seq = Sequence::create(
		CallFunc::create(this, callfunc_selector(Mouse::setFallDif)),
		Spawn::create(createAction("fall", 0.1, 0.08f, 1),
		MoveTo::create(0.56, Vec2(mousePositionX, mousePositionY - 70)), NULL),
		Spawn::create(createAction("fallend", 0.1, 0.08f, 1), MoveTo::create(0.56, mousePosition), NULL),
		CallFunc::create(this, callfunc_selector(Mouse::moveMouseBehineSnare)),
		createRunningSequence(), NULL);
	this->runAction(seq);
}


void Mouse::dizzy() {
	Sequence* seq;

	if (!fallIn) {
		seq = Sequence::create(
			CallFunc::create(this, callfunc_selector(Mouse::setDizzyDif)),
			Spawn::create(createAction("dizzy", 0, 0.15f, 1), MoveTo::create(0.1, Vec2(mousePositionX, mousePositionY)), NULL),
			CallFunc::create(this, callfunc_selector(Mouse::resetDif)),
			createRunningSequence(), NULL);
	}
	else {
		float fallPosition = 0;
		if (fallingSnare == nullptr) {
			fallPosition = this->getPosition().x;
		}
		else {
			fallPosition = fallingSnare->getPosition().x +fallingSnare->getContentSize().width / 6;
		}

		seq = Sequence::create(
			CallFunc::create(this, callfunc_selector(Mouse::setDizzyDif)),
			Spawn::create(createAction("dizzy", 0, 0.15f, 1),
			MoveTo::create(0.1, Vec2(fallPosition, mousePositionY - 70)), NULL),
			Spawn::create(createAction("fallend", 0.2, 0.15f, 1),
			MoveTo::create(0.75, Vec2(this->getPosition().x, mousePositionY)), NULL),
			CallFunc::create(this, callfunc_selector(Mouse::moveMouseBehineSnare)),
			createRunningSequence(), NULL);
	}
	this->runAction(seq);
}

void Mouse::speedUp() {
	if (isSpeedUp)
		return;

	auto seq = Sequence::create(
		CallFunc::create(this, callfunc_selector(Mouse::setSpeedup)),
		Spawn::create(MoveTo::create(0.42, Vec2(this->getPosition().x + 20, this->getPosition().y)),
		createAction("run", 12, 0.03f, 1), NULL),
		CallFunc::create(this, callfunc_selector(Mouse::resetSpeedup)),
		createRunningSequence(), NULL);

	this->runAction(seq);
}

void Mouse::slowDown() {
	if (isSlowDown)
		return;
	auto moveTo = MoveTo::create(0.42, Vec2(this->getPosition().x - 20, this->getPosition().y));
	auto actions = Spawn::create(moveTo, createAction("run", 2, 0.06f, 1), NULL);
	auto seq = Sequence::create(
		CallFunc::create(this, callfunc_selector(Mouse::setSlowDown)),
		actions,
		CallFunc::create(this, callfunc_selector(Mouse::resetSlowDown)),
		createRunningSequence(), NULL);

	this->runAction(seq);
}

void Mouse::scooter() {
	auto seq = Sequence::create(
		CallFunc::create(this, callfunc_selector(Mouse::setSkateboardDif)),
		Animate::create(AnimationUtils::createWithNameAndStartIndex("scooter", 1, 0.1f, 1)),
		CallFunc::create(this, callfunc_selector(Mouse::resetSkateBoardFlag)),
		CallFunc::create(this, callfunc_selector(Mouse::resetIsAction)),
		createRunningSequence(), NULL);

	this->runAction(seq);
}

int Mouse::getIQ() {
	if (IQ >= 0)
		return IQ;
	return 0;
}

void Mouse::setIQ(int IQ_) {
	if (IQ_ > 100)
		IQ = 100;
	else {
		IQ = IQ_;
	}
}

int Mouse::getLife() {
	if (life >= 0)
		return life;
	return 0;
}

void Mouse::setLife(int life_) {
	life = life_;
}

Animate* Mouse::createAction(const char* filename, float dif_, float speed, int isLoop) {
	Util::getInstance()->setDif(dif_);
	this->setScale(0.4);
	this->stopAllActions();
	return Animate::create(AnimationUtils::createWithName(filename, speed, isLoop));
}

Sequence* Mouse::createRunningSequence() {
	return 
		Sequence::create(
		CallFunc::create(this, callfunc_selector(Mouse::resetSlowDown)),
		CallFunc::create(this, callfunc_selector(Mouse::resetSpeedup)),
		CallFunc::create(this, callfunc_selector(Mouse::resetJump)),
		CallFunc::create(this, callfunc_selector(Mouse::resetDif)), 
		CallFunc::create(this, callfunc_selector(Mouse::resetFallingSnare)),
		Spawn::create(createAction("run", 6, 0.05f, -1), MoveTo::create(0.1, Vec2(mousePositionX, mousePositionY)),
		NULL), NULL);
}

void Mouse::resetIsAction() {
	auto mainScene = (MainScene*)Director::getInstance()->getRunningScene()->getChildByTag(GAMETAG);
	mainScene->moveMouseBehineSnare();
	mainScene->resetIsAction();
}

void Mouse::resetFallingSnare() {
	fallingSnare = nullptr;
}

void Mouse::moveMouseBehineSnare() {
	Util::getInstance()->setDif(6);
	fallIn = false;
}

void Mouse::resetDif() {
	Util::getInstance()->setDif(6);
}

void Mouse::resetJump() {
	resetIsAction();
	auto mainScene = (MainScene*)Director::getInstance()->getRunningScene()->getChildByTag(GAMETAG);
	mainScene->resetIsJump();
	isJump = false;
}

void Mouse::resetSpeedup() {
	resetIsAction();
	isSpeedUp = false;
}
void Mouse::resetSlowDown() {
	resetIsAction();
	isSlowDown = false;
}

void Mouse::resetSkateBoardFlag() {
	auto mainScene = (MainScene*)Director::getInstance()->getRunningScene()->getChildByTag(GAMETAG);
	mainScene->resetIsSkateboardHit();
	this->setPosition(Vec2(mousePositionX, mousePositionY));
	this->setScale(0.4);
}

void Mouse::setSpeedup() {
	Util::getInstance()->setDif(12);
	isSpeedUp = true;
}
void Mouse::setSlowDown() {
	Util::getInstance()->setDif(2);
	isSlowDown = true;
}

void Mouse::setJump(){
	Util::getInstance()->setDif(12);
	isJump = true;
}

void Mouse::setSkateboardDif() {
	this->setPosition(Vec2(mousePositionX, size.height / 3.5));
	this->setScale(0.3);
	Util::getInstance()->setDif(10);
}

void Mouse::setDizzyDif() {
	resetIsAction();
	Util::getInstance()->setDif(0);
}

void Mouse::setFallDif() {
	Util::getInstance()->setDif(1.2);
}