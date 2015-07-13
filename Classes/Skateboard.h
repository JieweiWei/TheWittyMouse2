#ifndef __WittedMouse__Skateboard__
#define __WittedMouse__Skateboard__

#include "cocos2d.h"

USING_NS_CC;

class Skateboard : public Sprite {
public:
	bool init();
	void actionAfterHit();
	void resetSkateboardIsFinishFlag();

	CREATE_FUNC(Skateboard);

private:
	Size size;
};

#endif /* defined(__WittedMouse__Skateboard__) */
