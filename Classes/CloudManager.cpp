#include "CloudManager.h"

bool CloudManager::init() {
	if (!Sprite::init())
		return false;

	clouds.clear();
	this->setPosition(0, 0);

	return true;
}

void CloudManager::createCloud() {
	auto num = rand() % 3;
	for (int i = 0; i != num; ++i) {
		auto cloud = Cloud::create();
		clouds.pushBack(cloud);
		cloud->cloudAction();
		this->addChild(cloud);
	}
	removeOutCloud();
}

void CloudManager::removeOutCloud() {
	Vector<Cloud*> tempVector;
	for (auto cloud : clouds) {
		if (cloud->getPosition().x < (-cloud->getContentSize().width)) {
			tempVector.pushBack(cloud);
		}
	}

	for (auto cloud : tempVector) {
		clouds.eraseObject(cloud);
	}
}