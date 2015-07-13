/***********************************************
* Direction: 弹出框，可以在弹出框上增加 label 和
*              button
* Create Time: 2015-02-28 19:11:21
*
* Author: Zhiwang Xie
*
* E-mail: xiezhw3@163.com
***********************************************/

#ifndef __WittedMouse__Popup1__
#define __WittedMouse__Popup1__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define MAIN_BODY 1

class Popup : public Sprite {
public:
	bool init();

	/**
	* 使用 fnt 字体创建弹出框标题
	*
	* @param label弹出框标题的label
	*/
	void addTitle(Label* label);

	/**
	* 使用 TTF 格式的字体创建 label，显示在弹出框中央
	*
	* @param alignType排列方式，0为纵向排列，1为横向排列
	* @param item 需要进行排列的menu
	*/
	void addLabel(int alignType, MenuItem* item, ...);

	void addMainMenu(int alignType, Vector<MenuItem*> items);

	void removeMainBody();

	void addNodeInMain(Node* node);
	
	/**
	* 根据回调函数，菜单图片创建菜单，菜单排列在弹出框的框右边缘
	*
	* @param alignType排列方式，0为纵向排列，1为横向排列
	* @param item 需要进行排列的menu
	*/
	void addMenuInPopupFringe(int alignType, MenuItem* item, ...);

	/**
	* 根据回调函数，菜单图片创建菜单，菜单排列在屏幕右边
	*
	* @param alignType排列方式，0为纵向排列，1为横向排列
	* @param item 需要进行排列的menu
	*/
	void addMenuInScreenFringe(int alignType, MenuItem* item, ...);

	/**
	* 显示弹出框
	*/
	void display();

	/**
	* 隐藏弹出框
	*/
	void hide();

	CREATE_FUNC(Popup);

	Label* getTile();

	void setTitle(Label* _title);

	void setTitleText(std::string titleText);

private:
	Sprite *bg;

	Size size;

	Label* title;
};

#endif /* defined(__WittedMouse__Popup1__) */
