#include "TestScene.h"
#include "WeatherInfo.h"
#include "JSON\writer.h"
#include "JSON\reader.h"
#include "JSON\value.h"
#include "LoadingScene.h"
#include <fstream>

Scene* TestScene::createScene() {
	auto scene = Scene::create();
	auto layer = TestScene::create();
	scene->addChild(layer);
	return scene;
}

bool TestScene::init() {
	loadUIAndSetListner();
	return true;
}

void TestScene::loadUIAndSetListner() {
	auto rootNode = CSLoader::createNode("Test/TestScene.csb");
	Node* main = rootNode->getChildByName("main");
	IQ = (TextField*)main->getChildByName("IQ");
	life = (TextField*)main->getChildByName("life");
	distance = (TextField*)main->getChildByName("distance");
	weather = (TextField*)main->getChildByName("weather");
	Button* submitBtn = (Button*)main->getChildByName("submit");
	submitBtn->addTouchEventListener(this, toucheventselector(TestScene::submitData));
	this->addChild(rootNode);
}

void TestScene::submitData(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		if (weather->getString() == "sunny") {
			WeatherInfo::getInstance()->setTodayWeather(sunny);
		}
		else if (weather->getString() == "windy") {
			WeatherInfo::getInstance()->setTodayWeather(windy);
		}
		else if (weather->getString() == "rain") {
			WeatherInfo::getInstance()->setTodayWeather(rain);
		}
		else if (weather->getString() == "cloudy") {
			WeatherInfo::getInstance()->setTodayWeather(cloudy);
		}
		else {
			WeatherInfo::getInstance()->setTodayWeather(defaultStyle);
		}
		Json::Value root;
		root["IQ"] = Value(IQ->getString()).asInt();
		printf("%s\n", IQ->getString().c_str());
		root["life"] = Value(life->getString()).asInt();
		root["distance"] = Value(distance->getString()).asInt();

		Json::FastWriter writer;
		std::string strWrite = writer.write(root);

		printf("%s\n", strWrite.c_str());
		FILE *fp = fopen(MOUSE_DATA_PATH, "w");
		if (fp != NULL) {
			fputs(strWrite.c_str(), fp);
			fclose(fp);
		}
		Director::getInstance()->replaceScene(LoadingScene::createScene());
	}
}
