//
//  PropManager.cpp
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#include "PropManager.h"
#include "Prop.h"
#include <stdlib.h>

bool PropManager::init() {
	if (!Sprite::init())
		return false;

	
	auto fertilizers = FertilizerContainer::create();
	auto block = BlockContainer::create();
	auto magent = MagentContainer::create();
	propContainers.pushBack(fertilizers);
	propContainers.pushBack(block);
	propContainers.pushBack(magent);
	this->addChild(fertilizers);
	this->addChild(block);
	this->addChild(magent);
	this->setPosition(0, 0);

	prop = nullptr;
	size = Director::getInstance()->getVisibleSize();

	schedule(schedule_selector(PropManager::updateProp), 1);

	return true;
}

void PropManager::updateProp(float dt) {
	if (prop && (prop->getPositionX() > (size.width + 10))) {
		prop->removeFromParentAndCleanup(true);
		prop = nullptr;
	}
}

void PropManager::addProp(Attribute attribute) {
	for (auto container : propContainers) {
		if (container->getTheAttribute() == attribute) {
			container->addAProp();
			break;
		}
	}
	update();
}

bool PropManager::deleteProp(Attribute attribute) {
	bool isDeleteSuccess = false;
	for (auto container : propContainers) {
		if (container->getTheAttribute() == attribute) {
			isDeleteSuccess = container->deleteAProp();
			break;
		}
	}
	update();
	return isDeleteSuccess;
}

void PropManager::update() {
	for (auto container : propContainers) {
		container->updateContainer();
	}
}

void PropManager::propContainerTouchEvent(Touch *touch, Event *event, CucrbitManage* cucrbitManage) {
	if (propContainers.empty())
		return;

		auto touchLocation = touch->getLocation();
		auto fertiPosition = propContainers.at(0)->getPosition();
		auto fertiSize = propContainers.at(0)->getContentSize();
		auto blockPosition = propContainers.at(1)->getPosition();
		auto blockSize = propContainers.at(1)->getContentSize();
		auto magentPosition = propContainers.at(2)->getPosition();
		auto magentSize = propContainers.at(2)->getContentSize();

		PropContainer* container = nullptr;

		if (touchLocation.x >= fertiPosition.x + 2 && touchLocation.x <= fertiPosition.x + fertiSize.width - 2) {
			if (touchLocation.y >= fertiPosition.y + 2 && touchLocation.y <= fertiPosition.y + fertiSize.height - 2) {
				container = propContainers.at(0);
			}
		}
		if (container == nullptr && touchLocation.x >= blockPosition.x + 2 && touchLocation.x <= blockPosition.x + blockSize.width - 2) {
			if (touchLocation.y >= blockPosition.y + 2 && touchLocation.y <= blockPosition.y + blockSize.height - 2) {
				container = propContainers.at(1);
			}
		}
		if (container == nullptr && touchLocation.x >= magentPosition.x + 2 && touchLocation.x <= magentPosition.x + magentSize.width - 2) {
			if (touchLocation.y >= magentPosition.y + 2 && touchLocation.y <= magentPosition.y + magentSize.height - 2) {
				container = propContainers.at(2);
			}
		}

		if (container != nullptr && container->getPropNum() > 0) {
			auto sacleTo1 = ScaleTo::create(0.2, 1.1);
			auto sacleTo2 = ScaleTo::create(0.2, 1);
			auto seq = Sequence::create(sacleTo1, sacleTo2, NULL);
			container->runAction(seq);
			
			// Mouse and cucrbit do action
			if (this->deleteProp(container->getTheAttribute())) {
				container->propEffectAction(cucrbitManage);
			}
		}
}

void PropManager::propTouchEvent(Touch *touch, Event *event) {
	if (prop && prop->getIsTouch() == false) {
		auto touchLocation = touch->getLocation();
		auto propLocation = prop->getPosition();
		auto propSize = prop->getContentSize();
		if (propLocation.x <= touchLocation.x && propLocation.x + propSize.width >= touchLocation.x) {
			if (propLocation.y <= touchLocation.y && propLocation.y + propSize.height >= touchLocation.y) {
				prop->setIsTouch(true);
				this->addProp(prop->getAttribute());
				for (auto container : propContainers) {
					if (container->getTheAttribute() == prop->getAttribute()) {
						prop->burst(container->getPosition(), container->getContentSize());
						break;
					}
				}
				prop = nullptr;
				this->update();
			}
		}
	}
}

void PropManager::propCreator(float dt) {
	auto propType = rand() % 10;
	if (propType < 3) {
		prop = Fertilizer::create();
	}
	else if (propType < 6) {
		prop = Block::create();
	}
	else {
		prop = Magent::create();
	}
	prop->run();
	this->addChild(prop);
}