//
//  Cucurbit.h
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#ifndef __WittedMouse__Cucurbit__
#define __WittedMouse__Cucurbit__

#include "cocos2d.h"

USING_NS_CC;

class Cucurbit : public Sprite {
public:
    static Cucurbit* createCucurbit();
    virtual bool init();
    
    /**
     * The processor of the cucrbit when the cucrbit need growth
     *
     *@return Wtehter the cucrbit is mature
     */
    bool grow();

	/**
	* The cucrbit grow up directly
	*/
	void growUp();

	static float initialHeight();
    
    CC_SYNTHESIZE(bool, isCut, IsCut);
    CC_SYNTHESIZE(int, type, Type);

private:
	void createGrowAction();
private:
    int growTime;
    Size size;
	static float height;
};

#endif /* defined(__WittedMouse__Cucurbit__) */
