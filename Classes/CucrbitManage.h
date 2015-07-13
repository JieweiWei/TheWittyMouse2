//
//  CucrbitManage.h
//  WittedMouse
//
//  Created by wc on 15/2/26.
//
//

#ifndef __WittedMouse__CucrbitManage__
#define __WittedMouse__CucrbitManage__

#include "cocos2d.h"
#include "Cucurbit.h"
#include "Mouse.h"
#include "HUDLayer.h"
USING_NS_CC;

class CucrbitManage : public Sprite {
public:
    bool init();
    
    /**
     * Move the cucrbit and make run with background
     */
    void moveCucrbit(float dif);
    
    /**
     * The processor of the cucurbit, which to grow the cucrbit
     */
    void cucurbitProcess(float dt);
    
    /**
     * Initialize the cucrbit in the screen
     */
    void initCucurbit();
    
    /**
     * To add the cucurbit if need
     */
    void addCucurbit(float dt);
    
    /**
     * Make the action of the cucrbit that fall down
     */
    void cucrbitFallDown(Cucurbit *cucrbit);
    
    /**
     * Remove the cucrbit that is crash with mouse of fall down in the ground
     */
    void removeFallDownCucrbit(Mouse *mouse, HUDLayer *hudLayer);

	Vector<Cucurbit*> getFallDownCucrbit();
    
    /**
     * Cucrbit touch event
     */
    bool cucrbitTouchEvent(Touch *touch, Event *event);

	void allCucrbitGrowUp();
	void allCucrbitFallDown();
    
    CREATE_FUNC(CucrbitManage);
    
private:
    Vector<Cucurbit*> cucurbits;
    Vector<Cucurbit*> cucurbitsToFallDown;
    Size size;
};

#endif /* defined(__WittedMouse__CucrbitManage__) */
