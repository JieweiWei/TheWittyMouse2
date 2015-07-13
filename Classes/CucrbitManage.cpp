//
//  CucrbitManage.cpp
//  WittedMouse
//
//  Created by wc on 15/2/26.
//
//

#include "CucrbitManage.h"
#include "GameOver.h"
#include "Util.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"


bool CucrbitManage::init() {
    if (!Sprite::init())
        return false;
    
    cucurbitsToFallDown.clear();

    size = Director::getInstance()->getVisibleSize();
    this->setPosition(0, 0);
    return true;
}

void CucrbitManage::moveCucrbit(float dif) {
    // Move the cucrbits
    if (cucurbits.size() > 0) {
        Vector<Cucurbit*> tempVector;
        for (int i = 0; i != cucurbits.size(); ++i) {
            auto cucrbit = cucurbits.at(i);
            cucrbit->setPositionX(cucrbit->getPositionX() - dif);
            if (cucrbit->getPositionX() <  -10) {
                cucrbit->removeFromParentAndCleanup(true);
                tempVector.pushBack(cucrbit);
            }
        }
        
        for (auto cucrbit : tempVector) {
            if (!cucrbit->getIsCut())
                cucurbits.eraseObject(cucrbit);
        }
    }
}

void CucrbitManage::cucurbitProcess(float dt) {
    for (auto cucrbit : cucurbits) {
        if (!cucrbit->getIsCut()) {
            if (cucrbit->grow()) {
                cucurbitsToFallDown.pushBack(cucrbit);
                cucrbit->setIsCut(true);
                cucrbitFallDown(cucrbit);
            }
        }
    }
}

void CucrbitManage::initCucurbit() {
    for (int i = 0; i != 4; ++i) {
        auto cucrbit = Cucurbit::createCucurbit();
        this->addChild(cucrbit);
        cucurbits.pushBack(cucrbit);
    }
}

void CucrbitManage::addCucurbit(float dt) {
	int cucrbitNum = 10;
	int i = 0;
	while (cucurbits.size() < cucrbitNum && i++ < 100) {
			bool flag = true;
			auto cucrbit = Cucurbit::createCucurbit();
			cucrbit->setPositionX(cucrbit->getPositionX() + (size.width));
			for (auto cucrbitInList : cucurbits) {
				if ((cucrbitInList->getPosition().x > cucrbit->getPosition().x &&
					cucrbitInList->getPosition().x < (cucrbit->getPosition().x + cucrbit->getContentSize().width))
					) {
					flag = false;
					break;
				}
			}
			if (flag) {
				this->addChild(cucrbit);
				cucurbits.pushBack(cucrbit);
				break;
			}
    }
}

void CucrbitManage::cucrbitFallDown(Cucurbit *cucrbit) {
    if (cucrbit) {
		cucurbitsToFallDown.pushBack(cucrbit);
        auto moveTo = MoveTo::create(1, Vec2(cucrbit->getPositionX(), size.height / 8));
        cucrbit->runAction(moveTo);
    }
}

void CucrbitManage::removeFallDownCucrbit(Mouse* mouse, HUDLayer *hudLayer) {
    if (cucurbitsToFallDown.size() != 0) {
        Vector<Cucurbit*> tempVector;
		auto mainScene = (MainScene*)Director::getInstance()->getRunningScene()->getChildByTag(GAMETAG);
        for (auto cucrbitTemp : cucurbitsToFallDown) {
			if (cucrbitTemp->getBoundingBox().intersectsRect(mouse->getBoundingBox()) && !mainScene->getIsAction()) {
                // update iq
				int cucrbitType = cucrbitTemp->getType();
				if (cucrbitType < 2) {
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/hit.wav");
					if (cucrbitType == 0) {
						Mouse::setIQ(Mouse::getIQ() + 1);
						Mouse::setLife(Mouse::getLife() - 1);
					}
					else {
						Mouse::setIQ(Mouse::getIQ() + 2);
						Mouse::setLife(Mouse::getLife() - 2);
					}
					mouse->dizzy();
                } else {
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/eatHulu.wav");
                    if ( Mouse::getLife() < 10)
                        Mouse::setLife(Mouse::getLife() + 1);
                }
                // HUD layer
                hudLayer->updateIQ();
                
                cucurbits.eraseObject(cucrbitTemp);
                CallFunc* removeFunc = CallFunc::create([cucrbitTemp]() {
                    cucrbitTemp->removeFromParentAndCleanup(true);
                });
                if (cucrbitTemp->getType() == 2) {
                    ScaleTo* scaleTo = ScaleTo::create(0.2f, 0.0);
                    MoveTo* moveTo = MoveTo::create(0.5, Vec2(size.width / 5, size.height / 4));
                    FadeOut* fadeOut = FadeOut::create(0.5);
                    cucrbitTemp->runAction(Sequence::create(Spawn::create(scaleTo, moveTo, fadeOut, NULL), removeFunc, NULL));
                }
                else {
                    JumpBy* jumpBy = JumpBy::create(0.5f, Point(-100, 50), 200, 1);
                    ScaleTo* scaleTo = ScaleTo::create(0.5, 0.0);
                    cucrbitTemp->runAction(Sequence::create(Spawn::create(jumpBy, scaleTo, NULL), removeFunc, NULL));
                }
                tempVector.pushBack(cucrbitTemp);
                
            } else if ((cucrbitTemp->getPositionY() -
                        cucrbitTemp->getContentSize().height) <= size.height / 7) {
                cucrbitTemp->removeFromParentAndCleanup(true);
                cucurbits.eraseObject(cucrbitTemp);
                tempVector.pushBack(cucrbitTemp);
            }
        }
        
        for (auto cucrbitTemp : tempVector) {
            cucurbitsToFallDown.eraseObject(cucrbitTemp);
        }
    }
}

bool CucrbitManage::cucrbitTouchEvent(Touch *touch, Event *event) {
    // Only the first cucrbit that been incised need to fall down
    Vec2 touchLocation = touch->getLocation();
    for (auto cucrbit : cucurbits) {
        Vec2 cucrbitLocation = cucrbit->getPosition();
        Size sizeOfCucrbit = cucrbit->getContentSize();
        if (touchLocation.x >= cucrbitLocation.x && touchLocation.x <= (cucrbitLocation.x + sizeOfCucrbit.width)) {
            if (touchLocation.y <= cucrbitLocation.y && touchLocation.y >=
                (cucrbitLocation.y - sizeOfCucrbit.height)) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/carve.wav");
                cucrbit->setIsCut(true);
                cucrbitFallDown(cucrbit);
                return true;
            }
        }
    }
    return false;
}

void CucrbitManage::allCucrbitGrowUp() {
	for (auto cucrbit : cucurbits) {
		cucrbit->growUp();
	}
}

void CucrbitManage::allCucrbitFallDown() {
	for (auto cucrbit : cucurbits) {
		cucrbitFallDown(cucrbit);
	}
}


Vector<Cucurbit*> CucrbitManage::getFallDownCucrbit() {
	return cucurbitsToFallDown;
}