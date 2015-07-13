//
//  Progress.cpp
//  WriteMouseTest
//
//  Created by wc on 15/3/10.
//
//

#include "Progress.h"
#include "Util.h"
#include "Mouse.h"
#include "GameOver.h"

#define SCALE 0.6
#define WORMSCALE 0.4

float Progress::distance = 0.0;

bool Progress::init() {
	if (!Sprite::init())
		return false;
	initDistance();
	size = Director::getInstance()->getVisibleSize();
	auto pathBg = Sprite::createWithSpriteFrameName("progress-before.png");
	pathBg->setAnchorPoint(Vec2(1, 0));
	pathBg->setScale(SCALE);
	pathBg->setPosition(size.width - 10, size.height / 12);
	this->addChild(pathBg, 1);
	
	auto pathProgressLine = Sprite::createWithSpriteFrameName("progress-after.png");

	pathProgress = ProgressTimer::create(pathProgressLine);
	pathProgress->setBarChangeRate(Point(1, 0));
	pathProgress->setType(ProgressTimer::Type::BAR);
	pathProgress->setMidpoint(Point(0, 1));
	pathProgress->setPercentage(0.0f);
	pathProgress->setAnchorPoint(Vec2(1, 0));
	pathProgress->setScale(SCALE);
	pathProgress->setPosition(size.width - 10, size.height / 12);
	this->addChild(pathProgress, 2);

	worm = Sprite::createWithSpriteFrameName("worm.png");
	worm->setAnchorPoint(Vec2(0.5, 0));
	worm->setPosition(pathBg->getPosition().x - pathBg->getContentSize().width * SCALE,
		pathProgress->getPosition().y + pathProgress->getContentSize().height * SCALE / 1.5);
	worm->setScale(WORMSCALE);
	this->addChild(worm);
	this->setZOrder(2);

	return true;
}

void Progress::initDistance() {
	distance = 0.0;
}

void Progress::update() {
	auto percent = distance / Util::getInstance()->getDistanceTravelled();
	if (percent < 100) {
		pathProgress->setPercentage(percent);
		moveWorm(percent * pathProgress->getContentSize().width * SCALE / 100);
	}
	else {
		auto gameover = (GameOver*)Director::getInstance()->getRunningScene()->getChildByTag(GAMEOVERTAG);
		gameover->gameOver(true);
	}
}

void Progress::setDistance(float distance_) {
	distance = distance_;
}

float Progress::getDistance() {
	return distance;
}

void Progress::moveWorm(float xChange) {
	auto position = worm->getPosition();
	worm->setPosition(pathProgress->getPosition().x - pathProgress->getContentSize().width * SCALE + xChange, position.y);
}


float ProgressBlood::initBlood = 0;
bool ProgressBlood::init() {
	if (!Sprite::init())
		return false;

	initBlood = Util::getInstance()->getInitMouseLife();
	size = Director::getInstance()->getVisibleSize();

	auto pathBg = Sprite::create("images/progressBlood-before.png");
	pathBg->setAnchorPoint(Vec2(0, 1));
	pathBg->setScale(1.3, 1.4);
	pathBg->setPosition(10, size.height / 1.03);
	this->addChild(pathBg, 1);

	auto pathProgressLine = Sprite::create("images/progressBloood-after.png");
	pathProgressLine->setPosition(size.width / 2, size.height / 2);

	pathProgressBlood = ProgressTimer::create(pathProgressLine);
	pathProgressBlood->setBarChangeRate(Point(1, 0));
	pathProgressBlood->setType(ProgressTimer::Type::BAR);
	pathProgressBlood->setMidpoint(Point(0, 1));
	pathProgressBlood->setPercentage(100.0f);
	pathProgressBlood->setAnchorPoint(Vec2(0, 1));
	pathProgressBlood->setScale(1.3, 1.4);
	pathProgressBlood->setPosition(10, size.height / 1.03);
	this->addChild(pathProgressBlood, 2);
	this->setZOrder(2);

	return true;
}

void ProgressBlood::update() {
	if (Mouse::getLife() > 0) {
		auto percent = (Mouse::getLife() / initBlood) * 100;
		pathProgressBlood->setPercentage(percent);
	}
	else {
		auto gameover = (GameOver*)Director::getInstance()->getRunningScene()->getChildByTag(GAMEOVERTAG);
		gameover->gameOver(false);
	}
}