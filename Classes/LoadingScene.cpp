#include "LoadingScene.h"
#include "I18N.h"
#include "AnimationUtils.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "Mouse.h"
#include "JSON\writer.h"
#include "JSON\reader.h"
#include "JSON\value.h"
#include "Util.h"

Scene* LoadingScene::createScene() {
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init() {
	if (!Layer::init()) {
		return false;
	}
	Util::getInstance()->init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* loadingTile = Label::createWithTTF(I18N::getInstance()->getString("loadingTitle"), "fonts/huaifang.ttf", 100);
	loadingTile->setColor(Color3B(255, 255, 255));
	loadingTile->setPosition(
		Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - loadingTile->getContentSize().height)
	);
	this->addChild(loadingTile, 1);

	loadRes();
	loadData();

	auto mouse = Mouse::createMouse();
	mouse->setPosition(Point(-100, 150));
	this->addChild(mouse, 1);
	mouse->runAction(Animate::create(AnimationUtils::createWithName("run", 0.1f, -1)));

	MoveTo* moveTo = MoveTo::create(4.0f, Point(winSize.width + 100, 150));
	CallFunc* callFunc = CallFunc::create([]() {
		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	mouse->runAction(Sequence::create(moveTo, callFunc, NULL));
	return true;
}

void LoadingScene::loadRes() {
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("images/mouse.plist", "images/mouse.png");
	frameCache->addSpriteFramesWithFile("images/MainGame.plist", "images/MainGame.png");
	frameCache->addSpriteFramesWithFile("images/btn.plist", "images/btn.png");
	for (int i = 1; i <= 13; ++i) {
		frameCache->addSpriteFramesWithFile(StringUtils::format("images/scooter%d.plist", i), StringUtils::format("images/scooter%d.png", i));
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bgmusic1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bgmusic2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/hit.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/thunderclap.mp3"); 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/carve.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/finishGame.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/eatHulu.wav");
}

void LoadingScene::loadData() {
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile("data/mouse.json");
	if (reader.parse(data, root, false)) {
		Mouse::setIQ(root["IQ"].asInt());
		Mouse::setLife(root["life"].asInt());
		Util::getInstance()->setDistanceTravelled(root["distance"].asInt());
		Util::getInstance()->setInitMouseLife(root["life"].asInt());
	}
	else {
		Mouse::setIQ(INIT_IQ);
		Mouse::setLife(INIT_LIFE);
		Util::getInstance()->setDistanceTravelled(INIT_DISTANCE);
		Util::getInstance()->setInitMouseLife(INIT_LIFE);
	}
}