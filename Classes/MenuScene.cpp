#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "AnimationUtils.h"
#include "I18N.h"
#include "SimpleAudioEngine.h"
#include "CloudManager.h"
#include "WeatherInfo.h"

Scene* MenuScene::createScene() {
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init() {
	if (!Layer::init()) {
		return false;
	}

	_isBtnListShow = false;
	_isDialogShow = false;
	WeatherStyle weather = WeatherInfo::getInstance()->getTodayWeather();
	printf("%d\n", weather);
	if (weather == sunny || weather == windy || weather == defaultStyle) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgmusic2.mp3", true);
	}
	else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgmusic1.mp3", true);
	}
	loadUIAndSetListner();
	
	mouseBegin = Sprite::createWithSpriteFrameName("scooter29.png");

	mouseRun = Mouse::createMouse();

	mouseBegin->setScale(0.3);
	mouseBegin->setPosition(Point(-200, 180));
	mouseRun->setPosition(Point(650, 160));
	mouseRun->setVisible(false);

	this->addChild(mouseBegin, 1);
	this->addChild(mouseRun, 1);

	return true;
}

void MenuScene::loadUIAndSetListner() {
	auto rootNode = CSLoader::createNode("Menu/MenuScene.csb");
	this->addChild(rootNode);

	singleMode = (Button*)(rootNode->getChildByName("beginBtn"));
	singleMode->setTitleText(I18N::getInstance()->getString("singleMode"));
	singleMode->addTouchEventListener(this, toucheventselector(MenuScene::singleModeEvent));

	battle = (Button*)(rootNode->getChildByName("battleBtn"));
	battle->setTitleText(I18N::getInstance()->getString("battle"));
	
	_itemList = rootNode->getChildByName("btnList");
	_dialog = rootNode->getChildByName("dialog");
	((Text*)(_dialog->getChildByName("title")->getChildByName("titleText")))->setFontName("fonts/heichu.ttf");

	int developerNum = Value(I18N::getInstance()->getString("developerNum")).asInt();
	Node* developerMain = _dialog->getChildByName("body")->getChildByName("developerMain");
	for (int i = 0; i < developerNum; ++i) {
		Label* developer = Label::createWithTTF(
			I18N::getInstance()->getString(StringUtils::format("developer%d", i)),
			"fonts/heichu.ttf",
			40
			);
		developer->setTextColor(Color4B(Color3B(0, 0, 0)));
		developer->setPosition(Point(developerMain->getContentSize().width / 2, developerMain->getContentSize().height / developerNum * (developerNum - i)));
		developerMain->addChild(developer);
	}

	Node* settingMain = _dialog->getChildByName("body")->getChildByName("settingMain");
	std::vector<std::string> settingTitles;
	settingTitles.push_back("musicTitle");
	settingTitles.push_back("effectTitle");
	settingTitles.push_back("languageTitle");

	Text* title = NULL;
	for (auto titleStr : settingTitles) {
		title = (Text*)settingMain->getChildByName(titleStr);
		title->setFontName("fonts/heichu.ttf");
		title->setText(I18N::getInstance()->getString(titleStr));
	}

	Node* infoMain = _dialog->getChildByName("body")->getChildByName("infoMain");
	Text* IQ = (Text*)(infoMain->getChildByName("IQ"));
	IQ->setText(Value(Mouse::getIQ()).asString());

	Node* helpMain = _dialog->getChildByName("body")->getChildByName("helpMain");
	((PageView*)helpMain)->setClippingEnabled(true);

	showOrHideBtn = (Button*)(_itemList->getChildByName("showBtn"));
	showOrHideBtn->addTouchEventListener(this, toucheventselector(MenuScene::showOrHideEvent));

	auto helpBtn = (Button*)(_itemList->getChildByName("helpBtn"));
	helpBtn->addTouchEventListener(this, toucheventselector(MenuScene::showHelp));

	auto infoBtn = (Button*)(_itemList->getChildByName("infoBtn"));
	infoBtn->addTouchEventListener(this, toucheventselector(MenuScene::showInfo));

	auto settingBtn = (Button*)(_itemList->getChildByName("settingBtn"));
	settingBtn->addTouchEventListener(this, toucheventselector(MenuScene::showSetting));

	auto developerBtn = (Button*)(_itemList->getChildByName("developerBtn"));
	developerBtn->addTouchEventListener(this, toucheventselector(MenuScene::showDeveloper));

	closeDialogBtn = (Button*)(_dialog->getChildByName("closeDialog"));
	closeDialogBtn->addTouchEventListener(this, toucheventselector(MenuScene::closeDialog));

	auto helpPrevBtn = (Button*)(_dialog->getChildByName("body")->getChildByName("helpPrevBtn"));
	helpPrevBtn->addTouchEventListener(this, toucheventselector(MenuScene::prevHelpStep));
	auto helpNextBtn = (Button*)(_dialog->getChildByName("body")->getChildByName("helpNextBtn"));
	helpNextBtn->addTouchEventListener(this, toucheventselector(MenuScene::nextHelpStep));
	
}

void MenuScene::singleModeEvent(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		if (_isBtnListShow) {
			showOrHideEvent((Ref*)showOrHideBtn, TouchEventType::TOUCH_EVENT_ENDED);
		}
		if (_isDialogShow) {
			closeDialog((Ref*)closeDialogBtn, TouchEventType::TOUCH_EVENT_ENDED);
		}
		_itemList->setVisible(false);
		singleMode->setEnabled(false);
		singleMode->setTitleText("");
		battle->setEnabled(false);
		battle->setTitleText("");
		mouseBegin->runAction(Animate::create(AnimationUtils::createWithNameAndStartIndex("scooter", 29, 0.1f, 1)));
		MoveTo* moveTo = MoveTo::create(2.4f, Point(400, 180));
		Sprite* _mouseBegin = mouseBegin;
		Mouse* _mouseRun = mouseRun;
		CallFunc* changeMouse = CallFunc::create([_mouseBegin, _mouseRun]() {
			Size winSize = Director::getInstance()->getWinSize();
			_mouseBegin->setVisible(false);
			_mouseRun->setVisible(true);
			_mouseRun->runAction(Animate::create(AnimationUtils::createWithName("run", 0.05f, -1)));
			MoveTo* moveTo2 = MoveTo::create(1.7f, Point(winSize.width, 160));
			CallFunc* changeScene = CallFunc::create([]() {
				Director::getInstance()->replaceScene(MainScene::createScene());
			});
			_mouseRun->runAction(Sequence::create(moveTo2, changeScene, NULL));
		});
		mouseBegin->runAction(Sequence::create(moveTo, changeMouse, NULL));
	}
}

void MenuScene::showOrHideEvent(Ref* sender, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		auto showOrHideBtn = (Button*)sender;
		Point curPoint = _itemList->getPosition();
		_isBtnListShow = !_isBtnListShow;
		MoveBy* moveBy = MoveBy::create(0.35f, Point(0, 290 * (_isBtnListShow ? 1 : -1)));
		showOrHideBtn->setFlippedY(_isBtnListShow);
		_itemList->runAction(moveBy);
	}
}


void MenuScene::showHelp(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("helpTitle"), true);
		Node* helpMain = _dialog->getChildByName("body")->getChildByName("helpMain");
		helpMain->setVisible(true);
		_dialog->getChildByName("body")->getChildByName("helpPrevBtn")->setVisible(true);
		_dialog->getChildByName("body")->getChildByName("helpNextBtn")->setVisible(true);
	}
}

void MenuScene::showInfo(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("infoTitle"), true);
		Node* infoMain = _dialog->getChildByName("body")->getChildByName("infoMain");
		infoMain->setVisible(true);
	}
}

void MenuScene::showSetting(Ref* sender, TouchEventType type) {
	auto settingBtn = (Button*)sender;
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("settingTitle"), true);
		Node* settingMain = _dialog->getChildByName("body")->getChildByName("settingMain");
		settingMain->setVisible(true);
	}
}

void MenuScene::showDeveloper(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		toggleDialogAndSetTitle(I18N::getInstance()->getString("developerTitle"), true);
		Node* developerMain = _dialog->getChildByName("body")->getChildByName("developerMain");
		developerMain->setVisible(true);
	}
}

void MenuScene::closeDialog(Ref* sender, TouchEventType type) {
	auto closeBtn = (Button*)sender;
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		closeBtn->setScale(1);
		toggleDialogAndSetTitle("", false);
	}
	else if (type == TouchEventType::TOUCH_EVENT_BEGAN) {
		closeBtn->setScale(0.9);
	}
	else {
		closeBtn->setScale(1.0 / 0.9);
	}
}

void MenuScene::toggleDialogAndSetTitle(const char* title, bool _isShow) {
	// _isDialogShow表示dialog的状态,_isShow表示是否想要弹出
	if (_isShow ^ _isDialogShow) {
		_isDialogShow = !_isDialogShow;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		_dialog->runAction(MoveBy::create(0.4f, Point(0, (_isShow ? -1 : 1) * visibleSize.height)));
	}
	Text* titleText = (Text*)_dialog->getChildByName("title")->getChildByName("titleText");
	titleText->setText(string(title));
	Node* body = _dialog->getChildByName("body");
	for (auto child : body->getChildren()) {
		child->setVisible(false);
	}
}

void MenuScene::prevHelpStep(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		PageView* helpMain = (PageView*)_dialog->getChildByName("body")->getChildByName("helpMain");
		if (helpMain->getCurPageIndex() > 0) {
			helpMain->scrollToPage(helpMain->getCurPageIndex() - 1);
		}
	}
}

void MenuScene::nextHelpStep(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		PageView* helpMain = (PageView*)_dialog->getChildByName("body")->getChildByName("helpMain");
		if (helpMain->getCurPageIndex() < 2) {
			helpMain->scrollToPage(helpMain->getCurPageIndex() + 1);
		}
	}
}


