#ifndef __WittedMouse__Cloud__
#define __WittedMouse__Cloud__

#include "cocos2d.h"

USING_NS_CC;

class Cloud : public Sprite {
public:
	virtual bool init();
	void cloudAction();
	void removeSelf(Cloud *c);
	CREATE_FUNC(Cloud);
private:
	Size size;
};

#endif /* defined(__WittedMouse__Cloud__) */
