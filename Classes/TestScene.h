#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

#include "cocos2d.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;

USING_NS_CC;

#define MOUSE_DATA_PATH "data/mouse.json"

class TestScene : public Layer {
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene);
private:
	void loadUIAndSetListner();
	void submitData(Ref*, TouchEventType type);

private:
	TextField* IQ, *life, *distance, *weather;
};

#endif // !_TESTSCENE_H_
