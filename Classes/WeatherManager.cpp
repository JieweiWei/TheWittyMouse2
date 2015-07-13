#include "WeatherManager.h"

bool WeatherManager::init() {
	if (!Sprite::init())
		return false;
	
	weather = Weather::create();
	auto weatherType = weather->getWeatherTypr();
	if (weatherType == rain) {
		auto bg = Sprite::createWithSpriteFrameName("WeatherRainBg.png");
		auto size = Director::getInstance()->getVisibleSize();
		bg->setPosition(size.width / 2, size.height / 2);
		bg->setOpacity(80);
		bg->setScale(2.2);
		bg->setZOrder(2);
		this->addChild(bg);
	}
	else if (weatherType == sunny) {
		auto bg = Sprite::create("images/sun.png");
		auto size = Director::getInstance()->getVisibleSize();
		bg->setAnchorPoint(Vec2(0.5, 0.5));
		bg->setPosition(0, size.height);
		auto rotate = RotateTo::create(10, 720);
		auto repeat = RepeatForever::create(rotate);
		bg->runAction(repeat);
		this->addChild(bg);
	}
	this->setZOrder(1);
	this->addChild(weather);

	return true;
}