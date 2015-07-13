//
//  Prop.h
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#ifndef __WittedMouse__Prop__
#define __WittedMouse__Prop__

#include "cocos2d.h"

USING_NS_CC;

/**
* Attribute for Prop that used by player
*/
enum Attribute {
	FERTILIZER = 1,
	BLOCK,
	MAGNET,
	LEAF = 4,
	SKATEBOARDSHOES,
	DIMENSIONDOOR
};

/**
* Prop used by player
*/
class Prop : public Sprite {
public:
	virtual bool init();

	/**
	* Gert the attribute of the prop
	*/
	Attribute getAttribute();

	/**
	* 气泡跑过屏幕的动作
	*/
	void run();

	/**
	* 气泡破裂的动作并飘到道具栏的动作
	*/
	virtual void burst(Vec2 containerPosition, Size containerSize);

	/**
	* 将自己移除
	*/
	void removeSelf(Prop *p);

	CC_SYNTHESIZE(bool, isTouch, IsTouch);

	CREATE_FUNC(Prop);
protected:
	Attribute attribute;
	Size size;
};

class Fertilizer : public Prop {
public:
	bool init();
	void burst(Vec2 containerPosition, Size containerSize);
	CREATE_FUNC(Fertilizer);
};

class Block : public Prop {
public:
	bool init();
	void burst(Vec2 containerPosition, Size containerSize);
	CREATE_FUNC(Block);
};

class Magent : public Prop {
public:
	bool init();
	void burst(Vec2 containerPosition, Size containerSize);
	CREATE_FUNC(Magent);
};

#endif /* defined(__WittedMouse__Prop__) */
