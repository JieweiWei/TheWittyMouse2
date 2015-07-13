#ifndef _MENUSCEME_H_
#define _MENUSCEME_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Mouse.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define IQ_DATA_PATH "data/mouse.json"

class MenuScene : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

private:
	/* 加载CocosStudio中UI并添加点击事件 */
	void loadUIAndSetListner();

	/* 按钮的触发事件 */
	void singleModeEvent(Ref*, TouchEventType type);
	void showOrHideEvent(Ref* sender, TouchEventType type);

	void showHelp(Ref*, TouchEventType type);
	void showInfo(Ref*, TouchEventType type);
	void showSetting(Ref*, TouchEventType type);
	void showDeveloper(Ref*, TouchEventType type);
	
	void closeDialog(Ref*, TouchEventType type);
	void toggleDialogAndSetTitle(const char* title, bool _isShow);

	void prevHelpStep(Ref*, TouchEventType type);
	void nextHelpStep(Ref*, TouchEventType type);

private:
	bool _isBtnListShow;
	bool _isDialogShow;
	Node* _itemList;
	Node* _dialog;
	Sprite* mouseBegin;
	Mouse* mouseRun;
	Button *showOrHideBtn, *closeDialogBtn, *singleMode, *battle;
};


#endif // !_MENUSCEME_H_