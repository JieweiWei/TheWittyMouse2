//
//  PropManager.h
//  WittedMouse
//
//  Created by wc on 15/2/25.
//
//

#ifndef __WittedMouse__PropManager__
#define __WittedMouse__PropManager__

#include "cocos2d.h"
#include "Prop.h"
#include "PropContainer.h"
#include "Snare.h"

USING_NS_CC;

class PropManager : public Sprite{
public:
	bool init();

	/**
	* Add a prop to the container, which means that the number of the prop increase by one
	*/
	void addProp(Attribute attribute);

	/**
	* Delete a prop from the container, which means that the number of the prop decrease by one
	*/
	bool deleteProp(Attribute attribute);

	/**
	* Update the number of the prop
	*/
	void update();

	/**
	* The event processor of screen touch when touch the prop
	*/
	void propTouchEvent(Touch *touch, Event *event);

	/**
	* Block made event
	*/
	Snare* blockEvent(Touch *touch, Event *event);

	/**
	* Create a prop randomly at intervals
	*/
	void propCreator(float dt);

	/**
	* The event processor of screen touch when touch the prop container
	*/
	void propContainerTouchEvent(Touch *touch, Event *event, CucrbitManage* cucrbitManage);

	void updateProp(float dt);

	/**
	* Creator of snare
	*/
	Snare* createSnare(Vec2 position);

	CREATE_FUNC(PropManager);
private:
	///< The container of three props
	Vector<PropContainer*> propContainers;
	Size size;
	Prop *prop;
};

#endif /* defined(__WittedMouse__PropManager__) */