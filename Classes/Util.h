//
//  Util.h
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#ifndef __WittedMouse__Util__
#define __WittedMouse__Util__

#include "cocos2d.h"

USING_NS_CC;

#define GAMELAYERTAG 8
#define GAMETAG 9
#define MOUSETAG 10
#define CUCRBITTAG 11
#define PAUSETAG 12
#define PROPTAG 13
#define GAMEOVERTAG 14
#define CLOUDTAG 15

class Util : public Ref {
public:
	static Util* getInstance();
	virtual void init();

    void setPauseMenuWidth(float pw);
    float getPauseMenuWidth();
    float getDif();
    void setDif(float dif_);
	void setDistanceTravelled(float distanceTravelled);
	float getDistanceTravelled();
	void setInitMouseLife(float initLife);
	float getInitMouseLife();

private:
    float pauseMenuWidth;
    float dif;
	float distanceTravelled;
	float initMouseLife;

	static Util* util;
};


#endif /* defined(__WittedMouse__Util__) */
