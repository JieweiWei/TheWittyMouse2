#ifndef _LOADINGSCENE_H_
#define _LOADINGSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

#define INIT_IQ 50
#define INIT_LIFE 100
#define INIT_DISTANCE 1000

class LoadingScene : public Layer {
public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LoadingScene);

	static void loadData();

private:
	void loadRes();
};

#endif // !_LOADINGSCENE_H_
