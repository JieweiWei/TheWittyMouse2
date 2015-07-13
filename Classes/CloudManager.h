#ifndef __WittedMouse__CloudManager__
#define __WittedMouse__CloudManager__

#include "cocos2d.h"
#include "Cloud.h"

USING_NS_CC;

class CloudManager : public Sprite {
public:
	virtual bool init();
	void createCloud();
	void removeOutCloud();
	CREATE_FUNC(CloudManager);
private:
	Size size;
	Vector<Cloud*> clouds;
};

#endif /* defined(__WittedMouse__CloudManager__) */
