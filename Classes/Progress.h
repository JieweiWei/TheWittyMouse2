//
//  Progress.h
//  WriteMouseTest
//
//  Created by wc on 15/3/10.
//
//

#ifndef __WriteMouseTest__Progress__
#define __WriteMouseTest__Progress__

#include "cocos2d.h"

USING_NS_CC;

/**
* 老鼠的路程图类
*/
class Progress : public Sprite {
public:
	bool init();
	void update();
	static void setDistance(float distance);
	static float getDistance();
	static void initDistance();
	CREATE_FUNC(Progress);

private:
	void moveWorm(float xChange);
private:
	ProgressTimer* pathProgress;
	Size size;
	Sprite* worm;
	static float distance;
};

class ProgressBlood : public Sprite {
public:
	bool init();
	void update();

	CREATE_FUNC(ProgressBlood);

private:
	ProgressTimer* pathProgressBlood;
	Size size;
	static float initBlood;
};

#endif /* defined(__WriteMouseTest__Progress__) */
