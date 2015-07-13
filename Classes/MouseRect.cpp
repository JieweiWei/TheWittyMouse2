//
//  MouseRect.cpp
//  WriteMouseTest
//
//  Created by wc on 15/3/4.
//
//

#include "MouseRect.h"
#include "Cucurbit.h"


bool MouseRect::init() {
	if (!Sprite::init())
		return false;

	auto rect = Rect();
	auto size = Director::getInstance()->getVisibleSize();

	rect.setRect(size.width / 2.4, size.height / 2.8, size.width / 2, size.height / 2.5);
	this->setPosition(size.width / 2.4, size.height / 2.6);
	this->setContentSize(Size(size.width / 2, size.height / 2.8));
	this->setVisible(false);
	//this->setColor(Color3B::BLUE);
	this->setTextureRect(rect);

	return true;
}