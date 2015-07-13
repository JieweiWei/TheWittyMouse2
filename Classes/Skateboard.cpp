#include "Skateboard.h"
#include "MainScene.h"
#include "Util.h"

bool Skateboard::init() {
	if (!Sprite::init())
		return false;

	size = Director::getInstance()->getVisibleSize();
	this->setSpriteFrame("skateboard-shoes.png");
	this->setPosition(size.width * 1.5, size.height / 2.5);
	return true;
}

void Skateboard::actionAfterHit() {
	this->stopAllActions();
	auto moveTo = MoveTo::create(0.5, Vec2(size.width, size.height / 4.8));
	auto scaleTo = ScaleTo::create(0.5, 1.7);
	auto actions = Spawn::create(moveTo, scaleTo, NULL);
	auto seq = Sequence::create(
		actions,
		CallFunc::create(this, callfunc_selector(Skateboard::resetSkateboardIsFinishFlag)),
		NULL
		);
	this->runAction(seq);
}

void Skateboard::resetSkateboardIsFinishFlag() {
	auto mainScene = (MainScene*)Director::getInstance()->getRunningScene()->getChildByTag(GAMETAG);
	mainScene->setIsSkateboardFinishAction();
}