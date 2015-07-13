//
//  Pause.h
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#ifndef __WittedMouse__Pause__
#define __WittedMouse__Pause__

#include "cocos2d.h"
#include "MainScene.h"
#include "Popup.h"

USING_NS_CC;

class Pause : public Layer {
public:
	bool init();

	/**
	* Pause function
	*/
	void pause(Ref* sender);

	/**
	* Resume after pause
	*/
	void resume(Ref* sender);

	/**
	* Go to main menu layer
	*/
	void mainMenu(Ref* sender);

	/**
	* Toggle button to control the game after touch the pause menu
	*/
	void toggleButton(bool flag);

	/**
	* Get the size of the pause menu
	*/
	Size getSizeOfMenu();

	/**
	* Hide the pause button
	*/
	static void hide();

	/**
	* Update the IQ and Life
	*/
	void update();

	CREATE_FUNC(Pause);
private:
	MenuItemSprite *pauseButton;
	MenuItemSprite *continueButton;
	Popup* popup;
	MenuItemLabel* IQLabel;
	MenuItemLabel* LifeLabel;
	MenuItemImage* mainSceneMenu;
};

#endif /* defined(__WittedMouse__Pause__) */
