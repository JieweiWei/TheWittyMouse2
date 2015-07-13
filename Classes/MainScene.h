//
//  MainScene.h
//  WittedMouse
//
//  Created by wc on 15/2/14.
//
//

#ifndef __WittedMouse__MainScene__
#define __WittedMouse__MainScene__

#include "cocos2d.h"
#include "HUDLayer.h"
#include "Mouse.h"
#include "Cucurbit.h"
#include "Prop.h"
#include "PropManager.h"
#include "CucrbitManage.h"
#include "CloudManager.h"
#include "Snare.h"
#include "Progress.h"
#include "MouseRect.h"
#include "MouseUtil.h"
#include "SkateBoard.h"

USING_NS_CC;

class MainScene : public Layer {
public:
	virtual bool init();
	static Scene* createScene();
	/**
	* Move the background picture from right to left repeatly
	*/
	void moveBackgroundAndCucrbit(float dt);

	/**
	* The processor of the cucurbit, which to grow the cucrbit
	*/
	void cucurbitProcess(float dt);

	/**
	* To add the cucurbit if need
	*/
	void addCucurbit(float dt);

	/**
	* Initialize the cucrbit in the screen
	*/
	void initCucurbit();

	/**
	* The processor of event like touch
	*/
	void eventProcess();

	/**
	* The cucrbit which is incised or grown up and need to fall down
	*/
	void cucrbitFallDown(Cucurbit *cucrbit);

	/**
	* Remove the cucrbit that is crash with mouse of fall down in the ground
	*/
	void removeFallDownCucrbit(float dt);

	/**
	* The prop creator
	*/
	void propCreator(float dt);

	/**
	* Cucrbit touch event
	*/
	void cucrbitTouchEvent(Touch *touch, Event *event);

	/**
	* Prop touch event
	*/
	void propTouchEvent(Touch *touch, Event *event);

	/**
	* Prop container touch event
	*/
	void propContainerTouchEvent(Touch *touch, Event *event);

	/**
	* Make block with sholve
	*/
	void blockEvent(Touch *touch, Event *event);

	/**
	* The cloud creater
	*/
	void cloudCreater(float dt);

	/**
	* Create background
	*/
	void createBackground();

	/**
	* Create of cloud and its creator
	*/
	void createCloud();

	/**
	* Create of prop and its creater
	*/
	void createProp();

	/**
	* Create of mouse
	*/
	void createMouse();

	/**
	* Create of cucrbit
	*/
	void createCucrbit();

	/**
	* Create of weather
	*/
	void createWeather();

	/**
	* Create of progress
	*/
	void createProgress();

	/**
	* Create of blood progress
	*/
	void createProgressBlood();

	/**
	* Schedule process
	*/
	void scheduleProcess();

	void snareCreateProcess(Touch *touch, Event *event);

	/**
	* Remove snare from screen and vector
	*/
	void removeSnare();

	/**
	* Move the snare
	*/
	void moveSnare(float dif);

	/**
	* Fall to snare
	*/
	void fallInSnare();

	/**
	* Move mouse behine snare
	*/
	void moveMouseBehineSnare();

	/**
	* Update the progress display
	*/
	void updateProgressAndBlood();

	void runWithScooter();

	void rectCrashAction(ItemType itemType, Vec2 distance, Vec2 speed, float range);

	void rectCrash();

	void resetIsAction();

	void resetIsJump();

	void addSkateboard(float dt);

	bool isFridgeCrash(Node* first, Node* second);

	void moveSkateboard(float dif);
	void removeSkateboard(bool flag);
	void skateboardCrash();
	void resetIsSkateboardHit();
	void setIsSkateboardFinishAction();

	bool getIsAction();

	void setIsSholvePropChose(bool isSholvePropChose);
	///< The size of the screen
	CC_SYNTHESIZE_READONLY(Size, size, Size);

	CREATE_FUNC(MainScene);

private:
	bool isMouseOnSnare(Snare* snare);
	bool neareSnare(Snare* snare);
	void moveAllBg(float dif);
private:
	Sprite *bg1, *bg2;
	Snare* mouseFallingSnare;
	Mouse *mouse;
	MouseRect* mouseRect;
	Vector<Snare*> snares;
	PropManager *propManager;
	CucrbitManage *cucrbitManage;
	CloudManager* cloudManager;
	Progress* progress;
	ProgressBlood* progressBlood;
	Skateboard* skateboard;
	static HUDLayer *hudLayer;

	///< If there is a cucrbit fall down in one touch
	bool isHold;
	bool isFall;
	bool isAction;
	bool isJump;
	bool isSkateboardHit;
	bool isSkateboardFinishAction;
	bool isSkateboard;
	bool isSholvePropChose;
};

#endif /* defined(__WittedMouse__MainScene__) */
