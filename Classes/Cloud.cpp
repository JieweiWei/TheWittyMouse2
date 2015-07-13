#include "Cloud.h"
#include "Util.h"
#include <stdlib.h>

bool Cloud::init() {
	if (!Sprite::init())
		return false;

	size = Director::getInstance()->getVisibleSize();
	int cloudType = rand() % 3;
	switch (cloudType) {
	case 0:
		this->setSpriteFrame("cloud.png");
		break;
	default:
		this->setSpriteFrame("cloud2.png");
		break;
	}
	this->setTag(CLOUDTAG);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(Vec2(size.width + (1 + rand() % 3) * this->getContentSize().width, (4 + rand() % 2) * size.height / 6));
	this->setScale(0.7);

	return true;
}

void Cloud::cloudAction() {
	auto moveTo = MoveTo::create(10, Vec2(-(this->getContentSize().width + 10), (3 + rand() % 2) * size.height / 5));
	auto cf = CallFunc::create(CC_CALLBACK_0(Cloud::removeSelf, this, this));
	auto seq = Sequence::create(moveTo, cf, NULL);
	this->runAction(seq);
}

void Cloud::removeSelf(Cloud *c) {
	c->removeFromParentAndCleanup(true);
}