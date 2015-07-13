//
//  Snare.h
//  WriteMouseTest
//
//  Created by wc on 15/3/10.
//
//

#ifndef __WriteMouseTest__Snare__
#define __WriteMouseTest__Snare__

#include "cocos2d.h"

USING_NS_CC;

class Snare : public Sprite {
public:
	bool init();
	static Snare* createSnare(Vec2 position);
};

#endif /* defined(__WriteMouseTest__Snare__) */
