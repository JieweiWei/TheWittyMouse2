#ifndef _MOUSE_CONTROLLER_
#define _MOUSE_CONTROLLER_

#include "MouseUtil.h"

#include "cocos2d.h"
USING_NS_CC;

const int maxIQ = 100;
const float dt = 0.1;

class MouseController : public Ref {
public:
	static MouseController* getInstance();
	virtual bool init();
	MouseAction getMouseAction(float IQ, ItemType itemtype, Vec2 dis, Vec2 speed, float range);
private:
	int cmpFloat(float f1, float f2, float range);
private:
	static MouseController* mouseController;
};

#endif // !_MOUSE_CONTROLLER_