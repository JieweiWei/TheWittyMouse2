//
//  GameOver.h
//  WittedMouse
//
//  Created by wc on 15/2/27.
//
//

#ifndef __WittedMouse__GameOver__
#define __WittedMouse__GameOver__

#include "cocos2d.h"
#include "Popup.h"

class GameOver : public Layer {
public:
	bool init();
	/**
	* Display the message of Game over
	*/
	void gameOver(bool finish);

	/**
	* Replay the game
	*/
	void replay(Ref* sender);

	/**
	* Go to the main menu screen
	*/
	void mainMenu(Ref* sender);

	/**
	* Update the IQ and Life of mouse
	*/
	void update();


	CREATE_FUNC(GameOver);

private:
	Popup *popup;
	MenuItemLabel* IQLabel;
	MenuItemLabel* LifeLabel;
	MenuItemImage* mainSceneMenu;
	MenuItemImage* replayMenu;
	Label* labelTitle;
};

#endif /* defined(__WittedMouse__GameOver__) */
