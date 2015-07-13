//
//  GameOver.cpp
//  WittedMouse
//
//  Created by wc on 15/2/27.
//
//

#include "GameOver.h"
#include "MainScene.h"
#include "Mouse.h"
#include "Util.h"
#include "ActionController.h"
#include "LoadingScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "I18N.h"

bool GameOver::init() {
	if (!Layer::init())
		return false;

	popup = Popup::create();
	labelTitle = nullptr;
	labelTitle = Label::createWithTTF("fonts/heichu.ttf", "Dog-Tired");
	labelTitle->setTextColor(Color4B(Color3B(33, 44, 238)));
	labelTitle->setSystemFontSize(45);
	popup->addTitle(labelTitle);
	
	mainSceneMenu = MenuItemImage::create(
		"images/homeNormal.png",
		"images/homeSelected.png",
		this,
		menu_selector(GameOver::mainMenu));
	replayMenu = MenuItemImage::create(
		"images/restartNormal.png",
		"images/restartSelected.png",
		this,
		menu_selector(GameOver::replay));

	auto label = Label::createWithTTF("fonts/heichu.ttf",
		String::createWithFormat("IQ: %d", Mouse::getIQ())->getCString());
	label->setTextColor(Color4B::BLACK);
	label->setSystemFontSize(35);
	auto label2 = Label::createWithTTF("fonts/heichu.ttf",
		String::createWithFormat("Life: %d", Mouse::getLife())->getCString());
	label2->setTextColor(Color4B::BLACK);
	label2->setSystemFontSize(35);
	IQLabel = MenuItemLabel::create(label);
	LifeLabel = MenuItemLabel::create(label2);

	popup->addMenuInScreenFringe(0, mainSceneMenu, replayMenu, NULL);
	popup->addLabel(0, IQLabel, LifeLabel, NULL);


	this->addChild(popup);
	this->setVisible(false);

	return true;
}

void GameOver::gameOver(bool finish) {
	if (finish) {
		labelTitle->setString("Arrives");
	}
	else {
		labelTitle->setString("Dog-Tired");
	}
	auto pause = Director::getInstance()->getRunningScene()->getChildByTag(PAUSETAG);
	pause->setVisible(false);
	this->setVisible(true);
	update();
	ActionController::control(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/finishGame.wav");
	popup->display();
}

void GameOver::replay(Ref* sender) {
	LoadingScene::loadData();
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void GameOver::mainMenu(Ref* sender) {
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameOver::update() {
	IQLabel->setString(String::createWithFormat("IQ: %d", Mouse::getIQ())->getCString());
	LifeLabel->setString(String::createWithFormat("Life: %d", Mouse::getLife())->getCString());
}