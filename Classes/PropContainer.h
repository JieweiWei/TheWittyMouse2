//
//  PropContainer.h
//  WittedMouse
//
//  Created by wc on 15/2/26.
//
//

#ifndef __WittedMouse__PropContainer__
#define __WittedMouse__PropContainer__

#include "cocos2d.h"
#include "Prop.h"
#include "CucrbitManage.h"
#include "Snare.h"

USING_NS_CC;

class PropContainer : public Sprite {
public:
    virtual bool init();
    /**
     * Add a prop to the prop container
     */
    void addAProp();
    
    /**
     * Delete a prop from the prop container
     */
    virtual bool deleteAProp();
    
    /**
     * Is the container empty
     */
    bool isEmpty();
    
    /**
     * Update the container and the prop in the screen
     */
    void updateContainer();

	virtual void  propEffectAction(CucrbitManage* cucrbitManage);

	int getPropNum() const;

	CC_SYNTHESIZE(Attribute, attribute, TheAttribute);

	CREATE_FUNC(PropContainer);
    
protected:
    int propNum;
	Size size;
    Label* numLabel;
};

class FertilizerContainer : public PropContainer {
public:
	bool init();
	void  propEffectAction(CucrbitManage* cucrbitManage);
	CREATE_FUNC(FertilizerContainer);
};

class BlockContainer : public PropContainer {
public:
	bool init();
	void  propEffectAction(CucrbitManage* cucrbitManage);
	bool deleteAProp();
	CREATE_FUNC(BlockContainer);
};

class MagentContainer : public PropContainer {
public:
	bool init();
	void  propEffectAction(CucrbitManage* cucrbitManage);
	CREATE_FUNC(MagentContainer);
};

#endif /* defined(__WittedMouse__PropContainer__) */
