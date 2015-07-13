//
//  MainScene.cpp
//  WittedMouse
//
//  Created by wc on 15/2/14.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Pause.h"
#include "Util.h"
#include "GameOver.h"
#include "CloudManager.h"
#include "WeatherManager.h"
#include "LoadingScene.h"
#include "MouseUtil.h"
#include "MouseController.h"

HUDLayer* MainScene::hudLayer = nullptr;

bool MainScene::init() {
	if (!Layer::init())
		return false;

	size = Director::getInstance()->getVisibleSize();

	createBackground();
	createCloud();
	createMouse();
	createProp();
	createCucrbit();
	createWeather();
	eventProcess();
	initCucurbit();
	createProgress();
	createProgressBlood();

	LoadingScene::loadData();

	if (hudLayer != nullptr)
		hudLayer->updateIQ();

	scheduleProcess();

	isHold = false;
	isFall = false;
	isAction = false;
	isJump = false;
	isSkateboardHit = false;
	isSkateboardFinishAction = false;
	isSkateboard = false;
	isSholvePropChose = false;
	mouseFallingSnare = nullptr;
	skateboard = nullptr;
	snares.clear();

	return true;
}

Scene* MainScene::createScene() {
	auto scene = Scene::create();
	auto pause = Pause::create();
	auto gameOver = GameOver::create();
	hudLayer = HUDLayer::create();
	auto mainGame = MainScene::create();
	scene->setTag(GAMELAYERTAG);
	if (!scene)
		return nullptr;

	mainGame->setTag(GAMETAG);
	gameOver->setTag(GAMEOVERTAG);
	scene->addChild(mainGame);
	scene->addChild(hudLayer);
	scene->addChild(pause);
	scene->addChild(gameOver);

	return scene;
}

void MainScene::createBackground() {
	///< Set the background
	bg1 = Sprite::createWithSpriteFrameName("background.png");
	bg2 = Sprite::createWithSpriteFrameName("background.png");

	///< Set the scaling
	auto sx = size.width / bg1->getContentSize().width;
	auto sy = size.height / bg1->getContentSize().height;
	bg1->setScale(sx, sy);
	bg1->setAnchorPoint(Vec2(0, 0));
	///< Set the position
	bg1->setPosition(Vec2(0, 0));

	sx = size.width / bg2->getContentSize().width;
	sy = size.height / bg2->getContentSize().height;
	bg2->setScale(sx, sy);
	bg2->setAnchorPoint(Vec2(0, 0));
	bg2->setPosition(Vec2(size.width - 2, 0));
	this->addChild(bg1);
	this->addChild(bg2);
}

void MainScene::moveBackgroundAndCucrbit(float dt) {
	// Move background
	float dif;
	if (Util::getInstance()->getDif() == -1)
		dif = 6;
	else
		dif = Util::getInstance()->getDif();

	if (dif == 0)
		return;

	moveAllBg(dif);
}

void MainScene::moveAllBg(float dif) {
	Progress::setDistance(Progress::getDistance() + dif);
	updateProgressAndBlood();
	bg1->setPosition(Vec2(bg1->getPositionX() - dif, bg1->getPositionY()));
	bg2->setPosition(Vec2(bg2->getPositionX() - dif, bg2->getPositionY()));

	if (bg2->getPositionX() < 0) {
		float temp = bg2->getPositionX() + size.width;
		bg1->setPosition(Vec2(temp - 2, bg1->getPositionY()));
	}

	if (bg1->getPositionX() < 0) {
		float temp = bg1->getPositionX() + size.width;
		bg2->setPosition(Vec2(temp - 2, bg2->getPositionY()));
	}
	moveSnare(dif);
	moveSkateboard(dif);
	cucrbitManage->moveCucrbit(dif);
	removeSnare();
	removeSkateboard(false);

	if (!isAction) {
		fallInSnare();
		skateboardCrash();
		if (!isJump && !isFall) {
			rectCrash();
		}
	}
}

void MainScene::skateboardCrash() {
	if (skateboard == nullptr)
		return;
	if (mouse->getBoundingBox().intersectsRect(skateboard->getBoundingBox())) {
		if (!isSkateboardHit) {
			skateboard->actionAfterHit();
			isSkateboardHit = true;
		}
		else if (isSkateboardFinishAction) {
			isSkateboardFinishAction = false;
			removeSkateboard(true);
			runWithScooter();
		}
	}
}

bool MainScene::isFridgeCrash(Node* first, Node* second) {
	// if is mouse, mouse must be the first argument
	auto firstPosition = first->getPosition();
	auto secondPosition = second->getPosition();
	auto firstSize = first->getContentSize();
	auto secondSize = second->getContentSize();
	auto firstAncrpoint = first->getAnchorPoint();
	auto secondAncrpoint = second->getAnchorPoint();

	float distancesx = secondPosition.x - firstPosition.x - firstSize.width * (1.0 - firstAncrpoint.x) - secondSize.width * secondAncrpoint.x;
	float distancesy = secondPosition.y - firstPosition.y - firstSize.height * (1.0 - firstAncrpoint.y) - secondSize.height * secondAncrpoint.y;

	if (((distancesx > -7 && distancesx <= 0 || distancesy > -7 && distancesy <= 0)) && (first->getBoundingBox().intersectsRect(second->getBoundingBox()))) {
		return true;
	}
	return false;
}

void MainScene::setIsSkateboardFinishAction() {
	isSkateboardFinishAction = true;
	isSkateboardHit = true;
}

void MainScene::rectCrash() {
	ItemType itemtype = NULLTYPE;
	Vec2 distance, speed;
	speed.x = Util::getInstance()->getDif();

	float range = -1;

	for (auto snare : snares) {
		if (neareSnare(snare)) {
			itemtype = HOLE;
			distance.x = snare->getPosition().x - mouse->getPosition().x;
			distance.y = snare->getPosition().y - mouse->getPosition().y;
			speed.y = 0;
			break;
		}
	}

	if (itemtype == NULLTYPE) {
		if (skateboard != nullptr) {
			if (isFridgeCrash(mouseRect, skateboard)) {
				itemtype = SCOOTER;
				distance.x = skateboard->getPosition().x - skateboard->getContentSize().width / 2;
				distance.y = skateboard->getPosition().y - skateboard->getContentSize().height / 2 - mouse->getContentSize().height / 2;
				speed.y = 0;
				isSkateboard = true;
			}
		}
	}

	if (itemtype == NULLTYPE) {
		auto fallDownCucrbit = cucrbitManage->getFallDownCucrbit();
		Cucurbit* creshCucrbit = nullptr;
		for (auto cucrbit : fallDownCucrbit) {
			if (isFridgeCrash(mouseRect, cucrbit)) {
				creshCucrbit = cucrbit;
			}
		}
		if (creshCucrbit != nullptr) {
			if (creshCucrbit->getType() < 2) {
				itemtype = DENGEROUS_CUCRBIT;
			}
			else {
				itemtype = BENEFICATE_CUCRBIT;
			}
			distance.x = creshCucrbit->getPosition().x - creshCucrbit->getContentSize().width - mouse->getPosition().x - mouse->getContentSize().width * 0.5;
			distance.y = creshCucrbit->getPosition().y - creshCucrbit->getContentSize().height - mouse->getPosition().y - mouse->getContentSize().height * 0.5;
			speed.y = (Cucurbit::initialHeight() - (size.height / 10) - creshCucrbit->getContentSize().height) / 1;
			range = (mouse->getContentSize().width + creshCucrbit->getContentSize().width) / speed.x;
		}
	}

	if (itemtype != NULLTYPE) {
		rectCrashAction(itemtype, distance, speed, range);
	}
}

void MainScene::resetIsAction() {
	isAction = false;
}

void MainScene::resetIsJump() {
	isJump = false;
}

void MainScene::resetIsSkateboardHit() {
	isSkateboardHit = false;
}

void MainScene::rectCrashAction(ItemType itemType, Vec2 distance, Vec2 speed, float range) {
	if (isFall)
		return;
	auto mouseAction = MouseController::getInstance()->getMouseAction(Mouse::getIQ(), itemType, distance, speed, range);
	if (mouseAction == JUMP && !(isSkateboard && isSkateboardHit)) {
		isSkateboard = false;
		isJump = true;
		mouse->jump();
	}
	else if (mouseAction == SPEEDUP) {
		mouse->speedUp();
	}
	else if (mouseAction == SLOWDOWN) {
		mouse->slowDown();
	}
}

bool MainScene::neareSnare(Snare* snare) {
	return isFridgeCrash(mouse, snare);
}

void MainScene::snareCreateProcess(Touch *touch, Event *event) {
	if (isSholvePropChose && touch->getLocation().y < size.height / 6) {
		isSholvePropChose = false;
		auto snare = Snare::createSnare(Vec2(touch->getLocation().x, size.height / 5.4));
		snares.pushBack(snare);
		this->addChild(snare);
	}
}

void MainScene::removeSnare() {
	if (snares.size() > 0) {
		auto tempVector = Vector<Snare*>();
		for (auto snare : snares) {
			auto snarePosition = snare->getPosition();
			if ((snare->getPosition().x + snare->getContentSize().width) < 0) {
				tempVector.pushBack(snare);
				snare->removeFromParentAndCleanup(true);
			}
		}

		for (auto snare : tempVector) {
			snares.eraseObject(snare);
		}
	}
}

void MainScene::removeSkateboard(bool flag) {
	if (flag || (skateboard != nullptr && (skateboard->getPosition().x - skateboard->getContentSize().width / 2 < -10))) {
		skateboard->removeFromParentAndCleanup(true);
		resetIsSkateboardHit();
		skateboard = nullptr;
	}
}

void MainScene::eventProcess() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *touch, Event *event) {
		propContainerTouchEvent(touch, event);
		snareCreateProcess(touch, event);
		return true;
	};

	listener->onTouchMoved = [=](Touch *touch, Event *event) {
		cucrbitTouchEvent(touch, event);
		propTouchEvent(touch, event);
	};

	listener->onTouchEnded = [=](Touch *touch, Event *event) {
		isHold = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainScene::cucurbitProcess(float dt) {
	cucrbitManage->cucurbitProcess(dt);
}

void MainScene::initCucurbit() {
	cucrbitManage->initCucurbit();
}

void MainScene::addCucurbit(float dt) {
	cucrbitManage->addCucurbit(dt);
}

void MainScene::cucrbitFallDown(Cucurbit *cucrbit) {
	cucrbitManage->cucrbitFallDown(cucrbit);
}

void MainScene::removeFallDownCucrbit(float dt) {
	cucrbitManage->removeFallDownCucrbit(mouse, hudLayer);
}

void MainScene::addSkateboard(float dt) {
	if (skateboard == nullptr) {
		skateboard = Skateboard::create();
		this->addChild(skateboard);
	}
}

void MainScene::propCreator(float dt) {
	propManager->propCreator(dt);
}

void MainScene::cucrbitTouchEvent(Touch *touch, Event *event) {
	if (isHold == false) {
		// Only the first cucrbit that been incised need to fall down
		isHold = cucrbitManage->cucrbitTouchEvent(touch, event);
	}
}

void MainScene::propTouchEvent(Touch *touch, Event *event) {
	propManager->propTouchEvent(touch, event);
}

void MainScene::propContainerTouchEvent(Touch *touch, Event *event) {
	propManager->propContainerTouchEvent(touch, event, cucrbitManage);
}

void MainScene::cloudCreater(float dt) {
	cloudManager->createCloud();
}

void MainScene::createCloud() {
	///< add cloud Manager
	cloudManager = CloudManager::create();
	cloudManager->createCloud();
	this->addChild(cloudManager);
}

void MainScene::createProp() {
	///< Add prop manager
	propManager = PropManager::create();
	this->addChild(propManager);
}

void MainScene::createMouse() {
	///< Add mouse to the main scene
	mouse = Mouse::createMouse();
	mouse->run();
	this->addChild(mouse);

	mouseRect = MouseRect::create();
	this->addChild(mouseRect);
}

void MainScene::createCucrbit() {
	///< Add cucrbit manager
	cucrbitManage = CucrbitManage::create();
	this->addChild(cucrbitManage);
}

void MainScene::createWeather() {
	this->addChild(WeatherManager::create());
}

void MainScene::createProgressBlood() {
	progressBlood = ProgressBlood::create();
	this->addChild(progressBlood);
}

void MainScene::createProgress() {
	progress = Progress::create();
	this->addChild(progress);
}

void MainScene::moveSnare(float dif) {
	for (auto snare : snares) {
		snare->setPosition(Vec2(snare->getPositionX() - dif, snare->getPositionY()));
	}
}

void MainScene::moveSkateboard(float dif) {
	if (skateboard != nullptr)
		skateboard->setPosition(Vec2(skateboard->getPositionX() - dif, skateboard->getPositionY()));
}

void MainScene::scheduleProcess() {
	schedule(schedule_selector(MainScene::moveBackgroundAndCucrbit));
	schedule(schedule_selector(MainScene::cucurbitProcess), 2);
	schedule(schedule_selector(MainScene::addCucurbit), 0.5);
	schedule(schedule_selector(MainScene::removeFallDownCucrbit));
	schedule(schedule_selector(MainScene::propCreator), 10);
	schedule(schedule_selector(MainScene::cloudCreater), 4);
	schedule(schedule_selector(MainScene::addSkateboard), 20);
}

void MainScene::fallInSnare() {
	for (auto snare : snares) {
		if (isMouseOnSnare(snare) && !isFall && !isJump) {
			mouse->fall(snare);
			isFall = true;
		}
	}
}

bool MainScene::isMouseOnSnare(Snare* snare) {
	auto snarePositionX = snare->getPosition().x;
	auto mousePositionX = mouse->getPosition().x;

	if ((snarePositionX + snare->getContentSize().width / 4) < mousePositionX &&
		((snarePositionX + snare->getContentSize().width / 2) > mousePositionX)) {
		mouseFallingSnare = snare;
		return true;
	}
	return false;
}

void MainScene::moveMouseBehineSnare(){
	if (isFall && mouseFallingSnare != nullptr) {
		moveAllBg(mouseFallingSnare->getContentSize().width / 4);
		mouseFallingSnare = nullptr;
	}
	isFall = false;
}

void MainScene::updateProgressAndBlood() {
	progress->update();
	progressBlood->update();
}

void MainScene::runWithScooter() {
	isAction = true;
	mouse->scooter();
}

void MainScene::setIsSholvePropChose(bool isSholvePropChose) {
	this->isSholvePropChose = isSholvePropChose;
}

bool MainScene::getIsAction() {
	return isAction;
}