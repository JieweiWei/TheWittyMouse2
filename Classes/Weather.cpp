#include "Weather.h"

bool Weather::init() {
	if (!Sprite::init())
		return false;

	weatherType = WeatherInfo::getInstance()->getTodayWeather();

	switch (weatherType) {
	case rain:
		rainEffect();
		break;
	case sunny:
		sunnyEffect();
		break;
	case cloudy:
		cloudyEffect();
		break;
	case windy:
		windyEffect();
		break;
	default: // default style
		break;	
	}

	return true;
}

WeatherStyle Weather::getWeatherTypr() const {
	return weatherType;
}

void Weather::windyEffect() {
	ParticleSystem* emitter;
	auto size = Director::getInstance()->getVisibleSize();

	ParticleSystemQuad* leaf, *flower1, *flower2, *flower3, *grass1;
	emitter = ParticleSystemQuad::create("effect/windy.plist");
	emitter->setPosition(size.width * 1.2, size.height / 1.5);
	leaf = ParticleSystemQuad::create("effect/leaf.plist");
	leaf = ParticleSystemQuad::create("effect/leaf.plist");
	flower1 = ParticleSystemQuad::create("effect/flower1.plist");
	flower2 = ParticleSystemQuad::create("effect/flower2.plist");
	flower3 = ParticleSystemQuad::create("effect/flower3.plist");
	grass1 = ParticleSystemQuad::create("effect/grass1.plist");
	leaf->setPosition(size.width * 1.5, size.height / 1.5);
	flower1->setPosition(size.width * 1.5, size.height / 2);
	flower2->setPosition(size.width * 1.5, size.height / 2);
	flower3->setPosition(size.width * 1.5, size.height / 2);
	grass1->setPosition(size.width * 1.5, size.height / 3);
	this->addChild(leaf);
	this->addChild(flower1);
	this->addChild(flower2);
	this->addChild(flower3);
	this->addChild(grass1);
	emitter->retain();
	this->addChild(emitter);
}

void Weather::rainEffect(){
	ParticleSystem* emitter;
	auto size = Director::getInstance()->getVisibleSize();
	emitter = ParticleSystemQuad::create("effect/rain.plist");
	emitter->setPosition(size.width / 2, size.height * 1.1);
	emitter->setLife(1.6);
	emitter->retain();
	this->addChild(emitter);
}

void Weather::cloudyEffect() {
	ParticleSystem* emitter;
	auto size = Director::getInstance()->getVisibleSize();
	emitter = ParticleSystemQuad::create("effect/cloud.plist");
	emitter->setPosition(size.width * 1.2, size.height / 1.5);
	emitter->retain();
	this->addChild(emitter);
}

void Weather::sunnyEffect() {
	ParticleSystem* emitter;
	auto size = Director::getInstance()->getVisibleSize();
	emitter = ParticleSystemQuad::create("effect/sun.plist");
	emitter->setPosition(0, size.height);
	emitter->setLife(0.1);
	emitter->setLifeVar(0.3);
	emitter->setSpeed(1);
	emitter->retain();
	this->addChild(emitter);
}