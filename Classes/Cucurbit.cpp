//
//  Cucurbit.cpp
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#include "Cucurbit.h"
#include "Util.h"
#include <time.h>

float Cucurbit::height = 0;
Cucurbit* Cucurbit::createCucurbit() {
    auto cucurbit = new Cucurbit();
    if (cucurbit && cucurbit->init()) {
        cucurbit->autorelease();
        return cucurbit;
    }
    CC_SAFE_DELETE(cucurbit);
    return nullptr;
}

bool Cucurbit::init() {
    if (!Sprite::init())
        return false;
    
    size = Director::getInstance()->getVisibleSize();
	height = size.height - size.height / 20;
    type = 0;
    
    auto typeOfCucurbit = (int)(rand() % 10);
    auto sizeOfCucurbit = (int)(rand() % 4);
    switch(typeOfCucurbit) {
        case 0:
            this->setSpriteFrame("redHuLuBig.png");
            type = 2;
            break;
        default:
        {
            switch(sizeOfCucurbit) {
                case 0:
                    this->setSpriteFrame("greenHuLuBig.png");
                    type = 1;
                    break;
                default:
                    this->setSpriteFrame("yellowHuLuSmall.png");
                    type = 0;
                    break;
            }
        }
            break;
    }
    growTime = 0;
    isCut = false;
	auto width_ = size.width + rand() % (int)(size.width);
    this->setAnchorPoint(Vec2(1, 1));
	this->setPosition(Vec2(width_, height));
    this->setTag(CUCRBITTAG);
    return true;
}

float Cucurbit::initialHeight() {
	return height;
}

bool Cucurbit::grow() {
    growTime++;
    if (type == 0 && growTime == 3) {
        this->setSpriteFrame("greenHuLuBig.png");
		createGrowAction();
        type = 1;
        growTime = 0;
    } else if (type == 1 && growTime == 3) {
        this->setSpriteFrame("redHuLuBig.png");
		createGrowAction();
        type = 2;
        growTime = 0;
        return true;
    } else if(type == 2 && growTime == 1){
        growTime = 0;
        return true;
    }
    return false;
}

void Cucurbit::growUp() {
	if (type == 0) {
		growTime = 2;
		grow();
		createGrowAction();
	}
}

void Cucurbit::createGrowAction() {
	auto scaleTo1 = ScaleTo::create(0, 0.98);
	auto scaleTo2 = ScaleTo::create(0.2, 1);
	auto seq = Sequence::create(scaleTo1, scaleTo2, NULL);
	this->runAction(seq);
}