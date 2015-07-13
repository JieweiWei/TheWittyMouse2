/***********************************************
* Direction: �����򣬿����ڵ����������� label ��
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
	* ʹ�� fnt ���崴�����������
	*
	* @param label����������label
	*/
	void addTitle(Label* label);

	/**
	* ʹ�� TTF ��ʽ�����崴�� label����ʾ�ڵ���������
	*
	* @param alignType���з�ʽ��0Ϊ�������У�1Ϊ��������
	* @param item ��Ҫ�������е�menu
	*/
	void addLabel(int alignType, MenuItem* item, ...);

	void addMainMenu(int alignType, Vector<MenuItem*> items);

	void removeMainBody();

	void addNodeInMain(Node* node);
	
	/**
	* ���ݻص��������˵�ͼƬ�����˵����˵������ڵ�����Ŀ��ұ�Ե
	*
	* @param alignType���з�ʽ��0Ϊ�������У�1Ϊ��������
	* @param item ��Ҫ�������е�menu
	*/
	void addMenuInPopupFringe(int alignType, MenuItem* item, ...);

	/**
	* ���ݻص��������˵�ͼƬ�����˵����˵���������Ļ�ұ�
	*
	* @param alignType���з�ʽ��0Ϊ�������У�1Ϊ��������
	* @param item ��Ҫ�������е�menu
	*/
	void addMenuInScreenFringe(int alignType, MenuItem* item, ...);

	/**
	* ��ʾ������
	*/
	void display();

	/**
	* ���ص�����
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
